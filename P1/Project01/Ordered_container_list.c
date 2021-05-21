/* Ordered_container_list.c */

#include "Utility.h"
#include "Ordered_container.h"


#include <stdio.h>  /* defines NULL */
#include <stdlib.h> /* standard library, includes malloc/free */
#include <assert.h>

/* These global variables are used to monitor the memory usage of the Ordered_container */
int g_Container_count = 0;		       /* number of Ordered_containers currently allocated */
int g_Container_items_in_use = 0;	   /* number of Ordered_container items currently in use */
int g_Container_items_allocated = 0;   /* number of Ordered_container items currently allocated */

/*Ordered_container_list. In the linked-list implementation, the container is a linked-list
and the items are list nodes that contain a void* data pointer. The nodes are designated to
the client by casting node pointers to/from void*. Performance notes: The list is searched
linearly to locate items, and to locate where to insert a new item. We insert a new item by
creating a new node that comes before the appropriate existing node, or at the end of the list,
designated with an item pointer of NULL. Searching and inserting is linear with the number of
items (size) of the container (O(n)).

As shown by the declarations in the Ordered_container_list_skeleton.c file, we use a doubly-linked
or two-way linked list. Although this requires more code, it has the advantage that once a node is
located for removal, or a point of insertion is determined, the change to the list can be made in
constant (O(1)) time. In addition, as the list is modified, we keep and update a pointer to the last
node in the list, as well as the first node. This allows us to add a node to the end of the list without
having to scan for its predecessor. Similarly, we keep up-to-date a member variable for the current size
(length) of the list, so that client code can get the size in constant time. Finally, the insert and
find functions must search the list with a linear scan, but they always stop scanning when they have "gone
past" where the matching item would be if it was present. This way if the matching item is not present,
on the average only half the list will have to be examined. The time complexity is still linear, but this
small tweak saves a lot of time even so.

Implementation note: One approach to implementing a linked-list involves creating dummy nodes to simplify
the handling of empty lists. This approach is not recommended for this project for two reasons: (1) it
involves ugly special-case counting of the number of nodes in empty lists; (2) more seriously, it will
lead to the creation of bogus objects when you convert the code to a C++ templated
container class in the next project.*/

/* struct LL_Node structure declaration. This declaration is local to this file.
This is a two-way or doubly-linked list. Each node has a pointer to the previous
node and another pointer to the next node in the list. This means insertions or
removals of a node can be made in constant time, once the location has been
determined. */

struct LL_Node {
	struct LL_Node* prev;      /* pointer to the previous node */
	struct LL_Node* next;	   /* pointer to the next node */
	void* data_ptr; 		   /* uncommitted pointer to a data object created by the client */
};


/* Declaration for Ordered_container. This declaration is local to this file.
A pointer is maintained to the last node in the list as well as the first,
meaning that additions to the end of the list can be made in constant time.
The number of nodes in the list is kept up-to-date in the size member
variable, so that the size of the list can be accessed in constant time. */
struct Ordered_container {
	OC_comp_fp_t comp_func;     /* function to compare data types to keep desired order */
	struct LL_Node* first;      /* pointer to the first node */
	struct LL_Node* last;       /* pointer to the last node */
	int size;                   /* current size of container */
};


/* helper function */
int find_position(struct Ordered_container* c_ptr, struct LL_Node** current_node, struct LL_Node* item);


/*
Functions for the entire container.
*/

/* Create an empty container using the supplied comparison function, and return the pointer to it. */
/* same as (int (*OC_comp_fp_t) (const void* data_ptr1, const void* data_ptr2) f_ptr) */
struct Ordered_container* OC_create_container(OC_comp_fp_t f_ptr) {
	/* create data structure on the heap */
	struct Ordered_container* container = safe_malloc(sizeof(struct Ordered_container));
	/* initialize contain variables */
	container->comp_func = f_ptr;
	container->first = NULL;
	container->last = NULL;
	container->size = 0;
	/* update the number of Ordered_containers currently allocated */
	++g_Container_count;
	return container;
}

/* Destroy the container and its items; caller is responsible for
deleting all pointed-to data before calling this function.
After this call, the container pointer value must not be used again.*/
void OC_destroy_container(struct Ordered_container* c_ptr) {
	/* free the dynamically allocated items */
	OC_clear(c_ptr);
	/* free the dynamically allocated container */
	free(c_ptr);
	/* If expression evaluates to true, assert() does nothing If expression
	evaluates to false, assert() displays an error message on stderr
	(standard error stream to display error messages) and aborts program
	execution */
	assert(g_Container_count > 0);
	/* update the number of Ordered_containers currently allocated */
	--g_Container_count;
}

/* Delete all the items in the container and initialize it.
Caller is responsible for deleting any pointed-to data first. */
void OC_clear(struct Ordered_container* c_ptr) {
	/* copy current node to get to next node before deallocating*/
	struct LL_Node* temp;
	struct LL_Node* current = c_ptr->first;
	while (current) { /* while current is valid */
		/* copy next one */
		temp = current;
		current = current->next;
		/* free current node */
		free(temp);
	}
	/* update the globals */
	g_Container_items_in_use -= c_ptr->size;
	g_Container_items_allocated -= c_ptr->size;
	/* re-initialize the Ordered_container */
	c_ptr->first = NULL;
	c_ptr->last = NULL;
	c_ptr->size = 0;

}

/* Return the number of items currently stored in the container */
int OC_get_size(const struct Ordered_container* c_ptr) {
	return c_ptr->size;
}

/* Return non-zero (true) if the container is empty, zero (false) if the container is non-empty */
int OC_empty(const struct Ordered_container* c_ptr) {
	return (c_ptr->size) > 0 ? 0 : 1;
}


/*
Functions for working with individual items in the container.
*/

/* Get the data object pointer from an item. */
void* OC_get_data_ptr(const void* item_ptr) {
	/* client side - when you get a data pointer out of the container, you have
	to cast th void* to the correct type in order to access the data
	in the object because it is forever an incomplete type. Pointer is just
	an address in memory. void pointers has no type information associated
	with it. Therefore, the computer does not know how many bytes this pointer
	points to. Because a void pointer has no data type, that creates a problem
	for the compiler to predict the size of the pointed object. So before
	dereferencing we have to typecast it to help the compiler out */

	/* why are void pointer used?
	A very important feature of the void pointer is reusability. Using the void pointer
	can store the address of any object and whenever required we can get back the
	object through the indirection operator with proper casting. */

	/* item_ptr-> == (*item_ptr. ), in the process of accessing you are dereferencing */
	return ((struct LL_Node*)item_ptr)->data_ptr;
}

/* Delete the specified item.
Caller is responsible for any deletion of the data pointed to by the item. */
void OC_delete_item(struct Ordered_container* c_ptr, void* item_ptr) {
	struct LL_Node* node = (struct LL_Node*)item_ptr;
	/* fix head and tail */
	if (node->prev == NULL) { /* head */
		c_ptr->first = node->next;
	}
	if (node->next == NULL) { /* tail */
		c_ptr->last = node->prev;
	}
	/* fix bindings */
	if (node->prev != NULL)
		node->prev->next = node->next;
	if (node->next != NULL)
		node->next->prev = node->prev;

	node->prev = NULL;
	node->next = NULL;
	/* after fixing nodes */
	free(node);
	/* update container */
	--(c_ptr->size);
	--g_Container_items_allocated;
	--g_Container_items_in_use;
}

/*
Functions that search and insert into the container using the supplied comparison function.
*/

/* Create a new item for the specified data pointer and put it in the container in order.
If there is already an item in the container that compares equal to new item according to
the comparison function, the insertion will not take place and 0 is returned to indicate failure.
Otherwise, the insertion is done and non-zero is returned to show success.
This function will not modify the pointed-to data. */

void insert_before(struct Ordered_container* c_ptr, struct LL_Node* current_node, struct LL_Node* item) {
	item->prev = current_node->prev; /* guaranteed move */
	item->next = current_node;       /* guaranteed move */
	if (current_node->prev == NULL) {
		c_ptr->first = item;
	}
	else {
		current_node->prev->next = item;
	}
	current_node->prev = item; /* guaranteed move, after done using prev */
}

void insert_after(struct Ordered_container* c_ptr, struct LL_Node* current_node, struct LL_Node* item) {
	item->prev = current_node;
	item->next = current_node->next;
	c_ptr->last = item;
	current_node->next = item;
}

int OC_insert(struct Ordered_container* c_ptr, const void* data_ptr) {
	/* create new item for specified data_ptr */
	struct LL_Node* item = safe_malloc(sizeof(struct LL_Node));
	item->data_ptr = (void*)data_ptr;
	item->next = NULL;
	item->prev = NULL;
	/* search and find correct index, interrupts if found equal or greater */
	if (OC_empty(c_ptr)) { /* if container is empty */
		c_ptr->first = item;
		c_ptr->last = item;
	}
	else {
		struct LL_Node* current_node = c_ptr->first;
		/* only breaks if 0 (equal) or -1 (less) than returns */
		int results = find_position(c_ptr, &current_node, item);
		/* break with results 0 (matching item, do nothing) */
		if (results == 0) { return 0; }
		/* break with -1 (found larger one), fit before  */
		if (results < 0) { insert_before(c_ptr, current_node, item); }
		/* break with results 1 (no larger one, reached end), fit after tail */
		else { insert_after(c_ptr, current_node, item); }
	}
	/* increase size of Ordered_container and globals */
	++(c_ptr->size);
	++g_Container_items_in_use;
	++g_Container_items_allocated;
	/* success, no matching item */
	return 1;
}

/* Return a pointer to an item that points to data equal to the data object pointed to by data_ptr,
using the ordering function to do the comparison with data_ptr as the first argument.
The data_ptr object is assumed to be of the same type as the data objects pointed to by container items.
NULL is returned if no matching item is found.
The pointed-to data will not be modified. */
void* OC_find_item(const struct Ordered_container* c_ptr, const void* data_ptr) {
	struct LL_Node* current = c_ptr->first;
	/* break if NULL, or 0 */
	while (current) {
		/* success, found node */
		if (current->data_ptr == data_ptr) { return current; }
		current = current->next;
	}
	/* failure, no matching item */
	return NULL;
}

/* Return a pointer to the item that points to data that matches the supplied argument given by arg_ptr
according to the supplied function, which compares arg_ptr as the first argument with the data pointer
in each item. This function does not require that arg_ptr be of the same type as the data objects, and
so allows the container to be searched without creating a complete data object first.
NULL is returned if no matching item is found. If more than one matching item is present, it is
unspecified which one is returned. The comparison function must implement an ordering consistent
with the ordering produced by the comparison function specified when the container was created;
if not, the result is undefined. */
void* OC_find_item_arg(const struct Ordered_container* c_ptr, const void* arg_ptr, OC_find_item_arg_fp_t fafp) {
	struct LL_Node* current = c_ptr->first;

	while (current) {
		/* success */
		if (fafp(arg_ptr, current->data_ptr) == 0) { return current; }
		current = current->next;
	}
	/* failure, no matching item */
	return NULL;
}


/*
Functions that traverse the items in the container, processing each item in order.
*/

/* Apply the supplied function to the data pointer in each item of the container.
The contents of the container cannot be modified. */
void OC_apply(const struct Ordered_container* c_ptr, OC_apply_fp_t afp) {
	struct LL_Node* node = c_ptr->first;
	while (node) {
		/* apply function given to data pointer */
		afp(node->data_ptr);
		node = node->next;
	}
}

/* Apply the supplied function to the data pointer in each item in the container.
If the function returns non-zero, the iteration is terminated, and that value
returned. Otherwise, zero is returned. The contents of the container cannot be modified. */
int OC_apply_if(const struct Ordered_container* c_ptr, OC_apply_if_fp_t afp) {
	struct LL_Node* node = c_ptr->first;
	while (node) {
		/* apply function with conditional */
		int result = afp(node->data_ptr);
		if (result != 0) { return result; }
		node = node->next;
	}
	return 0;
}


/* Apply the supplied function to the data pointer in each item in the container;
the function takes a second argument, which is the supplied void pointer.
The contents of the container cannot be modified. */
void OC_apply_arg(const struct Ordered_container* c_ptr, OC_apply_arg_fp_t afp, void* arg_ptr) {
	struct LL_Node* node = c_ptr->first;
	while (node) {
		/* apply function with two arguments */
		afp(node->data_ptr, arg_ptr);
		node = node->next;
	}
}


/* Apply the supplied function to the data pointer in each item in the container;
the function takes a second argument, which is the supplied void pointer.
If the function returns non-zero, the iteration is terminated, and that value
returned. Otherwise, zero is returned. The contents of the container cannot be modified */
int OC_apply_if_arg(const struct Ordered_container* c_ptr, OC_apply_if_arg_fp_t afp, void* arg_ptr) {
	struct LL_Node* node = c_ptr->first;
	while (node) {
		/* apply function with two argumetns and conditional */
		int result = afp(node->data_ptr, arg_ptr);
		if (result != 0) { return result; }
		node = node->next;
	}
	return 0;
}

/* helper functions */
int find_position(struct Ordered_container* c_ptr, struct LL_Node** current_node, struct LL_Node* item) {
	/* find position and return results to determine proper insertion method */
	int results;
	while ((results = c_ptr->comp_func(item->data_ptr, (*current_node)->data_ptr)) > 0) {
		if ((*current_node)->next == NULL) /* if reached the end, break; */
			break;
		*current_node = (*current_node)->next;
	}
	return results;
}
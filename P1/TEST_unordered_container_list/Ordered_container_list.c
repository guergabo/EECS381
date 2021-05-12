/* skeleton file for Ordered_container_list.c
The struct declarations below must be used for the linked-list node and Ordered_container objects.
Remove this comment and complete this file with all necessary code.*/

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


/*
Functions that search and insert into the container using the supplied comparison function.
*/

/* Create a new item for the specified data pointer and put it in the container in order.
If there is already an item in the container that compares equal to new item according to
the comparison function, the insertion will not take place and 0 is returned to indicate failure.
Otherwise, the insertion is done and non-zero is returned to show success.
This function will not modify the pointed-to data. */
int OC_insert(struct Ordered_container* c_ptr, const void* data_ptr) {


	return 1; 
}

/* Return a pointer to an item that points to data equal to the data object pointed to by data_ptr,
using the ordering function to do the comparison with data_ptr as the first argument.
The data_ptr object is assumed to be of the same type as the data objects pointed to by container items.
NULL is returned if no matching item is found.
The pointed-to data will not be modified. */
void* OC_find_item(const struct Ordered_container* c_ptr, const void* data_ptr) {

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

}


/*
Functions that traverse the items in the container, processing each item in order.
*/
#include "Utility1.h"
#include "Ordered_container.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define INITIAL_ARRAY_SIZE 3
#define GROW_ARRAY_FACTOR 2

/*Ordered_container_array. In the dynamic array implementation, the container is a dynamically 
allocated array in which each cell contains a void*. The cells of the array are designated to 
the client code by casting the address of a cell to/from a void*. Performance notes. The array 
is searched using binary search to locate items, so that searching will be logarithmic with 
container size (O(log n)). Not only the find functions use binary search, but also the insert 
function should use binary search to locate where to insert a new item. Note that the next step 
for insertion requires moving the items that come after the new item "down" by one to make room 
for the new item. This means that the insertion time is overall linear, even if binary search is 
used to speed up the first step. Similar to the "gone past" strategy, this will greatly improve 
average insertion performance even if the time is O(n) in the limit. */

/*Implementation notes: While in the linked-list implementation an item pointer points to a list 
node, in the array implementation, the item pointer simply points to an array cell. Since the 
array cell is a void*, a pointer to an array cell is a void**. The interface for the container 
requires casting this void** item pointer to/from a simple void* item pointer. Your implementation 
of the array container should represent item pointers in this way. As shown by the declarations in 
the Ordered_container_array_skeleton.c file, your code should have a simple void** pointer that 
points to the first cell of the array, and likewise, you should point to cells with a void**
pointer as well. Be brave and confront the double-void pointer! The C Standard Library includes 
a binary search function, bsearch, which is great, but it will not tell you where to insert an item if
it is not present. Fortunately, there is a simple modification to the binary search algorithm that will 
give you both whether or not the item is present, and if it is not, where it should be put. This is a 
good justification for writing your own, more general-purpose, binary search function. For example, 
refer to the example binary search function in K&R, p. 58 — if you drop out of the loop, the item was
not found, but the place where it should be inserted would be high+1. Consider writing a binary search 
helper function that in addition to returning where the item was found (or not) also takes an int* 
parameter and uses it to return the array index where the insertion should be made if the item is not 
present. Call this function to implement both finding and insertion. Notice that to delete an
item, the item pointer designates the to-be-removed item directly — you don’t need to search for it.
Growing the array. The array is dynamically allocated when the container is created, and initially 
contains a small number of cells. As items are added, the array is reallocated as needed: if there is 
no room for the new item, a bigger array is allocated, and the data pointers copied over, and the old 
array is deallocated. Note that if the to-be-inserted item is already present, the insertion is not done,
and so the array would not need to be increased in size. In other words, the process of checking the 
current allocation and then reallocation, copying the data, etc. is performed only if the new item will 
be actually inserted. For this project, the initial size of the array is 3 cells. When a new item is to 
be inserted and the array is full, a new array is allocated whose size is double the space required to 
hold the original array plus the new value (new size = 2 * (old size + 1)). This scheme can waste some
memory space, but results in fairly fast performance because as the container is filled, fewer new 
allocation/copy/ deallocate operations are required. But the array normally will have cells that are not 
currently in use; so this implementation has to keep track of how many cells are in use to hold items, 
which is returned by the OC_get_size function, and how many cells are currently allocated — the size of 
the current allocated array. To remove an item, the items that come after the removed one are moved
"up" by one, but the array is not reallocated — it retains its original size. The only time the array 
is "shrunk" is with the OC_clear function, which discards the entire array and starts over with the 
initial small allocation.*/

/* skeleton file for Ordered_container_array.c
The struct declaration below must be used for the Ordered_container object.
Remove this comment and complete this file with all necessary code.
*/

/* These global variables are used to monitor the memory usage of the Ordered_container */
int g_Container_count;				/* number of Ordered_containers currently allocated */
int g_Container_items_in_use;		/* number of Ordered_container items currently in use */
int g_Container_items_allocated;	/* number of Ordered_container items currently allocated */

/* A complete type declaration for Ordered_container implemented as an array */
struct Ordered_container {
	OC_comp_fp_t comp_fun;	/* pointer to comparison function  */
	void** array;			/* pointer to array of pointers to void, also void* array[] */
	int allocation;			/* current memory size of array */
	int size;				/* number of items currently in the array */
};


/* helper functions */
void initialize_array(struct Ordered_container* c_ptr);
int binary_finder(const struct Ordered_container* c_ptr, const void* data_ptr,
	OC_comp_fp_t comp_func, int* index);
void grow_array(struct Ordered_container* c_ptr);

/*
Functions for the entire container.
*/

/* Create an empty container using the supplied comparison function, and return the pointer to it. */
struct Ordered_container* OC_create_container(OC_comp_fp_t f_ptr) {
	struct Ordered_container* container = safe_malloc(sizeof(struct Ordered_container));
	/* initialize data types */
	container->comp_fun = f_ptr; 
	container->array = NULL; 
	container->allocation = 0;
	container->size = 0; 
	/* update globals */
	++g_Container_count;
	return container; 
}

/* Destroy the container and its items; caller is responsible for
deleting all pointed-to data before calling this function.
After this call, the container pointer value must not be used again.*/
void OC_destroy_container(struct Ordered_container* c_ptr) {
	/* free array */
	free(c_ptr->array);
	g_Container_items_in_use -= c_ptr->size;
	g_Container_items_allocated -= c_ptr->allocation;
	/* now free the container itself */
	free(c_ptr);
	--g_Container_count;
}


/* Delete all the items in the container and initialize it.
Caller is responsible for deleting any pointed-to data first. */

void OC_clear(struct Ordered_container* c_ptr) {
	/* free array */
	free(c_ptr->array);
	g_Container_items_in_use -= c_ptr->size; 
	g_Container_items_allocated -= c_ptr->allocation;
	/* initialize container */
	initialize_array(c_ptr);
}

/* Return the number of items currently stored in the container */
int OC_get_size(const struct Ordered_container* c_ptr) {
	return c_ptr->size; 
}

/* Return non-zero (true) if the container is empty, zero (false) if the container is non-empty */
int OC_empty(const struct Ordered_container* c_ptr) {
	return (c_ptr->size) == 0; 
}

/*
Functions for working with individual items in the container.
*/


/* Get the data object pointer from an item. */
void* OC_get_data_ptr(const void* item_ptr) {
	/* check if not null */
	assert(item_ptr);
	/* item_ptr is a void pointer pointing to the address of the void pointer in the array */
	/* therefore, it is a poitner of a void* making it = void** */
	/* cast it as a void** and dereference is to the not the adress of the void* in th array 
	but the void* itself. */
	/* to get data from a double void pointer I have to dereference it */
	/* fuck a double void pointer... */
	/* ((*int) ptr)->something == (*((*int) ptr)).something */
	/* void* can is generic and therefore can take a double void pointer as well */
	return  *((void**)item_ptr);
}

/* Delete the specified item.
Caller is responsible for any deletion of the data pointed to by the item. */
void OC_delete_item(struct Ordered_container* c_ptr, void* item_ptr) {
	void** container_end = c_ptr->array + c_ptr->size;
	void** data_ptr = (void**)item_ptr;
	/* move all elements above deleted element down */
	while (data_ptr < container_end) {
		*data_ptr = *(data_ptr + 1); // last one should take NULL? 
		++data_ptr; 
	}
	--(c_ptr->size);
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
int OC_insert(struct Ordered_container* c_ptr, const void* data_ptr) {
	/* if equal to new item the insertion will not take place */
	/* advantage of array is that it is contiguous memory */
	int index = 0, i = 0, result;

	/* if the array is full, grow it */
	if (c_ptr->size == c_ptr->allocation)
		grow_array(c_ptr);
	/* find index to fit the new item */
	result = binary_finder(c_ptr, data_ptr, c_ptr->comp_fun, &index);
	if (result) { return 0; } /* already exist with value */

	/* move all element above new item up one */
	for (i = c_ptr->size; i > index; --i) {
		c_ptr->array[i] = c_ptr->array[i - 1];
	}
	/* insert item */
	c_ptr->array[index] = data_ptr; 
	++(c_ptr->size);
	/* updata globals */
	++g_Container_items_in_use;

	return 1; 
}

/* Return a pointer to an item that points to data equal to the data object pointed to by data_ptr,
using the ordering function to do the comparison with data_ptr as the first argument.
The data_ptr object is assumed to be of the same type as the data objects pointed to by container items.
NULL is returned if no matching item is found.
The pointed-to data will not be modified. */
void* OC_find_item(const struct Ordered_container* c_ptr, const void* data_ptr) {
	int index; 
	int found = binary_finder(c_ptr, data_ptr, c_ptr->comp_fun, &index);

	/* c_ptr->array is index 0 */
	/* return a pointer to the void* which is the item of the array of pointers */
	return (found) ? c_ptr->array + index : NULL; 

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
	int index; 
	int found = binary_finder(c_ptr, arg_ptr, fafp, &index);
	/* c_ptr->array is index 0 */
	/* return a pointer to the void* which is the item of the array of pointers */
	return (found) ? c_ptr->array + index : NULL;

}


/*
Functions that traverse the items in the container, processing each item in order.
*/

/* Apply the supplied function to the data pointer in each item of the container.
The contents of the container cannot be modified. */
void OC_apply(const struct Ordered_container* c_ptr, OC_apply_fp_t afp) {
	/* void* is the node */
	int i; 
	for (i = 0; i < c_ptr->size; ++i)
		afp(c_ptr->array[i]);
}

/* Apply the supplied function to the data pointer in each item in the container.
If the function returns non-zero, the iteration is terminated, and that value
returned. Otherwise, zero is returned. The contents of the container cannot be modified. */
int OC_apply_if(const struct Ordered_container* c_ptr, OC_apply_if_fp_t afp) {
	int i, result;
	for (i = 0; i < c_ptr->size; ++i) {
		if (result = afp(c_ptr->array[i]) != 0) { return result; };
	}
	return 0; 
}

/* Apply the supplied function to the data pointer in each item in the container;
the function takes a second argument, which is the supplied void pointer.
The contents of the container cannot be modified. */
void OC_apply_arg(const struct Ordered_container* c_ptr, OC_apply_arg_fp_t afp, void* arg_ptr) {
	int i;
	for (i = 0; i < c_ptr->size; ++i)
		afp(c_ptr->array[i], arg_ptr);
}

/* Apply the supplied function to the data pointer in each item in the container;
the function takes a second argument, which is the supplied void pointer.
If the function returns non-zero, the iteration is terminated, and that value
returned. Otherwise, zero is returned. The contents of the container cannot be modified */
int OC_apply_if_arg(const struct Ordered_container* c_ptr, OC_apply_if_arg_fp_t afp, void* arg_ptr) {
	int i, result; 
	for(i = 0; i < c_ptr->size; ++i)
		if (result = afp(c_ptr->array[i], arg_ptr) != 0) { return result; }
	return 0; 
}


/* helper function */
/* initialize array with INITIAL_ARRAY_SIZE */
void initialize_array(struct Ordered_container* c_ptr) {
	c_ptr->array = safe_malloc(INITIAL_ARRAY_SIZE * sizeof(void*));
	c_ptr->allocation = INITIAL_ARRAY_SIZE;
	c_ptr->size = 0;

	g_Container_items_allocated += INITIAL_ARRAY_SIZE;
}

/* binary search function that updates index to to find the item */
int binary_finder(const struct Ordered_container* c_ptr, const void* data_ptr,
	OC_comp_fp_t comp_func, int* index) {

	int result;
	int low = 0;
	int high = c_ptr->size - 1;
	int mid;

	while (low <= high) {
		mid = (low + high) / 2;
		/* c_ptr->array[mid] == (*c_ptr).array[mid] */
		/* if pa poinnts to a particular element of an array, then pa + 1 points to next */
		/* in evaulating a[i] C converts it to *(a =+i) */
		/* if pa is a pointer, expressions may use it with a subscript, pa[i];
		pa[i] is identical to *(pa + i) */
		/* there is one difference between an array name and a poitner that must be kept in mind.
		a pointer is a variable, so pa=a and pa++ are legal. But an array name is not a variable;
		construction like a=pa and a++ are illegal. */
		/* c_ptr->array[mid] == *(c_ptr->array + mid)*/
		if ((result = comp_func(data_ptr, c_ptr->array[mid])) < 0) {
			high = mid - 1;
		}
		else if (result > 0) {
			low = mid + 1;
		}
		else {
			/* found item */
			*index = mid;
			return 1;
		}
	}
	/* failed to find item, high + 1 is index where it should be inserted */
	*index = high + 1;
	return 0;

}

/* When a new item is to
be inserted and the array is full, a new array is allocated whose size is double the space required to
hold the original array plus the new value(new size = 2 * (old size + 1)).This scheme can waste some
memory space, but results in fairly fast performance because as the container is filled, fewer new
allocation / copy / deallocate operations are required.But the array normally will have cells that are not
currently in use; so this implementation has to keep track of how many cells are in use to hold items,
which is returned by the OC_get_size function, and how many cells are currently allocated — the size of
the current allocated array.To remove an item, the items that come after the removed one are moved
"up" by one, but the array is not reallocated — it retains its original size.The only time the array
is "shrunk" is with the OC_clear function, which discards the entire arrayand starts over with the
initial small allocation.*/
void grow_array(struct Ordered_container* c_ptr) {
	int bigger_allocation;
	void** bigger_array;
	int i;

	/* have to create new array*/
	bigger_allocation = GROW_ARRAY_FACTOR + (c_ptr->size + 1);
	bigger_array = safe_malloc(bigger_allocation * sizeof(void*));
	/* copy old array into new array */
	for (i = 0; i < c_ptr->size; ++i) {
		bigger_array[i] = c_ptr->array[i];
	}
	/* free old array */
	free(c_ptr->array);
	/* set new array */
	c_ptr->array = bigger_array;
	c_ptr->allocation = bigger_allocation;
	/* update globals */
	g_Container_items_allocated += (bigger_allocation - c_ptr->size);
}
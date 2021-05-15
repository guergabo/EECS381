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

/* helper function */
void initialize_array(struct Ordered_container* c_ptr) {
	c_ptr->array = safe_malloc(INITIAL_ARRAY_SIZE * sizeof(void*));
	c_ptr->allocation = INITIAL_ARRAY_SIZE;
	c_ptr->size = 0; 

	g_Container_items_allocated += INITIAL_ARRAY_SIZE; 
}

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


/* helper function */


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
	int size = c_ptr->size; 
	void** container_ptr = c_ptr->array;
	void** data_ptr = (void**)item_ptr;

	/* move all elements above deleted element down */
	/*  0  1  2  3  4  5     6       7  8   */
	/* [v][v][v][v][v][v][delete v][v1][v2] */
	/* [v][v][v][v][v][v] [v1][v2][v2]      */
	/* [v][v][v][v][v][v] [v1][v2][NULL]    */
	/* contiguous memory so address will be in increasing order */
	/* guaranteed to be stored in increasing order */
	/* start from item given and shift everything else down afterwards*/
	while (data_ptr <= (container_ptr + (size - 1))) {
		if (data_ptr == (container_ptr + (size - 1))) {
			data_ptr == NULL;
			break;
		}
		*data_ptr = *(data_ptr + 1);
		++data_ptr; 
	}
	--(c_ptr->size);
	--g_Container_items_in_use;
}


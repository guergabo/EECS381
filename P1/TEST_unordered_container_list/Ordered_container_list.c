/* skeleton file for Ordered_container_list.c
The struct declarations below must be used for the linked-list node and Ordered_container objects.
Remove this comment and complete this file with all necessary code.*/

#include "Ordered_container.h"

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
	void* data_ptr; 		   /* uncommitted pointer to the data item */
};


/* Declaration for Ordered_container. This declaration is local to this file.
A pointer is maintained to the last node in the list as well as the first,
meaning that additions to the end of the list can be made in constant time.
The number of nodes in the list is kept up-to-date in the size member
variable, so that the size of the list can be accessed in constant time. */
struct Ordered_container {
	OC_comp_fp_t comp_func;     /* function to ... */
	struct LL_Node* first;      /* pointer to the first node */
	struct LL_Node* last;       /* pointer to the last node */
	int size;                   /* current size of container */
};



/*
Functions for the entire container.
*/


/*
Functions for working with individual items in the container.
*/


/*
Functions that search and insert into the container using the supplied comparison function.
*/


/*
Functions that traverse the items in the container, processing each item in order.
*/
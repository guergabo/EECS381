/* Test file for generic linked-list version */

/* Reminder Definitions */
/* Incomplete type declaration :: tells the compiler that the named struct exists without implementation */
/* Static :: a variable will be globally known only in this file (limits visibility) */

/* Global :: a variable defined in another file outside a function, access it by using extern */

/* typedef :: keyword to give a certain variation of a type (or function pointer) a new name */
/* Function Pointer ::
* 
	void fun(int a) { printf("Value of a is %d\n", a); }

	int main(){
		// fun_ptr is a pointer to function fun()
		void (*fun_ptr) (int) = fun; // functiona call gives address so no need for &
		
		// invoking fun() using fun_ptr
		(*fun_ptr)(10); // "Value of a is 10" 

		return 0;
	}
*/

/* malloc / free :: casting to before returning */
/* Opaque type :: is a type whose implementation is hidden from the user. Only way to access 
is through a poitner interface exposwed in the API */
/* Pointers to Struct :: simply treat a struct or class as a self-defined type */
/* Void Pointers :: the generic pointer type can be used for any type because it is uncommitted */
/* insertion doubly linked-list :: */

/* Interfaces */
#include "Utility.h"
#include "Ordered_container.h"

/* Libraries */
#include <stdio.h>  /* defines NULL */
#include <stdlib.h> /* standard library, includes malloc/free */


int main() {

	/* test with some string constants - the container items hold their addresses, not the actual strings! */
	char* s1 = "s1";
	char* s2 = "s2";
	char* s3 = "s3";
	char* s4 = "s4";
	char* probe1 = "s3";
	char* probe2 = "s99";

	struct Ordered_container* container;

	/* we can use the function pointer typedefs in Ordered_container.h
	instead of writing out the casts ourselves.
	test : function should create a container. */
	container = OC_create_container(compare_string);

	/*	container = OC_create_container((OC_comp_fp_t)compare_string); 
	test : function should return size of the container as an integer */
	printf("size is %d\n", OC_get_size(container));

	/* test : function should return 1 if the container is empty */
	if (OC_empty(container)) { printf("container is empty.\n");  }

	/* fill the container of s1, s2, s3, s4 but insert in this order: s3, s1, s4, s2,
	and see if the strings get put in the right order. */
	
	OC_insert(container, s1);
	OC_insert(container, s2);
	
	OC_insert(container, s3);
	OC_insert(container, s1);
	OC_insert(container, s4); 
	OC_insert(container, s2);

	OC_insert(container, s1);
	OC_insert(container, s2);

	/* print out order */
	printf("size is %d\n", OC_get_size(container));
	printf("Done\n");

	return 0;
}


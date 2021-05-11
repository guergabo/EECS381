/* Test file for generic linked-list version */

/* Reminder Definitions */
/* Static :: */
/* Gloabl :: */
/* Pointers to Struct :: */
/* Void Pointers :: */
/* Opaque type :: */
/* typedef :: */
/* insertion doubly linked-list :: */

/* Interfaces */
#include "Ordered_container.h"

/* Libraries */
#include <assert.h>
#include <stdio.h>

int main() {
	/* An Ordered_container object is create by the OC_create_container function 
	which returns an opaque struct type */
	struct Ordered_container* rooms_ptr = OC_create_container();
	struct Ordered_container* persons_ptr = OC_create_container(); 

	/* isolate and read the command given  */
	char first_letter, second_letter; 

	while (1) {
		printf("Enter Command: ");
		scanf(" %c", &first_letter);
		scanf(" &c", &second_letter);

		printf("%c %c", first_letter, second_letter);
		if (first_letter == 'q') { return 0;  }
	}

	return 0;
}
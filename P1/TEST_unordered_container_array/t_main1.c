/* test for array implementation */

/* interfaces */
#include "Ordered_container.h"


/* libraries */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Reminder Definitions */
/* C-string ::  
	int strlen(char* s){
		char*p = s; 
		while(*p != '\0')
				++p;
		return p - s; // no +1 because already one pass the end of the string
	}

	char* pmessage;
	pmessage = "now is the time"; 

	char arr[] = "now is the time" // can modify 
	char* ptr = arr; 
	while((*ptr) != '\0'){
		*ptr = 'a'; // can modify
	}

	char* ptr = "now is the time" // string literal is read-only and cannot be modified. 

*/
/* C-style arrays :: "contiguous memory" 
	f(int arr[]) == f(int* arr) 

*/

int demo_function(const void* data_ptr1, const void* data_ptr2);

int main(void) {
	/* create container with array implementation */
	struct Ordered_container* container = OC_create_container(demo_function);

	if(container)
		printf("%p", &container);

	return 0; 
}

int demo_function(const void* data_ptr1, const void* data_ptr2) {
	return strcmp((char*)data_ptr1, (char*)data_ptr2);
}
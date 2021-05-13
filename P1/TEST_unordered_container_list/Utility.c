#include "Utility.h"

#include <stdio.h>
#include <stdlib.h> /* standard library, includes malloc/free */
#include <string.h> /* contains compare strings function strcmp */

/* compares strings, returns 0 if equal, less than 0 if the 
first is less than second, and greater than 0 if first is greater second */
int compare_string(const void* data_ptr1, const void* data_ptr2) {
	return strcmp(data_ptr1, data_ptr2);
}

/* safe malloc function */
void* safe_malloc(int bytes) {
	void* dynamic_memory = (void*) malloc(bytes);
	if (!dynamic_memory) {
		printf("Memory allocation error. Could not allcoate %d bytes of memory", bytes);
		exit(0); 
	}
	return dynamic_memory;
}

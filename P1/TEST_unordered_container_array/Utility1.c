#include "Utility1.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* safe malloc*/
void* safe_malloc(int bytes) {
	void* dynamic_memory = (void*) malloc(bytes);
	if (!dynamic_memory) {
		printf("Memory allocation error. Could not allcoate %d bytes of memory", bytes);
		exit(0);
	}
	return dynamic_memory;
}
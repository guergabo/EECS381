#include "Utility.h"
#include "Person.h"

#include <stdio.h>
#include <stdlib.h> /* standard library, includes malloc/free */
#include <string.h> /* contains compare strings function strcmp */

/* compares strings, returns 0 if equal, less than 0 if the
first is less than second, and greater than 0 if first is greater second */
int compare_string(const void* data_ptr1, const void* data_ptr2) {
	return strcmp((char*)data_ptr1, (char*)data_ptr2);
}

/* safe malloc function */
void* safe_malloc(int bytes) {
	void* dynamic_memory = (void*)malloc(bytes);
	if (!dynamic_memory) {
		printf("Memory allocation error. Could not allcoate %d bytes of memory", bytes);
		exit(0);
	}
	return dynamic_memory;
}

/* safe malloc for characters, make sure it is casted to char* */
char* alloc_char(int bytes) {
	char* dynamic_memory = (char*) safe_malloc(bytes);
	/* potential global for string memory */
	return dynamic_memory; 
}

/* safe malloc for characters, make sure it is casted to char* */
struct Ordered_container* alloc_container(int bytes) {
	struct Ordered_container* dynamic_memory = (struct Ordered_container*)safe_malloc(bytes);
	return dynamic_memory;
}

/* comparison function for Person using their lastnames */
int comp_func_person(const void* person_ptr1, const void* person_ptr2) {
	return strcmp(get_Person_lastname((struct Person*) person_ptr1), 
				  get_Person_lastname((struct Person*) person_ptr2));
}

/* comparison function to find Person with last name */
int comp_func_person_arg(const void* lastname, const void* person_ptr2) {
	return strcmp((char*) lastname,
		get_Person_lastname((struct Person*)person_ptr2));
}
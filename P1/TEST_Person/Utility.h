#ifndef UTILITY_H
#define UTILITY_H

#include "Person.h"

#include <string.h>

/* compare function for Rooms */
int compare_string(const void* data_ptr1, const void* data_ptr2);

/* safe malloc function */
void* safe_malloc(int bytes);

/* comparison function for Person */
int comp_func_person(const void* person_ptr1, const void* person_ptr2);

#endif
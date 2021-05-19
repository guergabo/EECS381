#ifndef UTILITY_H
#define UTILITY_H

#include <string.h>

/* incomplete declarations */
struct Ordered_container;

/* compare function for Rooms */
int compare_string(const void* data_ptr1, const void* data_ptr2);

/* safe malloc function */
void* safe_malloc(int bytes);

/* safe malloc for characters, make sure it is casted to char* */
char* alloc_char(int bytes);

/* safe malloc for characters, make sure it is casted to char* */
struct Ordered_container* alloc_container(int bytes);

/* comparison function for Person */
int comp_func_person(const void* person_ptr1, const void* person_ptr2);

/* comparison function to find Person with last name */
int comp_func_person_arg(const void* lastname, const void* person_ptr2);

#endif
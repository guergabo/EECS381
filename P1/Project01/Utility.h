#ifndef UTILITY_H
#define UTILITY_H

#include <string.h>


/* number of bytes used in C-strings */
extern int g_string_memory;

/* incomplete declarations */
struct Ordered_container;

/* safe malloc function */
void* safe_malloc(int bytes);

/* safe malloc for characters, make sure it is casted to char* */
char* alloc_char(int bytes);

/* safe malloc for characters, make sure it is casted to char */
char* free_char(char* char_ptr);

/* safe malloc for characters, make sure it is casted to char* */
struct Ordered_container* alloc_container(int bytes);

/* comparison function for Person */
int comp_func_person(const void* person_ptr1, const void* person_ptr2);

/* comparison function to find Person with last name */
int comp_func_person_arg(const void* lastname, const void* person_ptr2);

/* comparison function for Room */
int comp_func_room(const void* room_ptr1, const void* room_ptr2);

/* comparison function to find Room with number */
int comp_func_room_arg(const void* room_ptr1, const void* room_ptr2);

/* comparison function to organize Meetings */
int comp_func_meeting(const void* meeting_ptr1, const void* meeting_ptr2);

/* comparison function to find Meeting with a certain time */
int comp_func_meeting_arg(const void* time, const void* meeting_ptr2);


#endif
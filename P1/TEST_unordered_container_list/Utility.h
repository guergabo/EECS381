#ifndef UTILITY_H
#define UTILITY_H

/* compare function for Rooms */
int compare_string(const void* data_ptr1, const void* data_ptr2);

/* safe malloc function */
void* safe_malloc(int bytes);

#endif
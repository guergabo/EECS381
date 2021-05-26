/* Utility.c, implementation file for Utility functionality */

/* interfaces */
#include "Utility.h"
#include "Person.h"
#include "Meeting.h"
#include "Room.h"

/* libraries */
#include <stdio.h>
#include <stdlib.h> /* standard library, includes malloc/free */
#include <string.h> /* contains compare strings function strcmp */

/* number of bytes used in C-strings */
int g_string_memory = 0;

/* safe malloc function */
void* safe_malloc(int bytes) {
	void* dynamic_memory = malloc(bytes);
	if (!dynamic_memory) {
		printf("Memory allocation error. Could not allcoate %d bytes of memory", bytes);
		exit(0);
	}
	return dynamic_memory;
}

/* safe malloc for characters, make sure it is casted to char* */
char* alloc_char(int bytes) {
	char* dynamic_memory = safe_malloc(bytes);
	/* global for string memory */
	g_string_memory += bytes;

	return dynamic_memory;
}

/* safe malloc for characters, make sure it is casted to char */
void free_char(char* char_ptr) {
	g_string_memory -= (strlen(char_ptr) + 1);
	free(char_ptr);
}


/* safe malloc for characters, make sure it is casted to char* */
struct Ordered_container* alloc_container(int bytes) {
	struct Ordered_container* dynamic_memory = (struct Ordered_container*)safe_malloc(bytes);
	return dynamic_memory;
}

/* comparison function for Person using their lastnames */
int comp_func_person(const void* person_ptr1, const void* person_ptr2) {
	return strcmp(get_Person_lastname((struct Person*)person_ptr1),
		get_Person_lastname((struct Person*)person_ptr2));
}

/* comparison function to find Person with last name */
int comp_func_person_arg(const void* lastname, const void* person_ptr2) {
	return strcmp((char*)lastname,
		get_Person_lastname((struct Person*)person_ptr2));
}

/* comparison function for Room */
int comp_func_room(const void* room_ptr1, const void* room_ptr2) {
	/* incomplete declaration so have to call function */
	/* if equal will  return 0, if first is greater will return positive,
	if first is less will return negative */
	return get_Room_number((struct Room*)room_ptr1) -
		get_Room_number((struct Room*)room_ptr2);
}

/* comparison function to find Room with number */
int comp_func_room_arg(const void* room_number_ptr, const void* room_ptr) {
	return *((int*)room_number_ptr) - get_Room_number((struct Room*)room_ptr);
}

/* normalizing the time for meeting */
void normalize_time(int* time_1, int* time_2) {
	if (*time_1 < 6) { (*time_1) += 12; }
	if (*time_2 < 6) { (*time_2) += 12; }
}

/* comparison function to organize Meetings */
int comp_func_meeting(const void* meeting_ptr1, const void* meeting_ptr2) {
	int time_1 = get_Meeting_time((const struct Meeting*)meeting_ptr1);
	int time_2 = get_Meeting_time((const struct Meeting*)meeting_ptr2);
	/* normalize time to military time */
	normalize_time(&time_1, &time_2);
	return (time_1 - time_2);
}

/* comparison function to find Meeting with a certain time */
int comp_func_meeting_arg(const void* time, const void* meeting_ptr2) {
	int time_1 = *(int*)time;
	int time_2 = get_Meeting_time((const struct Meeting*)meeting_ptr2);
	normalize_time(&time_1, &time_2);
	return (time_1 - time_2);
}
/* skeleton file for Room.c
The struct declaration below must be used for Room objects.
Remove this comment and complete this file with all necessary code.
*/


#include "Utility.h"
#include "Ordered_container.h"
#include "Meeting.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* a Room contains a container of meetings and a room number */
struct Room {
	struct Ordered_container* meetings;	/* a container of pointers to Meeting objects */
	int number;
};

/* Create a Room object.
This is the only function that allocates memory for a Room
and the contained data. */
struct Room* create_Room(int number) {
	struct Room* room_ptr = (struct Room*)safe_malloc(sizeof(struct Room));
	room_ptr->meetings = OC_create_container(comp_func_meeting);
	room_ptr->number = number; 
	return room_ptr; 
}

/* Destroy a Room object.
This is the only function that frees the memory for a Room
and the contained data. The Meetings are destroyed before the
Meeting list is emptied. */
void destroy_Room(struct Room* room_ptr) {
	OC_destroy_container(room_ptr->meetings);
	free(room_ptr);
}

/* Return the room number. */
int  get_Room_number(const struct Room* room_ptr) {
	return room_ptr->number; 
}

/* Add the meeting to the room, return non-zero if a meeting already at that time, 0 if OK. */
int add_Room_Meeting(struct Room* room_ptr, const struct Meeting* meeting_ptr) {
	void* item_ptr;
	/* check if there is a meeting already at that time */
	int meeting_time = get_Meeting_time(meeting_ptr);
	item_ptr = OC_find_item_arg(room_ptr->meetings, &meeting_time, comp_func_meeting_arg);
	if (item_ptr) { return 0; }
	/* add meeting to the room */
	OC_insert(room_ptr->meetings, meeting_ptr);
	return 1; 
}

/* Return a pointer to the meeting at the specified time, NULL if not present. */
struct Meeting* find_Room_Meeting(const struct Room* room_ptr, int time) {
	const void* item_ptr; 
	item_ptr = OC_find_item_arg(room_ptr->meetings, &time, comp_func_meeting_arg);
	if (item_ptr) { return (struct Meeting*)(OC_get_data_ptr(item_ptr)); }
	return NULL; 
}

/* Remove the supplied meeting from the room; return non-zero if not there; 0 if OK.
The meeting is not destroyed because we may need to place it into another room. */
int remove_Room_Meeting(struct Room* room_ptr, const struct Meeting* meeting_ptr) {


	/* DOUBLE CHECK MEANING */
	const void* item_ptr; 
	item_ptr = OC_find_item(room_ptr->meetings, meeting_ptr);
	if (item_ptr) { OC_delete_item(room_ptr->meetings, item_ptr); return  0; }
	/* not there */
	return 1; 
	/* DOUBLE CHECK MEANING */

}

/* Clear and destroy the Meetings in a Room.
This function destroys each meeting and leaves the Room empty of meetings. */
void clear_Room(struct Room* room_ptr) {

}

/* Return a pointer to the const container of meetings for read-only iterations over the meetings. */
const struct Ordered_container* get_Room_Meetings(const struct Room* room_ptr) {

}

/* Print the data in a struct Room. */
void print_Room(const struct Room* room_ptr) {

}

/* Write the room data to a file. */
void save_Room(const struct Room* room_ptr, FILE* outfile) {
	return; 
}

/* Read a room's data from a file stream, create the data object and
return a pointer to it, NULL if invalid data discovered in file.
No check made for whether the room already exists or not. */
struct Room* load_Room(FILE* infile, const struct Ordered_container* people) {
	return NULL;
}
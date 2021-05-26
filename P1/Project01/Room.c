/* Room.c, implementation file for Room object and functionality */

/* allows me to use normal scanf, strcpy not scanf_s, etc. */
#pragma warning(disable : 4996)

/* interfaces */
#include "Utility.h"
#include "Ordered_container.h"
#include "Meeting.h"
#include "Room.h"

/* libraries */
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
void destroy_Meeting_helper(void* meeting_ptr);

void destroy_Room(struct Room* room_ptr) {
	/* a meeting cannot exist outside the room */
	OC_apply(room_ptr->meetings, destroy_Meeting_helper);
	OC_clear(room_ptr->meetings); /* for the nodes would be helpful */
	OC_destroy_container(room_ptr->meetings);
	free(room_ptr);
}

/* Return the room number. */
int get_Room_number(const struct Room* room_ptr) {
	return room_ptr->number;
}

/* Add the meeting to the room, return non-zero if a meeting already at that time, 0 if OK. */
int add_Room_Meeting(struct Room* room_ptr, const struct Meeting* meeting_ptr) {
	void* item_ptr;
	/* check if there is a meeting already at that time */
	int meeting_time = get_Meeting_time(meeting_ptr);
	item_ptr = OC_find_item_arg(room_ptr->meetings, &meeting_time, comp_func_meeting_arg);
	if (item_ptr) { return 1; }
	/* add meeting to the room */
	OC_insert(room_ptr->meetings, (void*)meeting_ptr);
	return 0;
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
	void* item_ptr;
	item_ptr = OC_find_item(room_ptr->meetings, meeting_ptr);
	if (item_ptr) { OC_delete_item(room_ptr->meetings, item_ptr); return  0; }
	/* not there */
	return 1;
}

/* Clear and destroy the Meetings in a Room.
This function destroys each meeting and leaves the Room empty of meetings. */
void destroy_Meeting_helper(void* meeting_ptr) {
	destroy_Meeting((struct Meeting*)meeting_ptr);
}

void clear_Room(struct Room* room_ptr) {
	/* a meeting cannot exist outside the room */
	OC_apply(room_ptr->meetings, destroy_Meeting_helper);
	/* clear container inside room */
	OC_clear(room_ptr->meetings);
}

/* Return a pointer to the const container of meetings for read-only iterations over the meetings. */
const struct Ordered_container* get_Room_Meetings(const struct Room* room_ptr) {
	/* for READ ONLY iterations over the meetings */
	return room_ptr->meetings;
}

/* Print the data in a struct Room. */
void print_meetings_helper(const void* data_ptr) {
	print_Meeting((struct Meeting*)data_ptr);
}

void print_Room(const struct Room* room_ptr) {
	printf("--- Room %d ---\n", room_ptr->number);
	if (OC_get_size(room_ptr->meetings) == 0)
		printf("No meetings are scheduled\n");
	else
		OC_apply(room_ptr->meetings, (OC_apply_fp_t)print_meetings_helper);
}

void save_room_helper(void* meeting_ptr, void* file_ptr) {
	save_Meeting((const struct Meeting*)meeting_ptr, (FILE*)file_ptr);
}

/* Write the room data to a file. */
void save_Room(const struct Room* room_ptr, FILE* outfile) {
	/* room number and number of meetings */
	fprintf(outfile, "%d %d\n", room_ptr->number, OC_get_size(room_ptr->meetings));
	/* each meeting in the room, time, topic, number of participants */
	OC_apply_arg(room_ptr->meetings, save_room_helper, (void*)outfile);
}

/* Read a room's data from a file stream, create the data object and
return a pointer to it, NULL if invalid data discovered in file.
No check made for whether the room already exists or not. */
struct Room* load_Room(FILE* infile, const struct Ordered_container* people) {
	struct Room* room_ptr; 
	int temp_number;
	int temp_num_of_meetings;

	if (!(fscanf(infile, "%d %d\n", &temp_number, &temp_num_of_meetings))) { return NULL; }

	/* create meetings and participants for the room */
	room_ptr = create_Room(temp_number);
	/* add all the meetings in the room */
	while (temp_num_of_meetings-- !=  0) {
		struct Meeting* meeting_ptr = load_Meeting(infile, people);
		if (!meeting_ptr) {
			destroy_Room(room_ptr);
			return NULL;
		}
		add_Room_Meeting(room_ptr, meeting_ptr);
	}
	return room_ptr; 
}
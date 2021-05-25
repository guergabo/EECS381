/* Meeting.c */

#pragma warning(disable : 4996)

#include "Utility.h"
#include "Ordered_container.h"
#include "Person.h"
#include "Meeting.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* a Meeting contains a time, a topic, and a container of participants */
struct Meeting {
	char* topic;
	int time;
	struct Ordered_container* participants;	/* a container of pointers to struct Person objects */
};


/* global variable declarations for this module */
int g_Meeting_memory;			/* number of meeting structs currently allocated */


/* Create a Meeting object.
This is the only function that allocates memory for a Meeting
and the contained data. The supplied time is assumed to be in 12-hr form. */
struct Meeting* create_Meeting(int time, const char* topic) {
	/* allocate */
	struct Meeting* meeting_ptr = (struct Meeting*)safe_malloc(sizeof(struct Meeting));
	meeting_ptr->topic = alloc_char(strlen(topic) + 1);
	meeting_ptr->participants = OC_create_container(comp_func_person);
	/* initialize and return */
	meeting_ptr->time = time;
	strcpy(meeting_ptr->topic, topic);
	/* update global count of Meetings container */
	++g_Meeting_memory;

	return meeting_ptr;
}

/* Destroy a Meeting object.
This is the only function that frees the memory for a Meeting
and the contained data. It discards the participant list,
but of course does not delete the Persons themselves. */
void destroy_Meeting(struct Meeting* meeting_ptr) {
	/* free items */
	OC_destroy_container(meeting_ptr->participants);
	free_char(meeting_ptr->topic);
	/* free containers */
	free(meeting_ptr);
	--g_Meeting_memory;
}

/* Return and set the meeting time. The time value is assumed to be in 12-hr form.*/
int get_Meeting_time(const struct Meeting* meeting_ptr) {
	return meeting_ptr->time;
}

void set_Meeting_time(struct Meeting* meeting_ptr, int time) {
	meeting_ptr->time = time;
}

/* Add a participant; return non-zero and do nothing if already present. */
int add_Meeting_participant(struct Meeting* meeting_ptr, const struct Person* person_ptr) {
	/* check if person already a participant */
	if ((is_Meeting_participant_present(meeting_ptr, person_ptr))) { return 1; }
	OC_insert(meeting_ptr->participants, (void*)person_ptr);
	return 0;
}

/* Return non-zero if the person is a participant, zero if not. */
int is_Meeting_participant_present(const struct Meeting* meeting_ptr, const struct Person* person_ptr) {
	void* item_ptr = OC_find_item(meeting_ptr->participants, person_ptr);
	return (item_ptr) ? 1 : 0;
}

/* Remove a participant; return non-zero if not present, zero if was present. */
int remove_Meeting_participant(struct Meeting* meeting_ptr, const struct Person* person_ptr) {
	/* check if person is even a participant */
	if (!(is_Meeting_participant_present(meeting_ptr, person_ptr))) { return 1; }
	/* find item that holds that person */
	void* item_ptr = OC_find_item(meeting_ptr->participants, person_ptr);
	OC_delete_item(meeting_ptr->participants, item_ptr);
	return 0;
}

/* Print the data in a struct Meeting. The time is expressed in 12-hr form with no AM/PM.*/
void print_participants_helper(void* data_ptr) {
	print_Person((struct Person*)data_ptr);
}

void print_Meeting(const struct Meeting* meeting_ptr) {
	printf("Meeting time: %d, Topic: %s\n", meeting_ptr->time, meeting_ptr->topic);
	/* participants */
	if (OC_get_size(meeting_ptr->participants) == 0) { printf("Participants: None\n"); return; }
	/* print out the participants */
	printf("Participants:\n");
	OC_apply(meeting_ptr->participants, (OC_apply_fp_t)print_participants_helper);
}

/* Write the data in a Meeting to a file. The time is expressed in 12-hr form with no AM/PM.*/
void save_Meeting(const struct Meeting* meeting_ptr, FILE* outfile) {
	return;
}

/* Read a Meeting's data from a file stream, create the data object and
return a pointer to it, NULL if invalid data discovered in file.
No check made for whether the Meeting already exists or not. The time is expressed in 12-hr form with no AM/PM.*/
struct Meeting* load_Meeting(FILE* input_file, const struct Ordered_container* people) {
	return NULL;
}
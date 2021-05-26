/* C Program for Project 1, Micro Meeting Manager, EECS 381 */

/* allows me to use normal scanf, strcpy not scanf_s, etc. */
#pragma warning(disable : 4996)

/* interfaces */
#include "Utility.h"
#include "Ordered_container.h"
#include "Person.h"
#include "Meeting.h"
#include "Room.h"

/* libraries */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

/* user defined data type. Assign names / states to integral constants */
typedef enum {
	BAD_COMMAND, READ_NO_INT, ROOM_OUT_OF_RANGE, ROOM_ALREADY_EXISTS,
	PERSON_ALREADY_EXISTS, NO_PERSON, ROOM_DOESNT_EXIST, MEETING_ALREADY_EXIST,
	TIME_OUT_OF_RANGE, MEETING_DOESNT_EXIST, ALREADY_PARTICIPANT, NOT_PARTICIPANT,
	SAME_MEETING, IS_PARTICIPANT, MEETINGS_EXIST, CANT_OPEN_FILE, INVALID_DATA
} Error_c;

/* function prototypes */
/* add functions */
void add_individual(struct Ordered_container* person_list);
void add_room(struct Ordered_container* room_list);
void add_meeting(struct Ordered_container* room_list);
void add_person_to_meeting(struct Ordered_container* person_list, struct Ordered_container* room_list);

/* print functions */
void print_individual(const struct Ordered_container* person_list);
void print_room(const struct Ordered_container* room_list);
void print_meeting(const struct Ordered_container* room_list);
void print_all_meetings(const struct Ordered_container* room_list);
void print_all_individuals(const struct Ordered_container* person_list);
void print_memory(const struct Ordered_container* person_list, const struct Ordered_container* room_list);

/* reschedule functions */
void reschedule_meeting(struct Ordered_container* room_list);

/* delete functions */
void delete_individual(struct Ordered_container* person_list, struct Ordered_container* room_list);
void delete_room(struct Ordered_container* room_list);
void delete_meeting(struct Ordered_container* room_list);
void delete_person_from_meeting(struct Ordered_container* person_list, struct Ordered_container* room_list); 
void delete_all_rooms_and_meetings(struct Ordered_container* room_list);
void delete_all_meetings(struct Ordered_container* room_list); 
void delete_all_individuals(struct Ordered_container* person_list); 
void delete_all(struct Ordered_container* person_list, struct Ordered_container* room_list); 
void quit(struct Ordered_container* person_list, struct Ordered_container* room_list);

/* save data functions */
void save_data(const struct Ordered_container* person_list, const struct Ordered_container* room_list);

/* load data functions */
void load_data(struct Ordered_container* person_list, struct Ordered_container* room_list);

/* person helper functions */
void print_all_helper(void* data_ptr);
void delete_all_individuals_helper(void* data_ptr);
struct Person* find_if_person_exists(const struct Ordered_container* person_list, char* lastname);
void read_person(char* firstname, char* lastname, char* phoneno);
void read_person_lastname(char* lastname);
struct Person* read_and_find_person(const struct Ordered_container* person_list);
int is_person_in_meeting(void* meeting_ptr, void* person_ptr);
int is_person_room(void* room_ptr, void* person_ptr);

/* room helper functions */
int validate_room_number(int* room_number);
int read_room_number(int* room_number);
int read_room(int* room_number);
void* find_if_room_exists(const struct Ordered_container* room_list, const void* room_number);
struct Room* read_and_find_room(const struct Ordered_container* room_list);
void delete_all_rooms_helper(void* data_ptr);

/* meeting helper functions */
int validate_meeting_time(int* meeting_time);
int read_meeting_time(int* meeting_time);
int read_meeting_time_and_validate(int* meeting_time);
int read_meeting_topic(char* meeting_topic);
int read_meeting(int* meeting_time, char* meeting_topic);
struct Meeting* read_and_find_meeting(const struct Ordered_container* room_list);
struct Meeting* read_and_find_meeting_and_room(const struct Ordered_container* room_list, struct Room** room_ptr);
void print_all_meetings_helper(void* data_ptr);
void delete_all_meetings_helper(void* room_ptr);
void reschedule_helper(struct Meeting* meeting_ptr_1, struct Room* room_ptr_1, struct Room* room_ptr_2, int new_meeting_time);

/* save data helper functions */
void save_person_wrapper(void* person_ptr, void* file_ptr);
void save_room_wrapper(void* room_ptr, void* file_ptr);
void read_file_name(char* file_name);
void save_data_helper(const struct Ordered_container* person_list, const struct Ordered_container* room_list, FILE* file_ptr);

/* load data helper functions */
void delete_all_clean(struct Ordered_container* person_list, struct Ordered_container* room_list);
void print_error_and_discard(struct Ordered_container* person_list, struct Ordered_container* room_list);
int load_persons(FILE* file_ptr, struct Ordered_container* person_list);
int load_rooms(FILE* file_ptr, struct Ordered_container* person_list, struct Ordered_container* room_list);

/* error handling functions */
void print_error_and_clear(Error_c error);

int main() {
	/* containers */
	struct Ordered_container* person_list = OC_create_container(comp_func_person);
	struct Ordered_container* room_list = OC_create_container(comp_func_room);
	/* two character commands define program behavior */
	char command_one;
	char command_two;
	/* main behavior loop */
	while (1) {
		/* read the two command characters */
		printf("\nEnter command: ");
		/* the space tells scanf to first skip any number of
		whitespace characters, and then the %c will match the
		first non-whitespace character. */
		int s1 = scanf(" %c", &command_one);
		int s2 = scanf(" %c", &command_two);
		switch (command_one) {
		case 'a':
			switch (command_two) {
			case 'i':
				/* (add) individual command */
				add_individual(person_list);  
				break;
			case 'r':
				/* (add) room command */
				add_room(room_list);
				break;
			case 'm':
				/* (add) meeting command */
				add_meeting(room_list); 
				break;
			case 'p':
				/* (add) person to meeting command */
				add_person_to_meeting(person_list, room_list);
				break;
			default:
				print_error_and_clear(BAD_COMMAND);
				break;
			}
			/* break from command_one */
			break;
		case 'p':
			switch (command_two) {
			case 'i':
				/* (print) individual command */
				print_individual(person_list);
				break;
			case 'g':
				/* (print) all individuals command */
				print_all_individuals(person_list); 
				break;
			case 'r':
				/* (print) room command */
				print_room(room_list);
				break;
			case 'm':
				/* (print) meeting command */
				print_meeting(room_list);
				break;
			case 's':
				/* (print) all meetings commands */
				print_all_meetings(room_list);
				break;
			case 'a':
				/* (print) memory allocations command */
				print_memory(person_list, room_list);
				break;
			default:
				print_error_and_clear(BAD_COMMAND);
				break;
			}
			/* break from command_one */
			break;
		case 'r':
			switch (command_two) {
			case 'm':
				/* (reschedule) meeting command */
				reschedule_meeting(room_list);
				break;
			default:
				break;
			}
			/* break from command_one */
			break;
		case 'd':
			switch (command_two) {
			case 'i':
				/* (delete) individual command */
				delete_individual(person_list, room_list);
				break;
			case 'g':
				/* (delete) all individuals command */
				delete_all_individuals(person_list);
				break;
			case 'r':
				/* (delete) room command */
				delete_room(room_list);
				break;
			case 'a':
				/* (delete) all command */
				delete_all(person_list, room_list);
				break;
			case 'm':
				/* (delete) meeting command */
				delete_meeting(room_list);
				break;
			case 'p':
				/* (delete) participant from meeting command */
				delete_person_from_meeting(person_list, room_list);
				break;
			case 's':
				/* (delete) schedule command */
				delete_all_meetings(room_list);
				break;
			default:
				print_error_and_clear(BAD_COMMAND);
				break;
			}
			/* break from command_one */
			break;
		case 's':
			switch (command_two) {
			case 'd':
				/* (save) data command */
				save_data(person_list, room_list);
				break;
			}
			/* break from command_one */
			break;
		case 'l':
			switch (command_two) {
			case 'd':
				/* (load) data command */
				load_data(person_list, room_list);
				break;
			}
			/* break from command_one */
			break;
		case 'q':
			quit(person_list, room_list); 
			return 0;
		default:
			print_error_and_clear(BAD_COMMAND);
			break;
		}
	}

	return 0;
}

/*
add functions
*/
/* ai <firstname> <lastname> <phoneno> : add an individual person to the people list. Errors : a person
with that last name is already in the people list. */
void add_individual(struct Ordered_container* person_list) {
	struct Person* person_ptr;
	char firstname[NAME_BUFFER_SIZE]; char lastname[NAME_BUFFER_SIZE]; char phoneno[PHONE_BUFFER_SIZE];
	/* read input information for person */
	read_person(firstname, lastname, phoneno);
	/* check if the person already exist with the same lastname */
	if (!(person_ptr = find_if_person_exists(person_list, lastname))) { 
		/* dynamically allcate and insert Person to the list*/
		person_ptr = create_Person(firstname, lastname, phoneno);
		OC_insert(person_list, (void*)person_ptr);                              
		printf("Person %s added\n", &lastname);
		return;
	}
	print_error_and_clear(PERSON_ALREADY_EXISTS);
}

/* ar <room> : add a room with the specified number. Errors room number out of range; room of that
number already exists. */
void add_room(struct Ordered_container* room_list) {
	struct Room* room_ptr; 
	int room_number; 
	/* read input information for room */
	if (!read_room(&room_number)) { return; }
	/* check if room number does not already exist */
	else if (find_if_room_exists(room_list, (const void*)&room_number)) {
		print_error_and_clear(ROOM_ALREADY_EXISTS);
		return; 
	}
	/* if it does not exist add */
	room_ptr = create_Room(room_number);
	OC_insert(room_list, (void*)room_ptr);
	printf("Room %d added\n", room_number);
}

/* am <room> <time> <topic> : add a meeting in a specified room, at a specified time, 
and on a specified topic. Errors : room number out of range; no room number; time 
out of range; a meeting at that time already exists in that room. */
void add_meeting(struct Ordered_container* room_list) {
	struct Room* room_ptr;
	struct Meeting* meeting_ptr;
	int meeting_time ; 
	char meeting_topic[TOPIC_BUFFER_SIZE];
	/* can't add a meeting to a room that does not exist */
	if (!(room_ptr = read_and_find_room(room_list))) { return; }
	/* no meeting has to return and time has to be read in properly and changed */
	else if (!(read_meeting(&meeting_time, meeting_topic))) { return; }
	else if (!(meeting_ptr = find_Room_Meeting(room_ptr, meeting_time))) { 
		/* create meeting */
		meeting_ptr = create_Meeting(meeting_time, meeting_topic);
		/* insert meeting */
		add_Room_Meeting(room_ptr, meeting_ptr);
		/* notification */
		printf("Meeting added at %d\n", meeting_time);
		return;
	}
	print_error_and_clear(MEETING_ALREADY_EXIST);
}

/* ap <room> <time> <lastname> � add a specified person as a participant in a specified meeting. 
Errors: room number out of range; no room of that number; time out of range, no meeting at that 
time, no person in the people list of that name; there is already a participant of that name.*/
void add_person_to_meeting(struct Ordered_container* person_list, struct Ordered_container* room_list) {
	struct Room* room_ptr;
	struct Meeting* meeting_ptr; 
	struct Person* person_ptr;
	/* check if room exists and info is correct */
	/* check if meeting with that time in that room exists and valid */
	if (!(meeting_ptr = read_and_find_meeting_and_room(room_list, &room_ptr))) { return; }
	/* check if person in the people list */
	else if (!(person_ptr = read_and_find_person(person_list))) { return; }
	/* check if person is not already a participant */
	else if (!is_Meeting_participant_present(meeting_ptr, person_ptr)) {
		/* add person as a participant */
		add_Meeting_participant(meeting_ptr, person_ptr);
		printf("Participant %s added\n", get_Person_lastname(person_ptr));
		return;
	}
	print_error_and_clear(ALREADY_PARTICIPANT);
}

/* rm <old room> <old time> <new room> <new time> � reschedule a meeting by changing its 
room and/or time (without changing or reentering topic or participants). Each parameter 
is read and its value checked before going on to the next parameter. Actually changing 
the schedule is not done until all parameters have been read and checked. Errors: old room
number out of range; old room does not exist; old time is out of range; no meeting at that 
time in the old room; new room number out of range, new room does not exist; new time is 
out of range; a meeting at the new time already exists in the new room. To keep the logic 
simple, the last error will result if the user attempts to reschedule a meeting to be in 
the same room and at the same time as it is currently. */
void reschedule_meeting(struct Ordered_container* room_list) {
	struct Room* room_ptr_1;
	struct Room* room_ptr_2;
	struct Meeting* meeting_ptr_1;
	struct Meeting* meeting_ptr_2;
	int new_meeting_time = INT_MIN;

	/* check if old meeting with that time in that room exists and valid */
	if (!(meeting_ptr_1 = read_and_find_meeting_and_room(room_list, &room_ptr_1))) { return; }
	/* read and find new room */
	if (!(room_ptr_2 = read_and_find_room(room_list))) { return; }
	else if (!(read_meeting_time_and_validate(&new_meeting_time))) { return; }
	/* check if new meeting with that time already exists, save new time */
	else if (meeting_ptr_2 = find_Room_Meeting(room_ptr_2, new_meeting_time)) {
		/* check if it is the same meeting first */
		if (meeting_ptr_1 == meeting_ptr_2) {
			/* different error */
			print_error_and_clear(SAME_MEETING);
			return; 
		}
		print_error_and_clear(MEETING_ALREADY_EXIST);
		return; 
	}
	/* change room and/or time */
	reschedule_helper(meeting_ptr_1, room_ptr_1, room_ptr_2, new_meeting_time);
	printf("Meeting rescheduled to room %d at %d\n", get_Room_number(room_ptr_2), new_meeting_time);
}

/*
print functions
*/
/* pi <lastname> : print the specified individual information. Errors : no person with that last name. */
void print_individual(const struct Ordered_container* person_list) {
	struct Person* person_ptr;
	/* search for full info on Person with that lastname */
	if ((person_ptr = read_and_find_person(person_list)))
		print_Person(person_ptr);
}

/* pr <room> � print the meetings in a room with the specified number. Errors: room number out of
range; no room of that number. */
void print_room(const struct Ordered_container* room_list) {
	struct Room* room_ptr;
	/* read input information for rooom and find room */
	if (room_ptr = read_and_find_room(room_list))
		print_Room((const struct Room*)room_ptr);
}

/* pm <room> <time> � print the time, topic, and participants (full name and phone number) for
a specified meeting. Errors: room number out of range; no room of that number; time out of range
, no meeting at that time. */
void print_meeting(const struct Ordered_container* room_list) {
	struct Meeting* meeting_ptr;
	/* read input information for meeting and find meeting */
	if (meeting_ptr = read_and_find_meeting(room_list))
		print_Meeting(meeting_ptr);
}

/* ps � print the meeting information (same information as pm) for all meetings in all rooms. 
Errors: none. (It is not an error if there are no meetings � that is a valid possibility.)*/
void print_all_meetings(const struct Ordered_container* room_list) {
	/* no rooms */
	if (OC_empty(room_list)) { printf("List of rooms is empty\n"); return; }
	/* rooms  */
	printf("Information for %d rooms:\n", OC_get_size(room_list));
	OC_apply(room_list, (OC_apply_fp_t)print_all_meetings_helper);
}

/* pg : print the individual information (same information as pi) for all people in the person list.
Errors : none. (It is not an error if there are no people -- that is a valid possibility. */
void print_all_individuals(const struct Ordered_container* person_list) {
	/* check if size if zero */
	if (OC_empty(person_list)) { printf("%s\n", "List of people is empty"); return; }    
	/* if not empty, loop and apply print_Person function to data_ptr */
	printf("Information for %d people:\n", OC_get_size(person_list));
	OC_apply(person_list, (OC_apply_fp_t)print_all_helper);                                 
}

/* pa � print memory allocations (described below). Errors: none. In this project, the command 
provides more detailed information about the amount of memory allocated than in Project 0. */
void print_memory(const struct Ordered_container* person_list,
			      const struct Ordered_container* room_list) {
	printf("Memory allocations:\n");
	/* Person = 3x, Meeting = 1x, Room = 0x */
	printf("C-string: %d bytes total\n", g_string_memory);
	printf("Person structs: %d\n", OC_get_size(person_list));
	printf("Meeting structs: %d\n", g_Meeting_memory);
	printf("Room structs: %d\n", OC_get_size(room_list));
	printf("Containers: %d\n", g_Container_count);
	printf("Container items in use: %d\n", g_Container_items_in_use);
	printf("Container items allocated: %d\n", g_Container_items_allocated);
}

/*
delete functions
*/
/* di <lastname> : delete a person from the people list but only if he or she is not a participant
ina  meeting. Erros : No person of that name; person is a participant in a meeting. */
void delete_individual(struct Ordered_container* person_list, 
	struct Ordered_container* room_list) {
	struct Person* person_ptr; void* item_ptr;
	/* search if person with the lastname exists */
	if (!(person_ptr = read_and_find_person(person_list))) { return; }
	/* check if persons is a participant */
	else if (OC_apply_if_arg(room_list, is_person_room, person_ptr)) {
		print_error_and_clear(IS_PARTICIPANT);
		return;
	}
	/* delete cell / node that points to the individual */
	item_ptr = OC_find_item(person_list, person_ptr);
	OC_delete_item(person_list, item_ptr);
	/* destroy person */
	printf("Person %s deleted\n", get_Person_lastname(person_ptr));
	destroy_Person(person_ptr);
}

/* dr <room> : delete the room with the specified number, including all of the
meetings scheduled in that room -- conceptually, unless the meetings have been
rescheduled into another room, taking the room out of the list of rooms means
that its meetings are all cancelled. Errors : room number out of range, no room
number. */
void delete_room(struct Ordered_container* room_list) {
	struct Room* room_ptr;
	/* read input information for room and find room */
	if (room_ptr = read_and_find_room(room_list)) {
		void* item_ptr = OC_find_item(room_list, room_ptr);
		printf("Room %d deleted\n", get_Room_number(room_ptr));
		/* delete item from continer */
		OC_delete_item(room_list, item_ptr);
		/* release pointer to room, and destroy meetings */
		destroy_Room(room_ptr);
		return;
	}
}

/* dm <room> <time> � delete a meeting. Errors: room number out of range; no room of that number;
time out of range; no meeting at that time. */
void delete_meeting(struct Ordered_container* room_list) {
	struct Room* room_ptr;
	struct Meeting* meeting_ptr;
	/* read input information for meeting and find meeting */
	if (meeting_ptr = read_and_find_meeting_and_room(room_list, &room_ptr)) {
		printf("Meeting at %d deleted\n", get_Meeting_time(meeting_ptr));
		/* remove from container and delted pointed to data */
		remove_Room_Meeting(room_ptr, meeting_ptr);
		destroy_Meeting(meeting_ptr);
	}
}

/* dp <room> <time> <lastname> � delete a specified person from the participant list for a specified meeting. Errors: room
number out of range; no room of that number; time out of range, no meeting at that time, no person of 
that name in the people list; no person of that name in the participant list. */
void delete_person_from_meeting(struct Ordered_container* person_list, struct Ordered_container* room_list) {
	struct Room* room_ptr;
	struct Meeting* meeting_ptr;
	struct Person* person_ptr;
	/* check if room exists and info is correct */
	/* check if meeting with that time in that room exists and valid */
	if (!(meeting_ptr = read_and_find_meeting_and_room(room_list, &room_ptr))) { return; }
	/* check if person in the people list */
	else if (!(person_ptr = read_and_find_person(person_list))) { return; }
	/* check if person is not already a participant */
	else if (is_Meeting_participant_present(meeting_ptr, person_ptr)) {
		/* add person as a participant */
		remove_Meeting_participant(meeting_ptr, person_ptr);
		printf("Participant %s deleted\n", get_Person_lastname(person_ptr));
		return;
	}
	/* not a participant */
	print_error_and_clear(NOT_PARTICIPANT);
}

/* used when deleting all command is called */
void delete_all_rooms_and_meetings(struct Ordered_container* room_list) {
	/* rooms */
	OC_apply(room_list, delete_all_rooms_helper);
	OC_clear(room_list); 
	/* meetings*/
	OC_apply(room_list, delete_all_meetings_helper);
	printf("%s\n", "All rooms and meetings deleted");
}

/* ds � delete schedule � delete all meetings from all rooms. Errors: none. */
void delete_all_meetings(struct Ordered_container* room_list) {
	OC_apply(room_list, delete_all_meetings_helper);
	printf("All meetings deleted\n");
}


/* dg : delete all of the individual information; but only if there are no meetings scheduled.
Logically this is overkill; it would suffice it there are no participants in any meetings, but this
specification is made for simplicity. Errors : There are scheduled meetings. */
void delete_all_individuals(struct Ordered_container* person_list) {
	/* check if there are no meetings */
	if (g_Meeting_memory > 0) {
		print_error_and_clear(MEETINGS_EXIST);
		return;
	}
	/* deallocate the Person pointed to be the items */
	OC_apply(person_list, (OC_apply_fp_t)delete_all_individuals_helper);
	/* clear the container */
	OC_clear(person_list);
	printf("%s\n", "All persons deleted");
}

/* da : delete all of the rooms and their meetings (as in dr) and then delete all individuals in
the people list. Errors : none. */
void delete_all(struct Ordered_container* person_list, struct Ordered_container* room_list){
	/* deallocate the Person pointed to be the items */
	delete_all_rooms_and_meetings(room_list);
	delete_all_individuals(person_list);
}

/* qq � delete everything (as in da), and also delete the rooms and people lists, so that 
all memory is deallocated, and then terminate. Errors: none.*/
void quit(struct Ordered_container* person_list, struct Ordered_container* room_list) {
	delete_all(person_list, room_list); 
	/* clear the container */
	OC_destroy_container(person_list);
	OC_destroy_container(room_list);
	printf("Done\n");
}


/* 
save data functions 
*/
/* sd <filename> � save data � writes the people, rooms, and meetings data to the named 
file. Errors: the file cannot be opened for output. */
void save_data(const struct Ordered_container* person_list,
	const struct Ordered_container* room_list) {
	/* will create new file or replace old file */
	FILE* file_ptr; 
	char file_name[FILE_NAME_BUFFER_SIZE];
	/* read in filename */
	read_file_name(file_name);
	/* OPEN */
	if (!(file_ptr = fopen(file_name, "w"))) {
		print_error_and_clear(CANT_OPEN_FILE);
		return;
	}
	save_data_helper(person_list, room_list, file_ptr);
	/* CLOSE */
	fclose(file_ptr);
	printf("Data saved\n");
}

/* 
load data functions 
*/
/* ld <filename> � load data � restores the program state from the data in the file. 
Errors: the file cannot be opened for input; invalid data is found in the file 
(e.g. the file wasn't created by the program). In more detail, the program first 
attempts to open the file, and if not successful simply reports the error and prompts 
for a new command. If successful, it deletes all current data, and then attempts to 
read the people, rooms, and meetings data from the named file, which should restore 
the program state to be identical to the time the data was saved. If an error is detected 
during reading the file, the error is reported and any data previously read is discarded, 
leaving all the lists empty.*/
void load_data(struct Ordered_container* person_list,
	 struct Ordered_container* room_list) {

	FILE* file_ptr;
	char file_name[FILE_NAME_BUFFER_SIZE];

	/* get filename to read */
	read_file_name(file_name); 
	/* OPEN */
	if (!(file_ptr = fopen(file_name, "r"))) { print_error_and_clear(CANT_OPEN_FILE); return; }
	/* delete all current data, and load new data */
	delete_all_clean(person_list, room_list);
	/* load everthing */
	if (load_persons(file_ptr, person_list) ||
		load_rooms(file_ptr, person_list, room_list)) {
		print_error_and_discard(person_list, room_list);
	}
	/* CLOSE */
	fclose(file_ptr);
	printf("Data loaded\n");
}


/*
helper functions
*/

/* 
person helper functions 
*/
void print_all_helper(void* data_ptr) {
	print_Person((struct Person*)data_ptr);
}

void delete_all_individuals_helper(void* data_ptr) {
	destroy_Person((struct Person*)data_ptr);
}

/* see if the person already exists, return the person if they do */
struct Person* find_if_person_exists(const struct Ordered_container* person_list, char* lastname) {
	void* item_ptr;
	/* for the linked list implementation it returns a struct Node* and for the array
	implementation it returns a void**, but does not matter becuase it is all generic */
	item_ptr = OC_find_item_arg(person_list, lastname, (OC_find_item_arg_fp_t)comp_func_person_arg);
	return (item_ptr) ? ((struct Person*)OC_get_data_ptr(item_ptr)) : NULL;
}

void read_person(char* firstname, char* lastname, char* phoneno) {
	/* read string data to create Person and in order to prevent a buffer overflow,
	specify maximum bumber of characters to store*/
	int result_firstname = scanf("%35s", firstname);
	int result_lastname = scanf("%35s", lastname);
	int result_phoneno = scanf("%10s", phoneno);
}

/* read just last name for print and add */
void read_person_lastname(char* lastname) {
	int results = scanf("%35s", lastname);
}

/* read and find for print and delete functions */
struct Person* read_and_find_person(const struct Ordered_container* person_list) {
	struct Person* person_ptr;
	char lastname[PHONE_BUFFER_SIZE];
	/* read input information for person */
	read_person_lastname(lastname);
	/* check if person already exists */
	if (!(person_ptr = find_if_person_exists(person_list, lastname)))
		print_error_and_clear(NO_PERSON);
	return person_ptr;
}

/* returns 1 if person in the meeting */
int is_person_in_meeting(void* meeting_ptr, void* person_ptr) {
	return is_Meeting_participant_present((struct Meeting*)meeting_ptr, (struct Person*)person_ptr);
}

/* returns 1 if person in the room */
int is_person_room(void* room_ptr, void* person_ptr) {
	return OC_apply_if_arg(get_Room_Meetings((struct Room*)room_ptr),
		is_person_in_meeting, (struct Person*)person_ptr);
}


/* 
room helper functions 
*/
/* validate that the room number is a positive number */
int validate_room_number(int* room_number) {
	if (*room_number < 0) { print_error_and_clear(ROOM_OUT_OF_RANGE); return 0; }
	return 1;
}

/* validate that the input is a readable int value */
int read_room_number(int* room_number) {
	/* check for scanf error, the scan fails if the FIRST non-whitespace character
	encountered cannot be part of a decimal integer. */
	int results;
	if (!(results = scanf("%d", room_number))) { print_error_and_clear(READ_NO_INT); }
	return results;
}

/* read the room and validate all information before creating */
int read_room(int* room_number) {
	int scan_results;
	int valid_results;
	/* scanf error, starts with non-integer, or interrupted by typo */
	if (!(scan_results = read_room_number(room_number))) { return scan_results; }
	/* out of range error */
	return valid_results = validate_room_number(room_number);
}

/* see if the room already exists, return 0 if it does not, 1 if it does */
void* find_if_room_exists(const struct Ordered_container* room_list, const void* room_number) {
	/* returns NULL it not found */
	return OC_find_item_arg(room_list, room_number, comp_func_room_arg);
}

/* read and find, includes exception handling messages */
struct Room* read_and_find_room(const struct Ordered_container* room_list) {
	void* item_ptr;
	int read_result;
	int room_number;
	/* read input information for room */
	if (!(read_result = read_room(&room_number))) { return NULL; }
	/* check if room number already exists */
	else if (!(item_ptr = find_if_room_exists(room_list, (const void*)&room_number)))
		print_error_and_clear(ROOM_DOESNT_EXIST);
	return (item_ptr != NULL) ? (struct Room*)OC_get_data_ptr(item_ptr) : NULL;
}

/* used when deleting all command is called */
void delete_all_rooms_helper(void* data_ptr) {
	destroy_Room((struct Room*)data_ptr);
}


/* 
meeting helper functions 
*/
int validate_meeting_time(int* meeting_time) {
	if ((*meeting_time > 12) || (*meeting_time < 1) || (*meeting_time > 5 && *meeting_time < 9)) {
		/* time is out of range */
		*meeting_time = INT_MIN;
		print_error_and_clear(TIME_OUT_OF_RANGE);
		return 0;
	}
	return 1;
}

/* returns the results of reading the integer value */
int read_meeting_time(int* meeting_time) {
	int result;
	if (!(result = scanf("%d", meeting_time))) { print_error_and_clear(READ_NO_INT); }
	return result;
}

int read_meeting_time_and_validate(int* meeting_time) {
	if (!read_meeting_time(meeting_time)) { return 0; }
	else if (!validate_meeting_time(meeting_time)) { return 0; }
	return 1;
}

/* reads and return the results of reading the topic */
int read_meeting_topic(char* meeting_topic) {
	int results = scanf("%14s", meeting_topic);
	return results;
}

/* reads the time and topic making sure all information given is valid */
int read_meeting(int* meeting_time, char* meeting_topic) {
	int scan_time_results;
	int scan_topic_results;
	int valid_results;
	/* scanf error, starts with non-integer, or interrupted by typo */
	if (!(scan_time_results = read_meeting_time(meeting_time))) { return 0; }
	else if (!(scan_topic_results = read_meeting_topic(meeting_topic))) { return 0; }
	/* out of range error */
	return(valid_results = validate_meeting_time(meeting_time));
}

/* manages all the functions to read the input and returns the meeting at that time
or NULL if it does not exist */
struct Meeting* read_and_find_meeting(const struct Ordered_container* room_list) {

	struct Room* room_ptr;
	struct Meeting* meeting_ptr;
	int meeting_time;

	/* can't add a meeting to a room that does not exist */
	if (!(room_ptr = read_and_find_room(room_list))) { return NULL; }
	/* read time and topic of meeting, validates the time */
	else if (!(read_meeting_time_and_validate(&meeting_time))) { return NULL; }
	/* check if meeting at that time already exists in that room */
	else if (!(meeting_ptr = find_Room_Meeting(room_ptr, meeting_time)))
		print_error_and_clear(MEETING_DOESNT_EXIST);
	return meeting_ptr;
}

struct Meeting* read_and_find_meeting_and_room(const struct Ordered_container* room_list,
	struct Room** room_ptr) {
	struct Meeting* meeting_ptr;
	int meeting_time;

	/* can't add a meeting to a room that does not exist */
	if (!(*room_ptr = read_and_find_room(room_list))) { return NULL; }
	/* read time and topic of meeting, validates the time */
	else if (!(read_meeting_time_and_validate(&meeting_time))) { return NULL; }
	/* check if meeting at that time already exists in that room */
	else if (!(meeting_ptr = find_Room_Meeting(*room_ptr, meeting_time)))
		print_error_and_clear(MEETING_DOESNT_EXIST);
	return meeting_ptr;
}

/* Print the data in a struct Room. */
void print_all_meetings_helper(void* data_ptr) {
	print_Room((struct Room*)data_ptr);
}

/* clear the room and deleted meeting structs */
void delete_all_meetings_helper(void* room_ptr) {
	clear_Room((struct Room*)room_ptr);
}

/* reschedule helper function */
void reschedule_helper(struct Meeting* meeting_ptr_1, struct Room* room_ptr_1,
	struct Room* room_ptr_2, int new_meeting_time) {
	remove_Room_Meeting(room_ptr_1, meeting_ptr_1);
	set_Meeting_time(meeting_ptr_1, new_meeting_time);
	add_Room_Meeting(room_ptr_2, meeting_ptr_1);

}

/*
save data helper functions 
*/
void save_person_wrapper(void* person_ptr, void* file_ptr) {
	save_Person((const struct Person*)person_ptr, (FILE*)file_ptr);
}

void save_room_wrapper(void* room_ptr, void* file_ptr) {
	save_Room((const struct Room*)room_ptr, (FILE*)file_ptr);
}

void read_file_name(char* file_name) {
	int result = scanf("%19s", file_name);
}

void save_data_helper(const struct Ordered_container* person_list,
	const struct Ordered_container* room_list, FILE* file_ptr) {

	/* number of people */
	fprintf(file_ptr, "%d\n", OC_get_size(person_list));
	/* list of people */
	OC_apply_arg(person_list, save_person_wrapper, (void*)file_ptr);
	/* number of rooms */
	fprintf(file_ptr, "%d\n", OC_get_size(room_list));
	/* list of rooms with all there meetings */
	OC_apply_arg(room_list, save_room_wrapper, (void*)file_ptr);
}


/*
load data helper functions
*/
/* deleta all but without the messaging */
void delete_all_clean(struct Ordered_container* person_list,
	struct Ordered_container* room_list) {
	/* rooms */
	OC_apply(room_list, delete_all_rooms_helper);
	OC_clear(room_list);
	/* meetings*/
	OC_apply(room_list, delete_all_meetings_helper);

	/* check if there are no meetings */
	if (g_Meeting_memory > 0) {
		print_error_and_clear(MEETINGS_EXIST);
		return;
	}
	/* deallocate the Person pointed to be the items */
	OC_apply(person_list, (OC_apply_fp_t)delete_all_individuals_helper);
	/* clear the container */
	OC_clear(person_list);
}

/* if error is detected, report and discard everything */
void print_error_and_discard(struct Ordered_container* person_list,
	struct Ordered_container* room_list) {
	print_error_and_clear(INVALID_DATA);
	delete_all_clean(person_list, room_list);
}

int load_persons(FILE* file_ptr, struct Ordered_container* person_list) {
	struct Person* person_ptr;
	int num_of_people;

	/* number of people */
	if (!(fscanf(file_ptr, "%d", &num_of_people))) { return 1; }
	/* list of people */
	for (;num_of_people > 0; --num_of_people) {
		if (!(person_ptr = load_Person(file_ptr)))
			return 1;
		OC_insert(person_list, (void*)person_ptr);
	}
	return 0;
}

int load_rooms(FILE* file_ptr, struct Ordered_container* person_list,
	struct Ordered_container* room_list) {
	struct Room* room_ptr;
	int num_of_rooms;

	/* number of rooms */
	if (!(fscanf(file_ptr, "%d", &num_of_rooms))) { return 1; }
	/* list of rooms */
	for (;num_of_rooms > 0; --num_of_rooms) {
		if (!(room_ptr = load_Room(file_ptr, person_list)))
			return 1;
		OC_insert(room_list, (void*)room_ptr);
	}
	return 0;
}


/* 
error handling functions 
*/
void print_error_and_clear(Error_c error) {
	switch (error) {
	case BAD_COMMAND:
		printf("Unrecognized command!\n"); //
		break;
	case READ_NO_INT:
		printf("Could not read an integer value!\n"); //
		break; 
	case ROOM_OUT_OF_RANGE:
		printf("Room number is not in range!\n"); //
		break;
	case ROOM_ALREADY_EXISTS:
		printf("There is already a room with this number!\n"); //
		break;
	case PERSON_ALREADY_EXISTS:
		printf("There is already a person with this last name!\n"); //
		break;
	case NO_PERSON:
		printf("No person with that name!\n"); //
		break;
	case ROOM_DOESNT_EXIST:
		printf("No room with that number!\n"); //
		break;
	case MEETING_ALREADY_EXIST:
		printf("There is already a meeting at that time!\n"); //
		break; 
	case TIME_OUT_OF_RANGE:
		printf("Time is not in range!\n");
		break;
	case MEETING_DOESNT_EXIST:
		printf("No meeting at that time!\n"); //
		break;
	case ALREADY_PARTICIPANT:
		printf("This person is already a participant!\n"); //
		break;
	case NOT_PARTICIPANT:
		printf("This person is not a participant in the meeting!\n"); //
		break;
	case SAME_MEETING:
		printf("Cannot reschedule to the same room and time!\n");
		break;
	case IS_PARTICIPANT:
		printf("This person is a participant in a meeting!\n"); //
		break; 
	case MEETINGS_EXIST:
		printf("Cannot clear people list unless there are no meetings!\n"); //
		break;
	case CANT_OPEN_FILE:
		printf("Could not open file!\n");
		break;
	case INVALID_DATA:
		printf("Invalid data found in file!\n");
		break;
	default:
		break;
	}
	while(getchar() != '\n');
}

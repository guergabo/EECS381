/* C Program for Project 1, EECS 381 */

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

#define NAME_BUFFER_SIZE 36 
#define PHONE_BUFFER_SIZE 11
#define TOPIC_BUFFER_SIZE 15

/* user defined data type. Assign names / states to integral constants */
typedef enum {
	BAD_COMMAND, READ_NO_INT, ROOM_OUT_OF_RANGE, ROOM_ALREADY_EXISTS,
	PERSON_ALREADY_EXISTS, NO_PERSON, ROOM_DOESNT_EXIST, MEETING_ALREADY_EXIST,
	TIME_OUT_OF_RANGE, MEETING_DOESNT_EXIST
} Error_c;

/* function prototypes */
/* add functions */
void add_individual(struct Ordered_container* person_list);
void add_room(struct Ordered_container* room_list);
void add_meeting(struct Ordered_container* room_list);
/* add_person_to_meeting */

/* print functions */
void print_individual(const struct Ordered_container* person_list);
void print_all_individuals(const struct Ordered_container* person_list);
void print_room(const struct Ordered_container* room_list);
void print_meeting(const struct Ordered_container* room_list);
/* print_all_meetings */
/* print_memory */


/* delete functions */
void delete_individual(struct Ordered_container* person_list);
void delete_all_individuals(struct Ordered_container* person_list);
void delete_room(struct Ordered_container* room_list);
/* delete_all_meetings */
void delete_meeting(struct Ordered_container* room_list);
/* delete_all_meetings */
void delete_all(struct Ordered_container* person_list,
				struct Ordered_container* room_list);
/* delete_participants */




/* reschedule functions */

/* save data functions */

/* load data functions */



/* person helper functions */


/* room helper functions */


/* meeting helper functions */


/* error handling functions */
void print_error_and_clear(Error_c error);

int main() {
	/* containers */
	struct Ordered_container* person_list = OC_create_container(comp_func_person);
	struct Ordered_container* room_list = OC_create_container(comp_func_meeting);
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
				add_individual(person_list);  // HERE1
				break;
			case 'r':
				/* (add) room command */
				add_room(room_list);
				break;
			case 'm':
				/* (add) meeting command */
				add_meeting(room_list); 
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
				print_all_individuals(person_list); // HERE2
				break;
			case 'r':
				/* (print) room command */
				print_room(room_list);
				break;
			case 'm':
				/* (print) meeting command */
				print_meeting(room_list);
				break;
			default:
				print_error_and_clear(BAD_COMMAND);
				break;
			}
			/* break from command_one */
			break;
		case 'd':
			switch (command_two) {
			case 'i':
				/* (delete) individual command */
				delete_individual(person_list);
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
			default:
				print_error_and_clear(BAD_COMMAND);
				break;
			}
			/* break from command_one */
			break;
		case 'q':
			delete_all(person_list, room_list); return 0;
			break;
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
	if (item_ptr) { return ((struct Person*)OC_get_data_ptr(item_ptr)); }
	else { return NULL; }
}

void read_person(char* firstname, char* lastname, char* phoneno) {
	/* read string data to create Person and in order to prevent a buffer overflow,
	specify maximum bumber of characters to store*/
	int result_firstname;
	int result_lastname;
	int result_phoneno;
	/* read inputs */
	result_firstname = scanf("%35s", firstname);
	result_lastname = scanf("%35s", lastname);
	result_phoneno = scanf("%10s", phoneno);
}

/* read just last name for print and add */
void read_person_lastname(char* lastname) {
	int results = scanf("%35s", lastname);
}

/* read and find */
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
	if (!(item_ptr = find_if_room_exists(room_list, (const void*)&room_number)))
		print_error_and_clear(ROOM_DOESNT_EXIST);
	return (item_ptr != NULL) ? (struct Room*)OC_get_data_ptr(item_ptr) : NULL;
}

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
	if (!(scan_topic_results = read_meeting_topic(meeting_topic))) { return 0; }
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
	else if (!(read_meeting_time(&meeting_time))) { return NULL; }
	/* check if meeting at that time already exists in that room */
	else if(!(meeting_ptr = find_Room_Meeting(room_ptr, meeting_time)))
		print_error_and_clear(MEETING_DOESNT_EXIST);
	return meeting_ptr; 
}

struct Meeting* read_and_find_meeting_and_room(const struct Ordered_container* room_list,
	const struct Room** room_ptr) {
	struct Meeting* meeting_ptr;
	int meeting_time;

	/* can't add a meeting to a room that does not exist */
	if (!(*room_ptr = read_and_find_room(room_list))) { return NULL; }
	/* read time and topic of meeting, validates the time */
	else if (!(read_meeting_time(&meeting_time))) { return NULL; }
	/* check if meeting at that time already exists in that room */
	else if (!(meeting_ptr = find_Room_Meeting(*room_ptr, meeting_time)))
		print_error_and_clear(MEETING_DOESNT_EXIST);
	return meeting_ptr;
}

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

/* pg : print the individual information (same information as pi) for all people in the person list.
Errors : none. (It is not an error if there are no people -- that is a valid possibility. */
void print_all_individuals(const struct Ordered_container* person_list) {
	/* check if size if zero */
	if (OC_empty(person_list)) { printf("%s\n", "List of people is empty"); return; }    // HERE5
	/* if not empty, loop and apply print_Person function to data_ptr */
	OC_apply(person_list, (OC_apply_fp_t)print_all_helper);                                 // HERE6
}

void print_room(const struct Ordered_container* room_list) {
	struct Room* room_ptr;
	/* read input information for rooom and find room */
	if(room_ptr = read_and_find_room(room_list))
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


/*
delete functions
*/
/* di <lastname> : delete a person from the people list but only if he or she is not a participant
ina  meeting. Erros : No person of that name; person is a participant in a meeting. */
void delete_individual(struct Ordered_container* person_list) {
	struct Person* person_ptr; void* item_ptr;
	/* search if person with the lastname exists */
	if (!(person_ptr = read_and_find_person(person_list))) {
		return;
	}
	/* delete cell / node that points to the individual */
	item_ptr = OC_find_item(person_list, person_ptr);
	OC_delete_item(person_list, item_ptr);
	/* destroy person */
	printf("%s %s %s\n", "Person", get_Person_lastname(person_ptr), "deleted");
	destroy_Person(person_ptr);
}

/* dg : delete all of the individual information; but only if there are no meetings scheduled.
Logically this is overkill; it would suffice it there are no participants in any meetings, but this
specification is made for simplicity. Errors : There are scheduled meetings. */
void delete_all_individuals(struct Ordered_container* person_list) {
	/* check if there are no meetings */

	/* deallocate the Person pointed to be the items */
	OC_apply(person_list, (OC_apply_fp_t)delete_all_individuals_helper);
	/* clear the container */
	OC_clear(person_list);
	printf("%s\n", "All persons deleted");
}

/* dr <room> : delete the room with the specified number, including all of the 
meetings scheduled in that room -- conceptually, unless the meetings have been 
rescheduled into another room, taking the room out of the list of rooms means 
that its meetinsg are all cancelled. Errors : room number out of range, no room 
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

/* da : delete all of the rooms and their meetings (as in dr) and then delete all individuals in
the people list. Errors : none. */
void delete_all(struct Ordered_container* person_list,
				struct Ordered_container* room_list) {

	/* deallocate the Person pointed to be the items */
	OC_apply(person_list, (OC_apply_fp_t)delete_all_individuals_helper);
	/* clear the container */
	OC_clear(person_list);

	/* meetings */

	/* rooms */
	

	printf("%s\n%s\n", "All rooms and meetings deleted", "All persons deleted");
}


/*
helper functions
*/

/* 
person helper functions 
*/



/* 
room helper functions 
*/
/* validate that the room number is a positive number */



/* 
meeting helper functions 
*/



/* 
error handling functions 
*/
void print_error_and_clear(Error_c error) {
	switch (error) {
	case BAD_COMMAND:
		printf("Unrecognized command!\n");
		break;
	case READ_NO_INT:
		printf("Could not read an integer value!\n");
		break; 
	case ROOM_OUT_OF_RANGE:
		printf("Room number is not in range!\n");
		break;
	case ROOM_ALREADY_EXISTS:
		printf("There is already a room with this number!\n");
		break;
	case PERSON_ALREADY_EXISTS:
		printf("There is already a person with this last name!\n");
		break;
	case NO_PERSON:
		printf("No person with that name!\n");
		break;
	case ROOM_DOESNT_EXIST:
		printf("No room with that number!\n");
		break;
	case MEETING_ALREADY_EXIST:
		printf("There is already a meeting at that time!\n");
		break; 
	case TIME_OUT_OF_RANGE:
		printf("Time is not in range!\n");
		break;
	case MEETING_DOESNT_EXIST:
		printf("No meeting at that time!\n");
		break;
	default:
		break;
	}
	while(getchar() != '\n');
}

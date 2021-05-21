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

#define NAME_BUFFER_SIZE 36 
#define PHONE_BUFFER_SIZE 11

/* function prototypes */
/* add functions */
void add_individual(struct Ordered_container* person_list);
/* add_meeting */

/* print functions */
void print_individual(const struct Ordered_container* person_list);
void print_all_individuals(const struct Ordered_container* person_list);
/* print_meeting */
/* print_all_meetings */

/* delete functions */
void delete_individual(struct Ordered_container* person_list);
void delete_all_individuals(struct Ordered_container* person_list);
/* delete_meeting */
/* delete_all_meetings */
void delete_all(struct Ordered_container* person_list);

/* reschedule functions */

/* save data functions */

/* load data functions */

/* search functions */

/* apply helper functions */
void print_all_helper(void* data_ptr);
void delete_all_individuals_helper(void* data_ptr);

/* input helper functions */
void read_person(char* firstname, char* lastname, char* phoneno);

/* input validation helper functions */
struct Person* find_if_person_exists(const struct Ordered_container* person_list, char* lastname);

/* stream helper functions */
void clear_stream_state(void);

/* error functions */
void error(void);
void person_exists_error(void);
void no_person_error(void);

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
			default:
				error();
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
			default:
				error();
				break;
			}
			/* break from command_one */
			break;
		case 'd':
			switch (command_two) {
			case 'i':
				delete_individual(person_list);
				break;
			case 'g':
				delete_all_individuals(person_list);
				break;
			case 'a':
				delete_all(person_list);
				break;
			default:
				error();
				break;
			}
			/* break from command_one */
			break;
		case 'q':
			delete_all(person_list); return 0;
			break;
		default:
			error();
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
	if (!(person_ptr = find_if_person_exists(person_list, lastname))) { // HERE3
		/* dynamically allcate and insert Person to the list*/
		person_ptr = create_Person(firstname, lastname, phoneno);
		OC_insert(person_list, (void*)person_ptr);                              // HERE4
		printf("Person %s added\n", &lastname);
		return;
	}
	person_exists_error();
}


/*
print functions
*/
/* pi <lastname> : print the specified individual information. Errors : no person with that last name. */
void print_individual(const struct Ordered_container* person_list) {
	struct Person* person_ptr;
	char lastname[NAME_BUFFER_SIZE];
	/* get lastname */
	int result = scanf("%35s", &lastname);
	/* search for full info on Person with that lastname */
	if (!(person_ptr = find_if_person_exists(person_list, lastname))) {
		no_person_error();
		return;
	}
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


/*
delete functions
*/
/* di <lastname> : delete a person from the people list but only if he or she is not a participant
ina  meeting. Erros : No person of that name; person is a participant in a meeting. */
void delete_individual(struct Ordered_container* person_list) {
	struct Person* person_ptr; void* item_ptr;
	char lastname[NAME_BUFFER_SIZE];
	/* get lastname */
	int result = scanf("%35s", &lastname);
	/* search if person with the lastname exists */
	if (!(person_ptr = find_if_person_exists(person_list, lastname))) {
		no_person_error();
		return;
	}
	/* delete cell / node that points to the individual */
	item_ptr = OC_find_item(person_list, person_ptr);
	OC_delete_item(person_list, item_ptr);
	/* destroy person */
	destroy_Person(person_ptr);
	printf("%s %s %s\n", "Person", lastname, "deleted");
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

/* da : delete all of the rooms and their meetings (as in dr) and then delete all individuals in
the people list. Errors : none. */
void delete_all(struct Ordered_container* person_list) {
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
/* apply helper functions */
void print_all_helper(void* data_ptr) {
	print_Person((struct Person*)data_ptr);
}

void delete_all_individuals_helper(void* data_ptr) {
	destroy_Person((struct Person*)data_ptr);
}

/* input helper functions */
void read_person(char* firstname, char* lastname, char* phoneno) {
	/* read string data to create Person and in order to prevent a buffer overflow,
	specify maximum bumber of characters to store*/
	int result_firstname;
	int result_lastname;
	int result_phoneno;

	result_firstname = scanf("%35s", firstname);
	result_lastname = scanf("%35s", lastname);
	result_phoneno = scanf("%10s", phoneno);
}

/* input validation helper functions */
struct Person* find_if_person_exists(const struct Ordered_container* person_list, char* lastname) {
	void* item_ptr;
	/* for the linked list implementation it returns a struct Node* and for the array
	implementation it returns a void**, but does not matter becuase it is all generic */
	item_ptr = OC_find_item_arg(person_list, lastname, (OC_find_item_arg_fp_t)comp_func_person_arg);
	if (item_ptr) { return ((struct Person*)OC_get_data_ptr(item_ptr)); }
	else { return NULL; }
}

/* stream helper functions */
void clear_stream_state(void) {
	/* skip offending material and start over */
	while (getchar() != '\n');
}

/* error functions */
void error(void) {
	printf("%s\n", "Unrecognized command!");
	clear_stream_state(); /* only skip the rest of the line when an error is detected */
}

void person_exists_error(void) {
	printf("%s\n", "There is already a person with this last name!");
}

void no_person_error(void) {
	printf("%s\n", "No person with that name!");
}

/* test file for Person struct and commands */

/* allows me to use normal scanf */
#pragma warning(disable : 4996)

#include "Utility.h"
#include "Ordered_container.h"
#include "Person.h"

/* libraries */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_BUFFER_SIZE 36 
#define PHONE_BUFFER_SIZE 11

/* Reminder Definitions */
/* incomplete declarations :: */

/* Buffer :: C uses a buffer to output or input variables. The buffer stores the variable that is 
supposed to be taken in (input) or sent out (output) of the program. A buffer needs to be cleared
before the next input is taken in. A buffer is a temporary storage used to store input and output 
commands. All inputs and output commands are buffered in the OS's buffer. Typically
because buffer contains data that is stored for a short amount of time, it is in the computer's 
memory (RAM) */

/* 	Switch statement :: allows a variable to be tested for equality against a list of value. Each 
value is called a case, and the variable being switched on is checked for each switch case*/
/* 
	Stream I/O in C
	---------------
	A stream is a sequence of characters with functions to take characters oout of one 
	end, and put characters into the other end. 

	Specifically, one end of the stream is connected to a physical I/O device such as a 
	keyboard or display. If it is a console output stream, your program puts characters 
	into one end of the stream, and the display system takes characters out of the other 
	and puts them on the screen. 

	File streams follow the same principle, except that the file system is attached to 
	the other end of the stream. 

	The standard I/O streams: stdin and stdout 
	Two streams that allow you to communicate with your console.

	stdin --> keyboard
	stdout --> display 

	stdin and stdout are actually global variables that are declared in <stdio.h> and 
	initialized during program startup. 

	Stream Output :: printf()
	The value of the variable is converted into a sequence of characters on depending on 
	the format. 

	// the char* is the format string, and the ... is a special type declaration that 
	// tells the compiler that any number of argumnets of any type can appear before 
	// the right parentheses;
	int printf(const char*, ...);
	
	because pritnf() has to go by the format specification and not the actual types 
	of the variables, it is not type-safe. That is, there is no check that the variables 
	you supply match the format items in type. 

	Stream Input :: scanf()
	Like printf, scanf lacks type safety 

	int scanf(const char*, ...); 

	Each % item is a request to look for a value for a certain type in the input stream. 
	In almost all cases, the scanf functions starts the scan for the value by skipping over 
	any initial whitespace characters. 

	can collect digit, +, -
	space cannot be part of an integer so it stops 

	%c - whitespaces are characters and won't be skipped 

	if invalid :: 
	1. print a message
	2. skip over the bad input by reading and discarding it 
	3. start fresh 

	input reading loop structure :: 

	Attempt to read some input. 
	Check for successful read.
		If success, and only if success, 
			use the input (which may involve addition checks on validity) 
		If fail, do the following:
			Print a message informing the user of the bad input 
			Skip the offending material.
			Resume Processing. 

	while(getchar() != '\n'); // gets character from the stream`

	File Streams in C :: 
	

*/

/* function prototypes */
/* add functions */
void add_individual(struct Ordered_container* person_list);

/* print functions */
void print_individual(const struct Ordered_container* person_list);
void print_all_individuals(const struct Ordered_container* person_list);

/* delete functions */
void delete_individual(struct Ordered_container* person_list); 
void delete_all_individuals(struct Ordered_container* person_list);
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

int main(){

	struct Ordered_container* person_list; 
	person_list = OC_create_container(comp_func_person);

	/* two character commands define program behavior */
	char command_one;
	char command_two;
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
		OC_insert(person_list, (void*) person_ptr);                              // HERE4
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
	OC_apply(person_list, (OC_apply_fp_t) print_all_helper);                                 // HERE6
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


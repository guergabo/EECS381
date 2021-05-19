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

#define BUFFER_SIZE 31 
/* Reminder Definitions */
/* incomplete declarations :: */
/* Buffer :: */
/* 	Switch :: */
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
void add_individual(struct Orderd_container* person_list);

/* print functions */
void print_individual(struct Ordered_container* person_list);

/* delete functions */

/* reschedule functions */

/* save data functions */

/* load data functions */

/* search functions */

/* search helper functions */

/* input validation helper functions */

/* stream helper functions */

/* error functions */


int main(){

	struct Ordered_container* person_list; 
	person_list = OC_create_container(comp_func_person);

	/* two character commands define program behavior */
	char command_one;
	char command_two;
	while (1) {
		/* read the two command characters */
		printf("\nEnter command: ");
		int s1 = scanf("%1c", &command_one);
		int s2 = scanf("%1c", &command_two);
		switch (command_one) {
		case 'a':
			switch (command_two) {
			case 'i':
				/* (add) individual command */
				add_individual(person_list);
				break;
			default:
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
			default:
				break;
			}
			/* break from command_one */
			break;
		default:
			break;
		}
	}

	return 0;
}

/* add functions */
/* add an individual to the Ordered_container for Person */
void add_individual(struct Orderd_container* person_list) {
	struct Person* person_ptr; 
	char firstname[BUFFER_SIZE];
	char lastname[BUFFER_SIZE];
	char phoneno[BUFFER_SIZE]; 
	/* read string data to create Person */
	/* to prevent a buffer overflow, specify maximum bumber of characters to store*/
	int success1 = scanf("%30s", &firstname);
	int success2 = scanf("%30s", &lastname);
	int success3 = scanf("%30s", &phoneno);
	/* check if person exists already with same lastname */

	/* dynamically allocate Person */
	person_ptr = create_Person(firstname, lastname, phoneno);
	/* insert Person to the list*/
	OC_insert(person_list, person_ptr);
	printf("Person %s added\n", &lastname);
	printf("%s %s %s ", &firstname, &lastname, &phoneno);
}


/* print functions */
void print_individual(struct Ordered_container* person_list) {
	struct Person* found; 
	char lastname[BUFFER_SIZE];
	/* get lastname */
	int result = scanf("%30s", &lastname);
	/* search for full info on Person with that lastname */
	found = OC_find_item_arg(person_list, lastname, (OC_find_item_arg_fp_t)comp_func_person_arg);
	if (found) { print_Person(found); }
}


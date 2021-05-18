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

#define MAX 1000 
/* Reminder Definitions */
/* incomplete declarations :: */


/* function prototypes */
/* add functions */
void add_participant(struct Orderd_container* person_list);

/* print functions */

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
		/* read the two commadn characters */
		printf("\nEnter command: ");
		scanf("%c", &command_one);
		scanf("%c", &command_two);
		if (command_one == 'q') { break;  }
		switch (command_one) {
		case 'a':
			switch (command_two) {
			case 'i':
				/* (add) individual command */
				add_participant(person_list);
				break;
			default:
				break;
			}
		default:
			break;
		}
	}

	return 0;
}

/* add functions */
/* add an individual to the Ordered_container for Person */
void add_participant(struct Orderd_container* person_list) {
	struct Person* person_ptr; 
	char firstname[MAX];
	char lastname[MAX]; 
	char phoneno[MAX]; 
	
	/* read string data to create Person */
	scanf("%s", &firstname);
	scanf("%s", &lastname);
	scanf("%s", &phoneno);

	/* check if person exists already with same lastname */

	/* dynamically allocate Person */
	person_ptr = create_Person(firstname, lastname, phoneno);
	
	/* insert Person to the list*/
	OC_insert(person_list, person_ptr);
	printf("Person %s added\n", &lastname);
}

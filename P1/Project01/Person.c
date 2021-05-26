/* Person.c */

#pragma warning(disable : 4996) /* lets me use normal library functions */

#include "Utility.h"
#include "Person.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* a Person consist of pointers to C-strings for names and phone number */
struct Person {
	char* firstname;
	char* lastname;
	char* phoneno;
};

/* Create a Person object.
This is the only function that allocates dynamic memory for a Person
and the contained data. */
struct Person* create_Person(const char* firstname, const char* lastname, const char* phoneno) {
	struct Person* person_ptr = safe_malloc(sizeof(struct Person));
	/* dynamically allocate for string data */
	person_ptr->firstname = alloc_char(strlen(firstname) + 1); /* strlen does not include null */
	person_ptr->lastname = alloc_char(strlen(lastname) + 1);
	person_ptr->phoneno = alloc_char(strlen(phoneno) + 1);
	/* copy the string data into Person, linking life of data to life of struct */
	strcpy(person_ptr->firstname, firstname);
	strcpy(person_ptr->lastname, lastname);
	strcpy(person_ptr->phoneno, phoneno);

	return person_ptr;
}

/* Destroy a Person object
This is the only function that frees the memory for a Person
and the contained data. */
void destroy_Person(struct Person* person_ptr) {
	/* free the contained data */
	free_char(person_ptr->firstname);
	free_char(person_ptr->lastname);
	free_char(person_ptr->phoneno);

	/* free the struct */
	free(person_ptr);
}

/* Return the lastname pointer as a pointer to unmodifiable characters. */
const char* get_Person_lastname(const struct Person* person_ptr) {
	/* cannot modify because it is a string literal */
	return person_ptr->lastname;
}

/* Print a Person data item to standard output with a final \n character. */
void print_Person(const struct Person* person_ptr) {
	printf("%s %s %s\n", person_ptr->firstname, person_ptr->lastname, person_ptr->phoneno);
}

/* Write a Person to a file stream, as a line containing
firstname, lastname, phoneno,  whitespace-separated with a final \n character. */
void save_Person(const struct Person* person_ptr, FILE* outfile) {
	fprintf(outfile, "%s %s %s\n", person_ptr->firstname, person_ptr->lastname, person_ptr->phoneno);
}

/* Read a Person's data from a file stream, create the data object and
return a pointer to it, NULL if invalid data discovered in file.
No check made for whether the Person already exists or not. */
struct Person* load_Person(FILE* infile) {
	char first_name[NAME_BUFFER_SIZE];
	char last_name[NAME_BUFFER_SIZE];
	char phone_no[PHONE_BUFFER_SIZE];
	int result;
	if (!(result = fscanf(infile, "%35s %35s %10s", first_name, last_name, phone_no))) {
		return NULL;
	}
	/* create data object and return */
	return create_Person(first_name, last_name, phone_no);
}
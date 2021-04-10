/*
*	Filename: Person.cpp
*	These functions define a Person who is a potential participant in one of the meetings
*	The person is defined by a first name, last name, and phone number.
*/

#include "Person.h"
#include <iostream>
// #include <string> is already included by the Person.h file"

using namespace std;

// use colon syntax to create them and assign to desired value immediately
// a person starts off with 0 commitments or 0 Meetings
Person::Person(string fN, string lN, string pN) : firstName(fN), lastName(lN), phoneNumber(pN), commitments(0) {}

// return last name of each participants 
string Person::lastNames(void) const {
	return lastName;
}
// print out the complete information for an individual person
void Person::info(void) const {
	string info = firstName + " " + lastName + " " + phoneNumber + " ";
	cout << info << '\n';
	return;
}

string Person::infoS(void) const {
	string info = firstName + " " + lastName + " " + phoneNumber + " ";
	return info;
}

// add a new meeting in a specified room to the list as a commitment they have 
void Person::addCommitment() {
	++commitments;
	return;
}

// check if the person has any meetings or not
bool Person::busy(void) const {
	return commitments > 0 ? 1 : 0;
}

// set all commitmnets back to zero | free them from their commitments
void Person::free(void) {
	// subtract one meeting everytime a meeting is being deleted 
	--commitments;
	return;
}
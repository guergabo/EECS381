/*
*	Filename: Person.h
*	This class represents a person the user defines as a potential a participant in
*	the meetings. The person is defined by a first name, last name, and phone number.
*/

#ifndef PERSON_H
#define PERSON_H


#include <string>
#include <vector>
// declaring classes prototypes instead of header file which will shadow other includes
class Room;
class Meeting;

// if we don't use namespace std we have to explicitly state that it comes from the standard template library

class Person {
	// Private Date Members
private:
	// must be one word
	std::string firstName;
	// must be one and unique
	std::string lastName;
	// must be contiguous and represented as a character of strings
	std::string phoneNumber;
	// list of meetings person is involved in, if empty they can be deleted | order does not matter 
	int commitments;

	// Public Member Functions
public:
	// Person Constructor takes in a first name, last name, and phone number
	Person(std::string fN, std::string lN, std::string pN);
	// return last name of each participants 
	std::string lastNames() const;
	// prints out the complete information of an individual Person including first name, last name, and phone number
	void info(void) const;
	// returns the complete information of an individual including first name, last name, and phone number 
	std::string infoS(void) const;
	// add a new meeting in a specified room to the list as a commitment they have 
	void addCommitment();
	// check if the person has any meetings or not
	bool busy(void) const;
	// set all commitmnets back to zero | free them from their commitments
	void free(void);
};

#endif


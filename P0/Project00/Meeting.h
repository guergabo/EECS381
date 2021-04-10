/*
*	Filename: Meeting.h
*	This class represents a meeting the user defines with a time and topic.
*/

#ifndef MEETING_H
#define MEETING_H


#include "Person.h"
#include <map>
// #include <string> is already included by the Person.h file"

class Meeting {
	// Private Data Members
private:
	// meeting times fall within the traditional business day of 9:00Am to 5:00PM.
	// Therefore, the meeting times are expressed in 12-hour format without an AM/PM
	// For example, "10" is assumed to be 10:00AM; "2" is 2:00PM
	int meetingTime;
	// meeting topic must be one word
	std::string topic;
	// list of people participating in the meeting
	std::map<std::string, Person*> people;

	// Public Member Functions
public:
	// Meeting Constructor takes in a time and topic
	Meeting(int m, std::string t);
	// Copy Constructor 
	Meeting(const Meeting& source);
	// set the time of the meeting
	void setTime(int time);
	// return the time of the meeting
	int getTime(void);
	// return the topic of the meeting
	std::string getTopic();
	// get list of participants 
	std::map<std::string, Person*>& getPeople(void);
	// print the time, topic and participants (full name and phone number)
	void info();
	// print all the people in the meeting in order 
	void printAllPeople();
	// return all the people in the meeting in order 
	std::string getParticipants() const;
	// return number of participants 
	int numberofParticipants() const;
	// check if person with last name already part of meeting
	bool registeredPerson(std::string lastName);
	// add participant to the meeting 
	void addParticipant(std::string lastName, Person* person_ptr);
	// delete participant from the meeting
	void deleteParticipant(std::string lastName);
	// add committment to all people in the list
	void addCommitments();
};

#endif

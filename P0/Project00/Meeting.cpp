/*
*	Filename: Meeting.cpp
*	These functions define the functionality of a meeting which is defined
*	by a time, topic, and list of people involved in the meeting.
*/

#include "Meeting.h"
#include <iostream>
// #include <vector> is already included by the Meeting.h file"
// #include <string> is already included by the Person.h file"

using namespace std;

// Meeting constructor takes in a time and topic
Meeting::Meeting(int m, string t) : meetingTime(m), topic(t) { people = {}; }

// Copy Constructor  
Meeting::Meeting(const Meeting& source) : meetingTime(source.meetingTime), topic(source.topic), people(source.people) {
	// one committment for each 
	return;
}

// return the topic of the meeting
std::string Meeting::getTopic() {
	return topic;
}

// set the time of the meeting
void Meeting::setTime(int time) {
	meetingTime = time;
}
// return the time of th meeting
int Meeting::getTime(void) {
	return meetingTime;
}

// get list of participants 
std::map<std::string, Person*>& Meeting::getPeople(void) {
	return people;
}

// print the time, topic and participants (full name and phone number)
void Meeting::info() {
	cout << "Meeting time: " << meetingTime << ", Topic: " << topic << '\n';
	printAllPeople();
	return;
}

// print all the people in the meeting
void Meeting::printAllPeople() {
	std::map<std::string, Person*>::iterator it = people.begin();
	if (it == people.end()) { std::cout << "Participants: None" << '\n'; return; }
	std::cout << "Participants: " << '\n';
	while (it != people.end()) {
		Person* person_ptr = it->second;
		person_ptr->info();
		it++;
	}
	return;
}

// return all the people in the meeting in order 
std::string Meeting::getParticipants() const {
	std::map <std::string, Person*>::const_iterator it = people.begin();
	string LAST = "";
	while (it != people.end()) {
		string last = it->second->lastNames();
		LAST = LAST + last + '\n';
		++it;
	}
	if (LAST.length() > 0 ){LAST.pop_back();}
	// LAST.size() > 0 ? LAST.pop_back() : LAST;
	return LAST;
}

// return number of participants 
int Meeting::numberofParticipants() const {
	return people.size();
}

// check if person with last name already part of meeting
bool Meeting::registeredPerson(std::string lastName) {
	if (people.find(lastName) != people.end()) { return 1; }
	return 0;
}

// add participant to the meeting 
void Meeting::addParticipant(std::string lastName, Person* person_ptr) {
	people.insert(std::pair<std::string, Person*>(lastName, person_ptr));
	return;
}

// delete participant from the meeting
void Meeting::deleteParticipant(std::string lastName) {
	// free the people from this particular commitment
	// no need to deallocate person, they can still participate in other meetings 
	Person* person_ptr = people.at(lastName);
	person_ptr->free();
	// just erase key-value pair from the list 
	people.erase(lastName);
}

// add committment to all people in the list
void Meeting::addCommitments() {
	std::map<std::string, Person*>::iterator person_it = people.begin();
	while (person_it != people.end()) {
		person_it->second->addCommitment();
		++person_it;
	}
	return;
}

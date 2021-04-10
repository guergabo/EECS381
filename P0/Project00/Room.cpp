/*
*	Filename: Room.cpp
*	These functions define the functionality of a room which is defined
*	by a room number and a list of the meetings it will host today.
*/

#include "Room.h"
#include <iostream>
#include <string>
// Room constructor takes in a room number
Room::Room(int rNum) : roomNumber(rNum) { Meetings = {}; }

// return room number 
int Room::getRoomNumber(void) const {
	return roomNumber;
}

// insert meeting in the moring 9 - 12
void Room::insertMorning(int time, Meeting* meeting_ptr) {
	// start forward fro better chance at finding quicker
	std::list<Meeting*>::iterator it = Meetings.begin();
	while (1) {
		// main condition 1: number is in the afternoon
		if ((*it)->getTime() < 6) {
			// want to go before any numbers in the afternoon 
			break;
		}
		// main condition 2: number is in the morning
		else if ((*it)->getTime() > 6) {
			// searching for first bigger number 
			if ((*it)->getTime() < time) {
				if (++it == Meetings.end()) { it = Meetings.end(); break; }
				else { it; }
			}
			else if ((*it)->getTime() > time) { break; }
		}
	}
	// insert before the first later time in the morning
	Meetings.insert(it, meeting_ptr);
	return;
}


// insert meeting in ther afternoon 1- 5
void Room::insertAfternoon(int time, Meeting* meeting_ptr) {
	// start backwards for better chance at finding quicker
	// looking for the first earlier time
	std::list<Meeting*>::iterator it = Meetings.end();
	// pointing to last element
	--it;
	while (1) {
		// main condition 1: number is in the morning 
		if ((*it)->getTime() > 6) {
			if (++it == Meetings.end()) { it = Meetings.end(); break; }
			else { it; break; }
		}
		// main condition 2: number is in the afternoon 
		else if ((*it)->getTime() < 6) {
			// keeping search for smaller one 
			if ((*it)->getTime() > time) {
				// if it was the first element
				if (it == Meetings.begin()) { it = Meetings.begin(); break; }
				--it;
			}
			// found the first smaller/earlier time 
			else if ((*it)->getTime() < time) {
				// if it was the last element 
				if (++it == Meetings.end()) { it = Meetings.end(); break; }
				// it upates in conditional above already 
				else { it; break; }
			}
		}
	}
	// insert before the first later time in the afternoon
	Meetings.insert(it, meeting_ptr);
	return;
}

// replace with a linked list std::list
// std::list data structure keeps the list ordered and provides fast insertion 
// set of possible times = {9, 10, 11, 12, 1, 2, 3, 4, 5}
void Room::newMeeting(int time, Meeting* meeting_ptr) {
	// if linked lists is empty 
	if (Meetings.size() == 0) { Meetings.insert(Meetings.end(), meeting_ptr); return; }
	// if time is 9 - 12 inclusive
	if (time > 8) {
		insertMorning(time, meeting_ptr); return;
	}
	// if time is 1 - 5 inclusive
	else if (time < 6) {
		insertAfternoon(time, meeting_ptr); return;
	}
	return;
}

// replace with a linked list std::list
// return a pointer to a Meeting
Meeting* Room::getMeeting(int meetingTime) {
	std::list<Meeting*>::iterator it = Meetings.begin();
	while (it != Meetings.end()) {
		if ((*it)->getTime() == meetingTime) { return (*it); }
		++it;
	}
	return NULL;
}

// replace with a linked list std::list
// print all the meetings in the room in order 
void Room::printAllMeetings() {
	// room number header 
	std::cout << "--- Room " << roomNumber << " ---" << '\n';
	// check if Meetings list is empty
	std::list<Meeting*>::iterator it = Meetings.begin();
	if (it == Meetings.end()) { std::cout << "No Meetings are scheduled" << '\n'; return; }
	// loop and print in order 
	while (it != Meetings.end()) {
		// access KEY from element point by it
		int time = (*it)->getTime();
		// access VALUE from element pointed by it
		Meeting* meeting_pointer = (*it);
		// retrieve meeting topic and list of participants
		std::string topic = meeting_pointer->getTopic();
		// print out values
		std::cout << "Meeting time: " << time << ", " << "Topic: " << topic << '\n';
		// print out list of participants 
		meeting_pointer->printAllPeople();
		// go to the next node 
		++it;
	}
	return;
}
// return meeting info 
std::string Room::infoM() const{
	std::list<Meeting*>::const_iterator it = Meetings.begin();
	if (it == Meetings.end()) { return ""; }
	std::string RET;
	while (it != Meetings.end()) {
		// access time 
		std::string time = std::to_string((*it)->getTime());
		// access topic 
		std::string topic = (*it)->getTopic();
		// access number of participants
		std::string Participants = std::to_string((*it)->numberofParticipants());
		// concatenate 
		std::string ret = time + " " + topic + " " + Participants;
		RET = RET + ret + '\n';
		// if any participants, include them on each line (just last name)
		if (stoi(Participants) > 0) {
			std::string lastNames = (*it)->getParticipants();
			RET = RET + lastNames + '\n';
		}
		++it;
	}
	return RET;

}
// returns the number of meetings that the room is hosting today
int Room::sizeMeeting() {
	return Meetings.size();
}

// delete a single meeting given the time
void Room::deleteMeeting(int time) {
	// find proper meeting
	std::list<Meeting*>::iterator it = Meetings.begin();
	while (it != Meetings.end()) {
		if ((*it)->getTime() == time) { break; }
		++it;
	}
	// free the people in the meeting 
	std::map<std::string, Person*> people = (*it)->getPeople();
	std::map<std::string, Person*>::iterator person_it = people.begin();
	while (person_it != people.end()) {
		// free the person from this particular commitment 
		// no need to delete person, they can still participate in other meetings 
		person_it->second->free();
		++person_it;
	}
	// remove all people nodes after deallocating 
	people.clear();
	// deallocate the pointer first
	delete (*it);
	// now delete the empty/unwanted node 
	Meetings.erase(it);
	return;
}

// deallocating a meeting already knowing its iterator 
// free each participant from the meeting
void Room::deallocateMeeting(std::list<Meeting*>::iterator it) {
	// iterator at position of node going to be deleted 
	std::map<std::string, Person*> people = (*it)->getPeople();
	std::map<std::string, Person*>::iterator person_it = people.begin();
	// free the people from this particular commitment
	// no need to delete person, they can still participate in other meetings 
	while (person_it != people.end()) {
		person_it->second->free();
		++person_it;
	}
	// remove all people nodes after deallocating
	people.clear();
	// deallocate the Meeting pointer first 
	delete (*it);
	return;
}

// delete every single meeting in the room 
void Room::deleteAllMeetings() {
	std::list<Meeting*>::iterator it = Meetings.begin();
	while (it != Meetings.end()) {
		// deallocate the meeting_ptr first
		// takes care of people as well 
		deallocateMeeting(it);
		// nodes are coming to you 
		++it;
	}
	// after all memory management is good remove all the node from the list container
	Meetings.clear();
	return;
}

// delete all meetings before termination
void Room::deleteAllMeetings4Ever() {
	std::list<Meeting*>::iterator it = Meetings.begin();
	while (it != Meetings.end()) {
		// deallocate the meeting_ptr first
		delete(*it);
		// go to next node without having to worry about people 
		++it;
	}
	// after all memory management is good remove all the node from the list container
	Meetings.clear();
	return;
}
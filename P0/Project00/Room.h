/*
*	Filename: Room.h
*	This class represents a room defined by the user. The room is defined by
*	a room number and list of the meetings occuring in the room.
*/

#ifndef ROOM_H
#define ROOM_H


#include "Meeting.h"
#include <list>

class Room {
	// Private Data Members
private:
	// room number must be positive integer and must be unique
	int roomNumber;
	// the meetings in the room must be unique meetings; have different meeting times
	std::list<Meeting*> Meetings;

	// Public member functions
public:
	// Room constructor takes in a room number
	Room(int rNum);
	// return room number 
	int getRoomNumber(void) const;
	// insert meeting in the moring 9 - 12
	void insertMorning(int time, Meeting* meeting_ptr);
	// insert meeting in ther afternoon 1- 5
	void insertAfternoon(int time, Meeting* meeting_ptr);
	// add new meeting to the list of meetings 
	void newMeeting(int time, Meeting* meeting_ptr);
	// return a meeting
	Meeting* getMeeting(int meetingTime);
	// print the meetings in the room
	void printAllMeetings();
	// return meeting info 
	std::string infoM() const;
	// return how many meetings the room will host today
	int sizeMeeting();
	// delete a meeting given the time
	void deleteMeeting(int time);
	// delete a meeting already knowing its iterator 
	void deallocateMeeting(std::list<Meeting*>::iterator it);
	// delete every single meeting in the room 
	void deleteAllMeetings();
	// delete all meetings before termination
	void deleteAllMeetings4Ever();
};

#endif

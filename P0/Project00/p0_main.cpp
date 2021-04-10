/*
*	Project 0 | EECS 381
*	Task: Micro Meeting Manager
*	Developer: Gabriel Guerra
*	Date: 2-15-2021
*/
/*
*	Debugging Notes:
*	Technique1: Use the debugger to watch the program do its work, by stepping through the program one statement at a time -- break points.
*	Technique2: Use the debugger to show you a list of the calling stack frames in effect when the crash happened -- reading memory.
*/
/*
	Saturday :  type-ahead, reschedule function
	Sunday : Save/Load functions, Testing Files
*/

#include <iostream>
#include <fstream>
#include <map>
// #include "Utility.h"  // -- hierarchy -- 	
#include "Room.h"     // -- top -- 
#include "Meeting.h"  // -- middle --
#include "Person.h"   // -- bottom --

using namespace std;

/* function prototypes */
/* add functions */
void addPerson(map<string, Person*>& orderedTotalPeople);
void addRoom(map<int, Room*>& orderedTotalRooms);
void addMeeting(map<int, Room*>& orderedTotalRooms);
void addPersonToMeeting(map<string, Person*>& orderedTotalPeople, map<int, Room*>& orderedTotalRooms);

/* print functions */
void printPerson(const map<string, Person*>& orderedTotalPeople);
void printMeeting(const map<int, Room*>& orderedTotalRooms);
void printRoom(const map<int, Room*>& orderedTotalRooms);
void printAllPeople(const map<string, Person*>& orderedTotalPeople);
void printAllMeetings(const map<int, Room*>& orderedTotalRooms);
void printMemory(const map<string, Person*>& orderedTotalPeople, const map<int, Room*>& orderedTotalRooms);

/* delete functions */
void deletePerson(map<string, Person*>& orderedTotalPeople, map<int, Room*>& orderedTotalRooms);
void deleteMeeting(map<int, Room*>& orderedTotalRooms);
void deleteRoom(map<int, Room*>& orderedTotalRooms);
void deleteAllMeetings(map<int, Room*>& orderedTotalRooms);
void deleteAllPeople(map<string, Person*>& orderedTotalPeople, map<int, Room*>& orderedTotalRooms);
void deleteAll(map<string, Person*>& orderedTotalPeople, map<int, Room*>& orderedTotalRooms);
void deleteParticipant(map<string, Person*>& orderedTotalPeople, map<int, Room*>& orderedTotalRooms);

/* reschedule functions */
void rescheduleMeeting(map<int, Room*>& orderedTotalRooms);

/* save data functions */
void saveData(map<string, Person*>& orderedTotalPeople, map<int, Room*>& orderedTotalRoom);

/* load data functions */
void loadData(map<string, Person*>& orderedTotalPeople, map<int, Room*>& orderedTotalRoom);

/* search functions */
Room* validateNFindRoom(const map<int, Room*>& orderedTotalRooms);
Meeting* validateNFindMeeting(Room* room_ptr);

/* search helper functions*/
Person* findPerson(const map<string, Person*>& orderedTotalPeople, string lastName);
Room* findRoom(const map<int, Room*>& orderedTotalRooms, int roomNumber);
Meeting* findTime(Room* room_ptr, int time);

/* input validation helper function*/
int validRoomNumber(const map<int, Room*>& orderedTotalRooms);
int validTime(void);

/* stream helper functions */
void clearStreamState(void);
void loadPeople(std::ifstream& ifs, map<string, Person*>& orderedTotalPeople);
void loadRoom(std::ifstream& ifs, map<string, Person*>& orderedTotalPeople, map<int, Room*>& orderedTotalRoom);
bool get_int(istream& in_strm, int& x);

/* Error Function */
void error();

int main() {
	// oredered list of rooms by room numbers
	map<int, Room*> orderedTotalRooms;
	// oredered list of people by last name (strcmp, std::string::operator<)
	map<string, Person*> orderedTotalPeople;
	// describes desired program behavior 
	char command1, command2;
	// top level loop
	while (1) {
		// read the two command characters
		cout << "\nEnter  command: ";
		cin >> command1 >> command2;
		// all separate functions to carry out the work
		switch (command1) {
			// add command
		case 'a':
			switch (command2) {
			case 'i':
				// (add) individual command
				addPerson(orderedTotalPeople);
				break;
			case 'r':
				// (add) room command
				addRoom(orderedTotalRooms);
				break;
			case 'm':
				// (add) meeting command
				addMeeting(orderedTotalRooms);
				break;
			case'p':
				// (add) individual to meeting
				addPersonToMeeting(orderedTotalPeople, orderedTotalRooms);
				break;
			default:
				error();
				break;
			}
			// break from command1
			break;
			// print command
		case 'p':
			switch (command2) {
			case 'i':
				// (print) person coommand
				printPerson(orderedTotalPeople);
				break;
			case 'r':
				// (print) room command
				printRoom(orderedTotalRooms);
				break;
			case 'm':
				// (print) meeting 
				printMeeting(orderedTotalRooms);
				break;
			case 'g':
				// (print) all people in list
				printAllPeople(orderedTotalPeople);
				break;
			case 's':
				// (print) all meetings in all rooms
				printAllMeetings(orderedTotalRooms);
				break;
			case 'a':
				// (print) memory allocations
				printMemory(orderedTotalPeople, orderedTotalRooms);
				break;
			default:
				error();
				break;
			}
			break;
			// delete command
		case 'd':
			switch (command2) {
			case 'i':
				// (delete) person
				deletePerson(orderedTotalPeople, orderedTotalRooms);
				break;
			case 'r':
				// (delete) room
				deleteRoom(orderedTotalRooms);
				break;
			case 'm':
				// (delete) meeting
				deleteMeeting(orderedTotalRooms);
				break;
			case 's':
				// (delete) all meeting from all rooms
				deleteAllMeetings(orderedTotalRooms);
				break;
			case 'g':
				// (delete) all individuals
				deleteAllPeople(orderedTotalPeople, orderedTotalRooms);
				break;
			case 'a':
				deleteAll(orderedTotalPeople, orderedTotalRooms);
				break;
			case 'p':
				// (delete) participant in meeting
				deleteParticipant(orderedTotalPeople, orderedTotalRooms);
				break;
			default:
				error();
				break;
			}
			break;
		case 'r':
			switch (command2) {
			case 'm':
				// (reschedule) meeting
				rescheduleMeeting(orderedTotalRooms);
				break;
			default:
				error();
				break;
			}
			break;
		case 's':
			switch (command2) {
			case 'd':
				// (save) data
				saveData(orderedTotalPeople, orderedTotalRooms);
				break;
			default:
				error();
				break;
			}
			break;
		case 'l':
			switch (command2) {
			case 'd':
				// (load) data
				loadData(orderedTotalPeople, orderedTotalRooms);
				break;
			default:
				error();
				break;
			}
			break;
		case 'q':
			switch (command2) {
				// allowing the program to reach the return 0 from main terminates the program 
				// Terminate with a return from amin which completes deallocation of all memory
				// DELETE ALL CONTAINERS ON HEAP BEFORE TERMINATING
			case 'q':
				deleteAll(orderedTotalPeople, orderedTotalRooms);
				cout << "Done" << '\n';
				return 0;
			default:
				error();
				break;
			}
		default:
			error();
			break;
		}
	}
}

/*
	Possible Commands:
REFACTOR!!!!!!!!!!!!!!!!!!
[DONE]  (1) pi<lastname>
[DONE]  (2) pr<room>
[DONE]  (3) pm<room><time>
[DONE]  (4) ps
[DONE]  (5) pg
[DONE]  (6) pa
[DONE]	(7) ai<firstname><lastname><phone number>
[DONE]	(8) ar<room>
[DONE]  (9) am<room><time><topic>
[DONE] (10) ap
[DONE] (11) rm
[DONE] (12) di<lastname>
[DONE] (13) dr<room>
[DONE] (14) dm<room><time>
[DONE] (15) dp<room><time><lastname>
[DONE] (16) ds
[DONE] (17) dg
[DONE] (18) da
[DONE] [3](19) sd<filename>
[DONE] [4](20) ld<filename>
[DONE] (21) qq
*/

/* add functions */
// ai <firstname> <lastname> <phone number> - add an individual person to the people list. 
// Errors: A person with that last name is already in the people list.
void addPerson(map<string, Person*>& orderedTotalPeople) {
	// no invalid characters if you are reading a string
	string firstName, lastName, phoneNumber;
	cin >> firstName >> lastName >> phoneNumber;
	// check if person already exists with lastName
	if (findPerson(orderedTotalPeople, lastName)) {
		// only clear state and ignore type-ahead feature if some goes wrong 
		clearStreamState();
		cout << "There is already a person with this last name!" << '\n';
		return;
	}
	// dynamically allocate Person 
	Person* personPtr = new Person(firstName, lastName, phoneNumber);
	// add new person to the list
	orderedTotalPeople[lastName] = personPtr;
	cout << "Person " << lastName << " added" << '\n';
	return;
}

// ar <room> -add a room with the specified number.
// Errors: room number out of range; room of that number already exits.
void addRoom(map<int, Room*>& orderedTotalRooms) {
	int roomNumber; Room* room_ptr;
	// check if the input is valid before using it
	if ((roomNumber = validRoomNumber(orderedTotalRooms)) < 0) { clearStreamState(); return; }
	// check if room number already exists 
	else if (room_ptr = findRoom(orderedTotalRooms, roomNumber)) { cout << "There is already a room with this number!" << '\n'; clearStreamState(); return; }
	else {
		// create room number if it does not exist and has proper input
		Room* room_ptr = new Room(roomNumber);
		// add new room to the list of rooms 
		orderedTotalRooms[roomNumber] = room_ptr;
		cout << "Room " << roomNumber << " added" << '\n';
		return;
	}
}

// am <room> <time> <topic> - add a meeting in a specified room, at a specified time, and on a specified topic. 
// Errors: room number out of range; no room of that number; time out of range; a meeting at that time already exists in that room.
void addMeeting(map<int, Room*>& orderedTotalRooms) {
	int roomNumber, time; string topic; Room* room_ptr; Meeting* meeting_ptr;
	// check if room number is valid and stream is good 
	if ((roomNumber = validRoomNumber(orderedTotalRooms)) < 0) { clearStreamState(); return; }
	// check if room number exists 
	else if ((room_ptr = findRoom(orderedTotalRooms, roomNumber)) == NULL) { cout << "No room with that number!" << '\n'; clearStreamState(); return; }
	// check if time is valid and stream is good 
	else if ((time = validTime()) < 0) { clearStreamState(); return; }
	// check if meeting with that time already exists 
	else if ((meeting_ptr = findTime(room_ptr, time))) { cout << "There is already a meeting at that time!" << '\n'; clearStreamState(); return; }
	else {
		// if all good with the integer values read the topic
		cin >> topic;
		// create new meeting with given arguments 
		meeting_ptr = new Meeting(time, topic);
		// add meeting in the specified room  
		room_ptr->newMeeting(time, meeting_ptr);
		cout << "Meeting added at " << time << '\n';
		return;
	}
}

// ap <room> <time> <lastname> - add a specified person as a participant in a specified meeting. 
// Errors: room number out of range; no room of that number; time out of range, no meeting at that time, 
// no person in the people list of that name; there is already a participant of that name.
void addPersonToMeeting(map<string, Person*>& orderedTotalPeople, map<int, Room*>& orderedTotalRooms) {
	string lastName; Room* room_ptr; Person* person_ptr; Meeting* meeting_ptr;
	// check room 
	if ((room_ptr = validateNFindRoom(orderedTotalRooms)) == NULL) { return; }
	// check time 
	else if ((meeting_ptr = validateNFindMeeting(room_ptr)) == NULL) { return; }
	else {
		// if all good with integer values read the topic 
		cin >> lastName;
		// check if person exist in the people list
		if ((person_ptr = findPerson(orderedTotalPeople, lastName)) == NULL) { cout << "No person with that name!" << '\n'; clearStreamState(); return; }
		// check if the person is already a participant
		else if ((meeting_ptr)->registeredPerson(lastName)) { cout << "This person is already a participant!" << '\n'; clearStreamState(); return; }
		else {
			// if EVERYTHING is gucci add the person as a participant to the meeting
			meeting_ptr->addParticipant(lastName, person_ptr);
			cout << "Participant " << lastName << " added" << '\n';
			// make sure ther person committments lists is update to show that they are busy and cannot be deleted
			person_ptr->addCommitment();
		}
	}
	return;
}



/* print functions */
// pi <lastname>- print the specified individual person information. 
// Errors: no person with that last name. 
void printPerson(const map<string, Person*>& orderedTotalPeople) {
	string lastName; Person* person_ptr;
	cin >> lastName;
	// if the person with the given lastname exists output there information
	if (person_ptr = findPerson(orderedTotalPeople, lastName)) {
		person_ptr->info();
		clearStreamState();
		return;
	}
	// Error message 
	cout << "No person with that name!" << '\n';
	return;
}

// pr <room> - print the meetings in a room with the specified number. 
// Errors: room number out of range; no room of that number.
void printRoom(const map<int, Room*>& orderedTotalRooms) {
	Room* room_ptr;
	// check room 
	if ((room_ptr = validateNFindRoom(orderedTotalRooms)) == NULL) { return; }
	// if input is good and meets all conditions 
	room_ptr->printAllMeetings();
	return;
}

// pm <room> <time> -print the time, topic, and participants(full nameand phone number) for a specified meeting.
// Errors: room number out of range; no room of that number; time out of range, no meeting at that time.
void printMeeting(const map<int, Room*>& orderedTotalRooms) {
	int roomNumber, time; Room* room_ptr; Meeting* meeting_ptr;
	// check room 
	if ((room_ptr = validateNFindRoom(orderedTotalRooms)) == NULL) { return; }
	// check time 
	else if ((meeting_ptr = validateNFindMeeting(room_ptr)) == NULL) { return; }
	// if all good print info 
	meeting_ptr->info();
	return;
}

// ps - print the meeting information (same information as pm) for all meetings in all rooms. 
// Errors: none. (It is not an error if there are no meetings - that is a valid possibility.)
void printAllMeetings(const map<int, Room*>& orderedTotalRooms) {
	std::map<int, Room*>::const_iterator it = orderedTotalRooms.begin();
	if (it == orderedTotalRooms.end()) { cout << "List of rooms is empty" << '\n'; clearStreamState(); return; }
	// loop through the rooms to print out all the meetings
	cout << "Information for " << orderedTotalRooms.size() << " rooms:" << '\n';
	while (it != orderedTotalRooms.end()) {
		Room* room_ptr = it->second;
		room_ptr->printAllMeetings();
		++it;
	}
	return;
}

// pg - print the individual information (same information as pi) for all people in the person list. 
// Errors: none. (It is not an error if there are no people - that is a valid possibility.)
void printAllPeople(const map<string, Person*>& orderedTotalPeople) {
	if (orderedTotalPeople.size() == 0) { cout << "List of people is empty" << '\n'; clearStreamState(); return; }
	// if people exist then print them out 
	std::map<string, Person*>::const_iterator it = orderedTotalPeople.begin();
	cout << "Information for " << orderedTotalPeople.size() << " people:" << '\n';
	while (it != orderedTotalPeople.end()) {
		Person* person_ptr = it->second;
		person_ptr->info();
		++it;
	}
	return;
}

// pa - print memory allocations. Errors: none. In Project 0, this command outputs the number of 
// people in the person list, the number of rooms in the room list, and the number of meetings 
// currently scheduled in all rooms; it does not show the actual amount of memory allocated for this data.
void printMemory(const map<string, Person*>& orderedTotalPeople, const map<int, Room*>& orderedTotalRooms) {
	// find out how many meetings in total 
	int totalMeetings = 0;
	std::map<int, Room*>::const_iterator it = orderedTotalRooms.begin();
	while (it != orderedTotalRooms.end()) {
		Room* room_ptr = it->second;
		totalMeetings += room_ptr->sizeMeeting();
		++it;
	}
	cout << "Memory allocations: " << '\n';
	cout << "Persons: " << orderedTotalPeople.size() << '\n';
	cout << "Meetings: " << totalMeetings << '\n';
	cout << "Rooms: " << orderedTotalRooms.size() << '\n';
	return;
}


/* delete functions */
// di <lastname> - delete a person from the people list, but only if he or she is not a participant in a meeting. 
// Errors: No person of that name; person is a participant in a meeting.
void deletePerson(map<string, Person*>& orderedTotalPeople, map<int, Room*>& orderedTotalRooms) {
	string lastName; Person* person_ptr;
	cin >> lastName;
	// if the person with that lastname exists
	if (person_ptr = findPerson(orderedTotalPeople, lastName)) {
		// checking if the person is participating in a meeting, if so you can not delete
		if ((person_ptr->busy())) { cout << "This person is a participant in a meeting" << '\n'; clearStreamState(); return; }
		// release memory pointed by pointer but the invalid pointer still exists 
		delete person_ptr;
		// erase from key-value pair if the person is not a participant in a meeting
		orderedTotalPeople.erase(lastName);
		cout << "Person " << lastName << " deleted" << '\n';
		clearStreamState();
		return;
	}
	cout << "No person with that name!" << '\n';
	return;
}

// dr <room> - delete the room with the specified number, including all of the meetings scheduled in that room - conceptually,
// unless the meetings have been rescheduled into another room, taking the room out of the list of meeting rooms means that its
// meetings are all canceled.Errors: room number out of range; no room of that number.
void deleteRoom(map<int, Room*>& orderedTotalRooms) {
	int roomNumber; Room* room_ptr;
	string lastName;
	// check room 
	if ((room_ptr = validateNFindRoom(orderedTotalRooms)) == NULL) { return; }
	// if all condition good delete all meetings before deleting room 
	room_ptr->deleteAllMeetings();
	// grab room number before deleting pointer 
	roomNumber = room_ptr->getRoomNumber();
	// deallocate room pointer
	delete room_ptr;
	// erase from the map 
	orderedTotalRooms.erase(roomNumber);
	cout << "Room " << roomNumber << " deleted" << '\n';
	return;
}

// dm <room> <time> - delete a meeting. 
// Errors: room number out of range; no room of that number; time out of range; no meeting at that time
void deleteMeeting(map<int, Room*>& orderedTotalRooms) {
	int roomNumber, time; Room* room_ptr; Meeting* meeting_ptr;
	// check room 
	if ((room_ptr = validateNFindRoom(orderedTotalRooms)) == NULL) { return; }
	// check time 
	else if ((meeting_ptr = validateNFindMeeting(room_ptr)) == NULL) { return; }
	// grab meeting time 
	time = meeting_ptr->getTime();
	// if all good delete meeting 
	room_ptr->deleteMeeting(time);
	// output
	cout << "Meeting at " << time << " deleted" << '\n';
	return;
}

// ds - delete schedule - delete all meetings from all rooms. 
// Errors: none.
void deleteAllMeetings(map<int, Room*>& orderedTotalRooms) {
	std::map<int, Room*>::iterator it = orderedTotalRooms.begin();
	while (it != orderedTotalRooms.end()) {
		// delete all meetings from each room in order
		it->second->deleteAllMeetings();
		++it;
	}
	// not deleting the actual rooms! 
	cout << "All meeting deleted" << '\n';
	return;
}

// dg - delete all of the individual information, but only if there are no meetings scheduled. Logically this is overkill; it would
// suffice if there are no participants in any meetings, but this specification is made for simplicity.Errors: There are scheduled
// meetings
void deleteAllPeople(map<string, Person*>& orderedTotalPeople, map<int, Room*>& orderedTotalRooms) {
	// cannot delete all of the individuals if there are meetings schedule 
	std::map<int, Room*>::iterator it = orderedTotalRooms.begin();
	while (it != orderedTotalRooms.end()) {
		if ((it->second->sizeMeeting()) > 0) { cout << "Cannot clear people list unless there are no meetings!" << '\n'; clearStreamState(); return; };
		++it;
	}
	// if no meetings in any of the rooms, now we can delete every person 
	std::map<string, Person*>::iterator person_it = orderedTotalPeople.begin();
	while (person_it != orderedTotalPeople.end()) {
		// deallocate all pointers first
		delete (person_it->second);
		++person_it;
	}
	// clear the entire people list
	orderedTotalPeople.clear();
	cout << "All persons deleted" << '\n';
	return;

}

// da - delete all - deletes all of the rooms and their meetings (as in dr) and then deletes all individuals in the people list.
// Errors:none.
void deleteAll(map<string, Person*>& orderedTotalPeople, map<int, Room*>& orderedTotalRooms) {
	// deallocate all people
	std::map<string, Person*>::iterator person_it = orderedTotalPeople.begin();
	while (person_it != orderedTotalPeople.end()) {
		delete (person_it->second);
		++person_it;
	}
	// delete all elements in rhe people container list 
	orderedTotalPeople.clear();
	// deallocate all meetings and rooms 
	std::map<int, Room*>::iterator room_it = orderedTotalRooms.begin();
	while (room_it != orderedTotalRooms.end()) {
		// delete all meetings from the room; function takes care of memory management and deletes container 
		((room_it->second)->deleteAllMeetings4Ever());
		// deallocate the room
		delete (room_it->second);
		++room_it;
	}
	// delete all elements in room container 
	orderedTotalRooms.clear();
	cout << "All rooms and meetings deleted" << '\n';
	cout << "All persons deleted" << '\n';
	return;
}

// dp <room> <time> <lastname> - delete a specified person from the participant list for a specified meeting. Errors: room
// number out of range; no room of that number; time out of range, no meeting at that time, no person of that name in the people
// list; no person of that name in the participant list.
void deleteParticipant(map<string, Person*>& orderedTotalPeople, map<int, Room*>& orderedTotalRooms) {
	string lastName; Room* room_ptr; Person* person_ptr; Meeting* meeting_ptr;
	// check room 
	if ((room_ptr = validateNFindRoom(orderedTotalRooms)) == NULL) { return; }
	// check time 
	else if ((meeting_ptr = validateNFindMeeting(room_ptr)) == NULL) { return; }
	else {
		// validate Person 
		// check if person exist in the people list
		cin >> lastName;
		// if the pointer is NULL ther person does not exist 
		if ((person_ptr = findPerson(orderedTotalPeople, lastName)) == NULL) { cout << "No person with that name!" << '\n'; clearStreamState(); return; }
		// person exists but that name is not in the participant list 
		else if (!(meeting_ptr->registeredPerson(lastName))) { cout << "This person is not a participant in the meeting!" << '\n'; clearStreamState(); return; }
		else {
			// if EVERYTHING is gucci delete the person as a participant to the meeting
			// if all good delete person from Meeting
			// in delete participant already calling free() for the participnt
			meeting_ptr->deleteParticipant(lastName);
			cout << "Participant " << lastName << " deleted" << '\n';
		}
	}
	return;
}


/* reschedule functions */
// rm 1001 10 1002 12 
// rm <old room> <old time> <new room> <new time> - reschedule a meeting by changing its room and/or time (without
// changing or reentering topic or participants). Each parameter is read and its value checked before going on to the next
// parameter. Actually changing the schedule is not done until all parameters have been read and checked. 
// Errors: old room number out of range; old room does not exist; old time is out of range; no meeting at that time in the old room; new room
// number out of range, new room does not exist; new time is out of range; a meeting at the new time already exists in the new
// room. To keep the logic simpler, the last error will result if the user attempts to reschedule a meeting to be in the same room and
// at the same time as it is currently.
void rescheduleMeeting(map<int, Room*>& orderedTotalRooms) {
	int oldRoom, oldTime, newRoom, newTime; Room* room_ptr_old, * room_ptr_new; Meeting* meeting_ptr_old, * meeting_ptr_new;
	// check old room and old meeting
	if ((room_ptr_old = validateNFindRoom(orderedTotalRooms)) == NULL) { return; }
	else if ((meeting_ptr_old = validateNFindMeeting(room_ptr_old)) == NULL) { return; }
	// check new room 
	else if ((room_ptr_new = validateNFindRoom(orderedTotalRooms)) == NULL) { return; }
	// validate new time and check if a meeting already exists at new time; we cannot reschedule to a time that already contains a meeting; ideally we will get back NULL 
	else if ((newTime = validTime()) < 0) { clearStreamState(); return; }
	else if ((meeting_ptr_new = findTime(room_ptr_new, newTime))) { cout << "There is already a meeting at that time!" << '\n'; clearStreamState(); return; }
	// last error check 
	else if ((room_ptr_old == room_ptr_new) && ((meeting_ptr_old->getTime()) == newTime)) { cout << "Cannot reschedule to the same room and time!"; clearStreamState(); return; }
	else {
		// if EVERYTHING is good 
		// have to copy topic and participants before deleting using a copy constructor   
		meeting_ptr_new = new Meeting(*meeting_ptr_old);
		// set new time for the meeting 
		meeting_ptr_new->setTime(newTime);

		// remove meeting in old room; this subtracts 1 committment from the people
		room_ptr_old->deleteMeeting((meeting_ptr_old->getTime()));

		// add meeting in new room 
		room_ptr_new->newMeeting(newTime, meeting_ptr_new);
		meeting_ptr_new->addCommitments();

		cout << "Meeting rescheduled to room " << room_ptr_new->getRoomNumber() << " at " << newTime << '\n';
	}
	return;
}


/* save data functions */
// sd <filename> -save data - writes the people, rooms, and meetings data to the named file.
// Errors: the file cannot be opened for output.
void saveData(map<string, Person*>& orderedTotalPeople, map<int, Room*>& orderedTotalRoom) {
	// read in given file name 
	string filename;
	cin >> filename;
	// ask OS to create new empty file | local so it will be destroyed outside the function scope   
	ofstream output_file(filename);
	// if file cannot be opened for output 
	if (!output_file.is_open()) {
		cout << "Output file could not be opened!" << '\n';
		return;
	}
	// first line 
	int numberOfPeople = orderedTotalPeople.size();
	output_file << numberOfPeople << '\n';
	// firstname, lastname, and phonenumber for each person (one per line)
	std::map<string, Person*>::iterator person_it = orderedTotalPeople.begin();
	while (person_it != orderedTotalPeople.end()) {
		string info = person_it->second->infoS();
		output_file << info << '\n';
		++person_it;
	}
	// number of rooms on its own line 
	int numberOfRooms = orderedTotalRoom.size();
	output_file << numberOfRooms << '\n';
	// room number and number of meetings for the first room 
	std::map<int, Room*>::iterator room_it = orderedTotalRoom.begin();
	while (room_it != orderedTotalRoom.end()) {
		int roomNumber = room_it->second->getRoomNumber();
		int numberOfMeetings = room_it->second->sizeMeeting();
		output_file << roomNumber << " " << numberOfMeetings << '\n';
		// the time, topic, and number of participants in the first meeting (all meetings) 
		string meetingsInfo = room_it->second->infoM();
		output_file << meetingsInfo;
		// last names of each participant (one per line) 
		++room_it;
	}
	// close file 
	output_file.close();
	// notify user
	cout << "Data saved" << '\n';
	return;
}


/* load data functions */
// ld <filename> - load data - restores the program state from the data in the file. Errors: the file cannot be opened for input;
// invalid data is found in the file (e.g. the file wasn't created by the program). In more detail, the program first attempts to open
// the file, and if not successful simply reports the error and prompts for a new command. If successful, it deletes all current data,
// and then attempts to read the people, rooms, and meetings data from the named file, which should restore the program state to
// be identical to the time the data was saved. If an error is detected during reading the file, the error is reported and any data
// previously read is discarded, leaving all the lists empty. 
void loadData(map<string, Person*>& orderedTotalPeople, map<int, Room*>& orderedTotalRoom) {
	string filename;
	cin >> filename;
	// create input file stream object 
	ifstream input_file(filename);
	// if disk file cannot be opened for input 
	if (!input_file.is_open()) { cout << "Input file could not be opened!" << '\n'; return; }
	// find out the error and report it to the user if encountered

	// if successful, delete all current data
	deleteAll(orderedTotalPeople, orderedTotalRoom);
	// reads the people, rooms, and meetings data from file and restore that state 
	// read number of people and create the people
	loadPeople(input_file, orderedTotalPeople);
	// load rooms in the file  
	// load meetings in the appropriate rooms 
	// add people in the appropriate meeting 
	loadRoom(input_file, orderedTotalPeople, orderedTotalRoom);

	cout << "Data loaded" << '\n';
	return;
}


/* utility functions*/
// checks if the Person with certain last name already exists 
// returns a pointer to the person if they do or NULL if they do not
// NULL and not-NULL pointers act like 0 and 1 
Person* findPerson(const map<string, Person*>& orderedTotalPeople, string lastName) {
	if (orderedTotalPeople.find(lastName) != orderedTotalPeople.end()) { return orderedTotalPeople.at(lastName); }
	return NULL;
}

// checks if the Room with certain room number already exists 
// returns a pointer to the person if they do or NULL if they do not
// NULL and not-NULL pointers act like 0 and 1 
Room* findRoom(const map<int, Room*>& orderedTotalRooms, int roomNumber) {
	if (orderedTotalRooms.find(roomNumber) != orderedTotalRooms.end()) { return orderedTotalRooms.at(roomNumber); }
	return NULL;
}

// checking if there is a meeting at that time already 
Meeting* findTime(Room* room_ptr, int time) {
	Meeting* meeting_ptr;
	// check if a meeting at that time already exists in that room 
	if (meeting_ptr = (room_ptr->getMeeting(time))) { return meeting_ptr; }
	return NULL;
}

// check if the room and input is valid before using it 
int validRoomNumber(const map<int, Room*>& orderedTotalRooms) {
	// local roomNumber 
	int roomNumber;
	// check for a good stream state
	if (cin >> roomNumber) {
		// check if room number is out of range
		if (roomNumber < 0) { cout << "Room number is not in range!" << '\n'; return -1; }
	}
	else {
		// clear state if it is in a bad state
		cout << "Could not read an integer value!" << '\n';
		return -1;
	}
	// proper room number will always be greate than non-negative 
	return roomNumber;
}

// checking if the time is out of range or invalid input 
int validTime(void) {
	int time;
	// need to check state because looking for int value
	if (cin >> time) {
		// check if time out of range {9, 10, 11, 12, 1, 2, 3, 4, 5}
		if (time > 12 || time < 1 || (time > 5 && time < 9)) { cout << "Time is not in range!" << '\n'; return -1; }
	}
	else {
		cout << "Could not read an integer value!" << '\n';
		return -1;
	}
	return time;
}

/* search functions */
// does all the validation and returns room if it exists
Room* validateNFindRoom(const map<int, Room*>& orderedTotalRooms) {
	int roomNumber; Room* room_ptr;
	// check if the input is valid before using it, if not clear stream and return NULL 
	if ((roomNumber = validRoomNumber(orderedTotalRooms)) < 0) { clearStreamState(); return NULL; }
	// check if room exists 
	else if ((room_ptr = findRoom(orderedTotalRooms, roomNumber)) == NULL) { cout << "No room with that number!" << '\n'; clearStreamState(); return NULL; }
	return room_ptr;
}

// does all the validation and returns room if it exists 
Meeting* validateNFindMeeting(Room* room_ptr) {
	int time; Meeting* meeting_ptr;
	// check if time is valid and stream is good 
	if ((time = validTime()) < 0) { clearStreamState(); return NULL; }
	// check if there even is a meeting at that time 
	else if ((meeting_ptr = findTime(room_ptr, time)) == NULL) { cout << "No meeting at that time!" << '\n'; clearStreamState(); return NULL; }
	return meeting_ptr;
}


// reset the stream state to good and clear out the garbage input 
void clearStreamState(void) {
	// clear the state
	cin.clear();
	// skip the offending material 
	while (cin.get() != '\n');
	return;
}

// load person state from file
void loadPeople(std::ifstream& ifs, map<string, Person*>& orderedTotalPeople) {
	int x; 
	// first line (number of people)
	ifs >> x; 
	// read x lines to get x people in list 
	string first, second, number;
	int count = 0;
	while (count < x) {
		ifs >> first >> second >> number; 
		// dynamically allocate person 
		Person* personPtr = new Person(first, second, number);
		// add person to the list 
		orderedTotalPeople[second] = personPtr;
		++count;
	}
	return;
}

// load room state from file 
void loadRoom(std::ifstream& ifs, map<string, Person*>& orderedTotalPeople, map<int, Room*>& orderedTotalRoom) {
	int x; int roomCount = 0;
	// 1 + x people + 1 line (number of rooms) | iterate more on the next project 
	bool continue_flag = get_int(ifs, x);
	if (!continue_flag) { return;  }

	// read x lines to get x rooms in list 
	int roomNumber; int numOfMeetingsInRoom;

	while (roomCount < x) {
		// get room number
		continue_flag = get_int(ifs, roomNumber);
		if (!continue_flag) { return; }
		// get number of meetings in room
		continue_flag = get_int(ifs, numOfMeetingsInRoom);
		if (!continue_flag) { return; }
		// create room 
		Room* roomPtr = new Room(roomNumber);


		// add new room to list 
		orderedTotalRoom[roomNumber] = roomPtr;

		int numMeetings = 0;
		while (numMeetings < numOfMeetingsInRoom) {
			// add meetings into the room 
			int time; string topic; int numOfPeople;
			continue_flag = get_int(ifs, time);
			if (!continue_flag) { return; }
			ifs >> topic;
			continue_flag = get_int(ifs, numOfPeople);
			if (!continue_flag) { return; }
			// create new meeting
			Meeting* meetingPtr = new Meeting(time, topic);
			// add meeting in the specified room
			roomPtr->newMeeting(time, meetingPtr);

			// add people into those meetings 
			if (numOfPeople > 0) {
				int peeps = 0;
				while (peeps < numOfPeople) {
					string last;
					ifs >> last;
					// Point to person 
					Person* personPtr = orderedTotalPeople.at(last);
					personPtr->info();
					// add person to meeting
					meetingPtr->addParticipant(last, personPtr);
					// update person's commitment 
					personPtr->addCommitment();
					// next person 
					++peeps;
				}
			}
			// go to next meeting not next room 
			++numMeetings;
		}
		cout << "Next room" << '\n';
		// go to next room 
		++roomCount;
	}
	return; 
}

// error handles reading an int from a file 
bool get_int(istream& in_strm, int& x) {
	bool continue_flag;
	in_strm >> x;
	// check if stream is good 
	if (in_strm.good()) {
		continue_flag = true;
	}
	else if (in_strm.eof()) {
		cout << "End of File encountered." << '\n';
		continue_flag = true;
	}
	else if (in_strm.bad()) {
		cout << "Hard I/O Error." << '\n';
		continue_flag = false;
	}
	else if (in_strm.fail()) {
		cout << "Invalid input - deleting everything" << '\n';
		in_strm.clear();
		continue_flag = false;
	}
	return continue_flag;
}




// tells the user input the command is not recognizable
void error(void) {
	cout << "Unrecognized command!" << '\n';
	clearStreamState();
	return;
}
# Makefile for project 0 

# Variables are used for ease of modification
CC = g++

# specify compile and link options 
CFLAGS = -std=c++17 -pedantic-errors
LFLAGS = -Wall
TARGET = proj0


# following asks for executable to be built 
all: $(TARGET)

# to build this executable, check to see if any of the listed object files 
# need to be rebuilt and do so, then link to create the executable
$(TARGET): p0_main.o Person.o Meeting.o Room.o
	$(CC) $(LFLAGS) p0_main.o Person.o Meeting.o Room.o -o $(TARGET)

p0_main.o:  p0_main.cpp Person.h Meeting.h Room.h 
	$(CC) $(CFLAGS) -c p0_main.cpp 

Person.o: Person.cpp Person.h
	$(CC) $(CFLAGS) -c Person.cpp

Meeting.o: Meeting.cpp Meeting.h Person.h
	$(CC) $(CFLAGS) -c Meeting.cpp 

Room.o: Room.cpp Room.h Meeting.h
	$(CC) $(CFLAGS) -c Room.cpp 

# other shell commands 
clean:
	rm -f *.o
real_clean:
	rm -f *.o
	rm -f $(TARGET)


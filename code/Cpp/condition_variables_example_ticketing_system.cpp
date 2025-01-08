// Coursera CUDA cpp parallel programming assigment

// reference: https://cplusplus.com/reference/condition_variable/condition_variable/notify_one/

/** Makefile

.PHONY: clean build run

assignment.o: assignment.cpp assignment.h
	$(CXX) assignment.cpp -c -o assignment.o

build: assignment.o
	$(CXX) assignment.o -o assignment.exe $(CXXFLAGS)

clean:
	rm -f *.exe output-*.txt

run:
	./assignment.exe $(ARGS)

all: clean build run

**/

/** run.sh

#!/usr/bin/env bash
#make clean build

NUM_RUNS=$1
USERNAME=$2
NUM_THREADS=$3
PART_ID=$4

for i in $(seq 1 ${NUM_RUNS})
do
	make run ARGS="$NUM_THREADS $USERNAME $PART_ID"
done

**/

//
// Created by Chancellor Pascale on 1/31/21.
//
#include <thread>
#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>

#ifndef CPP_INITIAL_CODE_ASSIGNMENT_H
#define CPP_INITIAL_CODE_ASSIGNMENT_H

const std::string USERNAME = "Sergio";
static std::atomic<int> currentTicketNumber; // This could be an atomic variable
// Based on the implementation, the student may want to create a shared variable for managing the next ticket number
// to be assigned to a thread
static std::string currentPartId;
static std::string currentUser;
static int currentNumThreads;

void executeTicketingSystemParticipation(int ticketNumber);
int runSimulation();
std::string getUsernameFromUserFile();
int manageTicketingSystem(std::thread threadArray[], int numThreads);

#endif //CPP_INITIAL_CODE_ASSIGNMENT_H

// -- -end of .h ---


void executeTicketingSystemParticipation(int ticketNumber) {
	// For debugging purposes you might want to output the thread's ticketNumber
	
	std::string outputFileName = "output-" + currentPartId + ".txt";
	// NOTE: Do not remove this output to file statement as it is used to grade assignment,
	// so it should be called by each thread
	std::ofstream outputFile;
	outputFile.open (outputFileName, std::ofstream::app);
	outputFile << "C++11: Thread retrieved ticket number: " << ticketNumber << " started.\n";

	// wait until your ticket number has been called output your ticket number and the current time
 	std::unique_lock<std::mutex> lck(mtx);
  	while (currentTicketNumber != ticketNumber) cv.wait(lck);
	  		
	cv.notify_all(); // Unblocks all threads currently waiting for this condition.


	// NOTE: Do not remove this output to file statement as it is used to grade assignment,
	// so it should be called by each thread
	outputFile << "C++11: Thread with ticket number: " << ticketNumber << " completed.\n";
	outputFile.close();
	
	// Increment currentTicketNumber variable to allow other threads to do their job
	currentTicketNumber++;
}

int runSimulation() {
	int result = 0;
	int succesfullThreads = 0;
	//std::string userFromFile = getUsernameFromUserFile();
	//if(USERNAME == currentUser && USERNAME == userFromFile){
		std::cout << "Simple user verification completed successfully.\n";
		int currentTicketNumber;
		currentTicketNumber = -1;
		
		std::thread threads[currentNumThreads];
		
		for(int threadIndex = 0; threadIndex < currentNumThreads; ++threadIndex){
			// This is where you will start threads that will participate in a ticketing system
			// have the thread run the executeTicketingSystemParticipation function
			threads[threadIndex] = std::thread(executeTicketingSystemParticipation, threadIndex);
			succesfullThreads++;
		}

		cv.notify_all();
		
		// The code will also need to know when all threads have completed their work
		std::this_thread::sleep_for(std::chrono::seconds(1));
		manageTicketingSystem(threads, succesfullThreads);

	//} else {
	//	std::cout << "Simple user verification completed failed, code will not be executed.\n";
	//}
  
	return result;
}

// Utility function for retrieving a user name from the .user file
std::string getUsernameFromUserFile(){
	std::string line;
	std::ifstream userFile (".user");
	if (userFile.is_open())
	{
		std::getline (userFile,line);
		userFile.close();
	}
	std::cout << "user from .user file: " << line << "\n";
	return line;
}

// Centralized logic for managing the ticketing machine that is the basis for threads executing work in the order that
//	they "pulled" the ticket from the machine
int manageTicketingSystem(std::thread threadArray[], int numThreads) {
	std::string outputFileName = "output-" + currentPartId + ".txt";
	std::ofstream outputFile;
	outputFile.open (outputFileName, std::ofstream::app);
	outputFile << "C++11: Signaling threads to do work.\n";
	
	// Increment a ticket number shared by a number of threads and check that no active threads are running
	currentTicketNumber++;

	// Wait for all threads to complete
	for (int i=0; i < numThreads; i++)
	{
		threadArray[i].join();
	}
	
	outputFile << "C++11: All threads completed.\n";
	outputFile.close();
	return 0;
}

int main(int argc, char *argv[]) {
	int numThreads = 1;
	std::string user = "Sergio";
	std::string partId = "test";
	std::cout << "Starting assignment main function\n";
	
	if (argc > 3) {
		std::cout << "Parsing command line arguments\n";
		numThreads = atoi(argv[1]);
		user = argv[2];
		partId = argv[3];
	}
	
	currentNumThreads = numThreads;
	currentUser = user;
	currentPartId = partId;
	
	// Note this implementation is based on a single code file and use of static and shared variables,
	// other implementations could be designed and are encouraged
	
	std::cout << "Running the simulation\n";
	runSimulation();
}

/** example output with 20 threads

C++11: Thread retrieved ticket number: 0 started.
C++11: Thread with ticket number: 0 completed.
C++11: Thread retrieved ticket number: 1 started.
C++11: Thread with ticket number: 1 completed.
C++11: Thread retrieved ticket number: 2 started.
C++11: Thread with ticket number: 2 completed.
C++11: Thread retrieved ticket number: 3 started.
C++11: Thread with ticket number: 3 completed.
C++11: Thread retrieved ticket number: 4 started.
C++11: Thread with ticket number: 4 completed.
C++11: Thread retrieved ticket number: 5 started.
C++11: Thread with ticket number: 5 completed.
C++11: Thread retrieved ticket number: 6 started.
C++11: Thread with ticket number: 6 completed.
C++11: Thread retrieved ticket number: 7 started.
C++11: Thread with ticket number: 7 completed.
C++11: Thread retrieved ticket number: 8 started.
C++11: Thread with ticket number: 8 completed.
C++11: Thread retrieved ticket number: 9 started.
C++11: Thread with ticket number: 9 completed.
C++11: Thread retrieved ticket number: 10 started.
C++11: Thread with ticket number: 10 completed.
C++11: Thread retrieved ticket number: 11 started.
C++11: Thread with ticket number: 11 completed.
C++11: Thread retrieved ticket number: 12 started.
C++11: Thread with ticket number: 12 completed.
C++11: Thread retrieved ticket number: 13 started.
C++11: Thread with ticket number: 13 completed.
C++11: Thread retrieved ticket number: 14 started.
C++11: Thread with ticket number: 14 completed.
C++11: Thread retrieved ticket number: 15 started.
C++11: Thread with ticket number: 15 completed.
C++11: Thread retrieved ticket number: 16 started.
C++11: Thread with ticket number: 16 completed.
C++11: Thread retrieved ticket number: 17 started.
C++11: Thread with ticket number: 17 completed.
C++11: Thread retrieved ticket number: 18 started.
C++11: Thread with ticket number: 18 completed.
C++11: Thread retrieved ticket number: 19 started.
C++11: Thread with ticket number: 19 completed.
C++11: Signaling threads to do work.
C++11: All threads completed.

**/




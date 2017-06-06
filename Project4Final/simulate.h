//header file for simulate
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <queue>
#include <list>

#ifndef SIMULATE
#define SIMULATE

using namespace std;

class simulate {
public:
	//Constructor
	simulate();

	//Destrcutor
	~simulate();

	//actually does the bank transaction
	void action();

	//adds an arrival event
	void arrivalEvent(int time);

	//adds a departure event
	void departureEvent(int time);

	//prints out the end statistics
	void endResults();

	//prints out the events list
	void printEvents();

	//add person
	void addPerson(int arrival, int wait);

private:
	int numCustomers = 0;
	double averageTime = 0.0;
	double maxTime = 0.0;
	double averageWait = 0.0;
	double maxWait = 0.0;
	int maxInLine = 0;
	double totalWait = 0.0;
	double totalTime = 0.0;

	int clock = 0;
	bool tellerAvailable = true;
	bool bankerAvailable = true;

	struct Person
	{
		int arrivalTime = 0;
		int waitTime = 0;

		Person() : arrivalTime(0), waitTime(0) {};
	};

	struct Event
	{
		int arrival = 0;
		int departure = 0;
		int currentTime = 0;
	};

	queue<Person> tellerQueue; //queue for people with wait times less than or equal to 10 minutes
	queue<Person> bankerQueue; //queue for people with wait times over 10 minutes

	list<Event> events;
};

#endif

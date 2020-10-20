/*
File: Event.h
Name: Haoran Zhi
date: 3/16/2019
course: CIS 279
The Event.h file is an Abstract class that is used 
for other class to inherit from it.

Function:Event(unsigned int t ) initalizes the time variable 
Pre: the function requires a unsigned int variable as input 
Post:none

Function: processEvent is a virtual function 
Pre:none
Post:none

Function: CompareTo function is used for comparing two events by there time
Pre: a Event object is required as input
Post: the function returns true or false depending on which is smaller
*/

#ifndef EVENT_H
#define EVENT_H

#include <iostream>
using namespace std;

class Event{
public:
	unsigned int Time;
	Event(unsigned int t) : Time(t){ };
	virtual void processEvent() { };
	bool CompareTo(Event *event);
};




//This funtion will compare the object with another Event
//and return true if it is smaller
bool Event::CompareTo(Event *event){
return Time <= event->Time;
}
#endif //EVENT_H
/*
File: MinPQ.h
Name: Haoran Zhi
date: 3/16/2019
course: CIS 279
This header file is a Framework that supports all Event simulation using a Min PQ

Function:SimulationFramework function initailize the event queue and the currenttime variable
Pre:none
Post:none

Function:ScheduleEvent function will put a new event into the queue
Pre:the function requires a Event pointer as input
Post:none

Function:run function will run the simulation 
Pre:none
Post:none

Function:weightedProbability function will decide a persentage 
Pre:the function requires a verctor as input
Post: the function will returns a integer either 0, 1, 2 depending on what persentage 
*/
#ifndef SIMULATIONFRANEWORK_H
#define SIMULATIONFRANEWORK_H

#include <iostream>
#include "MinPQ.h"
#include <vector>
#include "Event.h"
using namespace std;

//the SimulationFramework class is used for building a simulation 
//with events
class SimulationFramework{
public:
	SimulationFramework(): eventQueue(), currentTime(0){}
	void ScheduleEvent(Event * newEvent);
	void run();
	int weightedProbability(const vector<unsigned int> &weight);
	unsigned int currentTime;//the time of the simulation
protected:
	MinPQ<Event> eventQueue;// a Min PQ contains the events

};






// the WeightedProbability function returns a number depending on a certain persentage
int SimulationFramework::weightedProbability(const vector<unsigned int> &weight){
	int maxNum =100;// the bound 
	int ranNum = rand()%maxNum +1;//a random number between 1~the bound
	// checks which area is the number in and decide a which number to output 0, 1,or 2
	if (ranNum < weight[1])
		return 0;
	else if(ranNum <=(weight[1]+weight[2]))
		return 1;
	else return 2;

}






// the shceduleEvent function inserts a new Event into the PQ
void SimulationFramework::ScheduleEvent(Event * newEvent){

		eventQueue.insert(newEvent);
	
}






// The run fumction start the simulation and process all the Events happend
//during the time interval
void SimulationFramework::run(){
	//keeps looping until the queue is empty
	while(!eventQueue.isEmpty()){
		Event* nextEvent = eventQueue.min();//get the next event 
		eventQueue.delMin();//remove iut from the queue
		currentTime = nextEvent->Time;//update the time
		nextEvent->processEvent();//start the process
		delete nextEvent;//delete the pointer
	}

}

#endif
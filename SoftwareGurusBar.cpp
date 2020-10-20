/*
Disvrete Event-Driven Simulation
Project 2
CIS 279
SoftwareGurusBar.cpp
Haoran Zhi
2019/03/16

Purpose: the purpose of this program is to use a Min heap implementation priority queue to 
simulates a bar's daily events.
*/
#include <iostream>
#include "Event.h"
#include <cstdlib>
#include "SimulationFramework.h"
using namespace std;

class randomInterger{
public:
	unsigned int operator()(unsigned int);
}randomizer;







unsigned int randomInterger::operator ()(unsigned int max){

	// rand return random integer
	// convert to unsigned to make positive
	// take remainder to put in range
	unsigned int rval = rand();
	return rval % max;
}







//this function returns a random value between two numbers
unsigned int randBetween(int low, int high){
	return low + randomizer(high - low);

}






/*
The class SoftwareGurusBar is the main objective of this project and 
it is simulating the daily events happens inside a bar
It has two members in it, the number of free chairs and the profits

Function:SoftwareGurusBar function is the constructor that initializes the avalible chairs and profit
Pre:none
Post:none

Function:canSeat function checkes if there are seats for incoming customers
Pre: the function requires a how many customer comes as input 
Post:the function returns true if there are chairs avalible

Function:order function update the profit by which type of beer is ordered
Pre:the type of beer is required as input
Post:none

Function:leave function increase the free chair when a group leaves
Pre:the integer number of people leaved is reuqired as input
Post:none
*/
class SoftwareGurusBar{
public:
	SoftwareGurusBar() :freeChairs(50), profits(0.0) {}
	bool canSeat(unsigned int numberOfPeople);
	void order(unsigned int beertype);
	void leave(unsigned int numberOfPeople);
	//the number of chairs avialible
	unsigned int freeChairs;
	//the profit earned
	double profits;
};

//Decalring globel variables
SimulationFramework theSimulation;
SoftwareGurusBar theBar;
vector<unsigned int> vect{ 15, 60, 25 };







//This function returns true if there are seats left for the incoming customers
bool SoftwareGurusBar::canSeat(unsigned int numberOfPeople){
	cout << "Time: "<<theSimulation.currentTime;
	cout << " Group of " << numberOfPeople << "customers arrives"<< endl;
	//let the group seat if there are  chairs avialible
	if (numberOfPeople <= freeChairs){
		cout << "Group is seated."<<endl;
		freeChairs -= numberOfPeople;
		return true;
	}else{
		cout << "No room, Group Leave" << endl;
		return false;
	}
}






//This function counts how many profits are earned by recieving
//what type of beer the customer orders
void SoftwareGurusBar::order(unsigned int beertype){
	cout << "Time:" << theSimulation.currentTime;
	cout << " serviced order for " << beertype << endl;
	//increase the profit by which type of beer they ordered
	switch(beertype){
		case 1:
			profits += 2;break;
		case 2:
			profits += 3;break;
		case 3:
			profits += 4;break;		
	}
	

}





//This function clears out the number of chairs by getting how many
//people are leaving.
void SoftwareGurusBar::leave(unsigned int numberOfPeople){
	cout << "Time:" << theSimulation.currentTime;
	cout << " Group of " << numberOfPeople << "people leaves" << endl;
	freeChairs += numberOfPeople;
}




/*
The class ArriveEvent inherits from the class Event

Function:ArriveEvent function is the comstructor of the class ArriveEvent
it initializes the groupsize and time
Pre:the function requires a integer time and a integer gs as input
Post:none

Function:processEvent function of arriveEvent seats the group and schedule an
orderEvent for them
Pre:none
Post:none
*/
class ArriveEvent : public Event{
public:
	//constructor
	ArriveEvent(unsigned int time, unsigned int gs) : Event(time), groupsize(gs){}
	
	virtual void processEvent();
protected:
	//how many people arrived
	unsigned int groupsize;
};






//the class OrderEvent inherits from the class Event
/*
Function:OrderEvent function is the comstructor of the class OrderEvent
it initializes the groupsize and time
Pre:the function requires a integer time and a integer gs as input
Post:none

Function:processEvent function orders for every people in the group
Pre:none
Post:none
*/
class OrderEvent : public Event{
public:
	//constructor
	OrderEvent(unsigned int time, unsigned int gs) : Event(time), groupsize(gs){}
	virtual void processEvent();
protected:
	unsigned int groupsize;	
};






//the class LeaveEvent inherits from the class Event
/*
Function:LeaveEvent function is the comstructor of the class LeaveEvent
it initializes the groupsize and time
Pre:the function requires a integer time and a integer gs as input
Post:none

Function:processEvent for LeaveEvent leaves the group of people
Pre:none
Post:none
*/
class LeaveEvent : public Event{
public:
	//constructor
	LeaveEvent(unsigned int time, unsigned int gs) : Event(time), groupsize(gs){}
	virtual void processEvent();
protected:
	unsigned int groupsize;	
};






//the class Re_OrderEvent inherits from the class Event
/*
Function:Re_OrderEvent function is the comstructor of the class Re_OrderEvent
it initializes the groupsize and time
Pre:the function requires a integer time and a integer gs as input
Post:none

Function:processEvent for Re_OrderEvent schedules either another reorder or leave event
Pre:none
Post:none
*/
class Re_OrderEvent : public Event{
public:
	//constructor
	Re_OrderEvent(unsigned int time, unsigned int gs, int chance) : Event(time), groupsize(gs), Chance(chance){}
	virtual void processEvent();
	int Chance;
protected:
	unsigned int groupsize;
};






//the processEvent of an ArriveEvent will seat the customers and schedule a orderEvent 
//for them
void ArriveEvent::processEvent(){
	if (theBar.canSeat(groupsize)){
		theSimulation.ScheduleEvent(new OrderEvent(theSimulation.currentTime + randBetween(2, 10), groupsize));
	}
}






//The OrderEvent::processEvent function will let the customers
//order by an seted possibility then schedule either a re-order or leave event
void OrderEvent::processEvent(){
	//loop through all the people in this group
	for (int i = 0; i < groupsize; i++){
		//increment the profit 
		switch(theSimulation.weightedProbability(vect)){
			case 0:
				theBar.order(1);break;
			case 1:
				theBar.order(2);break;
			case 2:
				theBar.order(3);break;	
		}
	}
	//the time this group leaves
	int leaveTime = theSimulation.currentTime + randBetween(15,35);
	//the chance they will order again
	int chance = 50;
	//a random number between 1~100
	int x = rand()%100 + 1;
	//schedule a reorder by 50% chance, else Leave the group
	if(x < chance){
		theSimulation.ScheduleEvent(new Re_OrderEvent(theSimulation.currentTime + randBetween(10, 15), groupsize, chance));
	}
	else{
		theSimulation.ScheduleEvent(new LeaveEvent(leaveTime, groupsize));
	}

}






// the LeaveEvent:: processEvent leaves the group of people
void LeaveEvent::processEvent(){
	theBar.leave(groupsize);
}






//The Re_OrderEvent::processEvent function will let the customers
//order by an seted possibility then schedule either a re-order or leave event
void Re_OrderEvent::processEvent(){
	//loop through all the people in this group
	for (int j = 0; j < groupsize; j++){
		//increment the profit 
		switch(theSimulation.weightedProbability(vect)){
			case 0:
				theBar.order(1);break;
			case 1:
				theBar.order(2);break;
			case 2:
				theBar.order(3);break;	
		}
	}
	//make the chance lower for them to order again
	int c = Chance/2;
	//set a leave time for the group
	int t = theSimulation.currentTime + randBetween(15, 35);
	//a random number between 1~100
	int x = rand()%100 + 1;
	//schedule a reorder by chance, else Leave the group
	if(x < Chance){
		theSimulation.ScheduleEvent(new Re_OrderEvent(theSimulation.currentTime + randBetween(10, 15), groupsize, Chance));
	}
	else{
		theSimulation.ScheduleEvent(new LeaveEvent(t, groupsize));
	
	}


}





//The main function puts arriveevents into the queue and runs it 
//with in a time interval
int main() {
    cout<<"SoftwareGurus Bar Simulation\n";
// load priority queue with initial Arrive Events then run simulation
    unsigned int t = 0;
// load 4 hours (240 minutes) of Arrive Events
    while (t < 240) {
// new group every 2-5 minutes
    t += randBetween(2,5);
// group size ranges from 1 to 5
    theSimulation.ScheduleEvent(new ArriveEvent(t, randBetween(1,5)));
    }
// then run simulation and print profits
    theSimulation.run();
// print out the total profit earned
    cout << "Total profits: " << theBar.profits << endl;

    return 0;
}
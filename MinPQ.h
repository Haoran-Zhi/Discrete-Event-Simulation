/*
File: MinPQ.h
Name: Haoran Zhi
date: 3/16/2019
course: CIS 279
the MinPQ.h is implementing a Min Heap Priority-Queue
that is used for a temp class T

Function:MinPQ function initailizes the size of the queue
Pre:none
Post:none

Function:insert function inserts the input into the queue
Pre: the function requires a object of class T as input
Post: none

Function:delMin function deletes the top term from the Min heap
Pre:none
Post:none

Function:isEmpty function test if the queue is empty or not
Pre:none
Post:the function returns true if the queue is empty

Function:min function returns the top term of the Min heap
Pre:none
Post: the component is PQueue[1]

Function:swim function move the obejct from one place in 
the queue to its proper position for a min heap
Pre: the function requires a interger as input
Post:none

Function:sink function will sink the element from one place in the queue to 
its poper position with a bound
Pre: the function requires two integer as inputs
Post:none

Function: less function compare two elements in the queue
Pre: the function requires two integer as inputs
Post:true or false depending on which element is begger

Function: exch function switches the element 
Pre:two integers are required as inputs
Post:none
*/
#ifndef MinPQ_H
#define MinPQ_H

#include <iostream>
using namespace std;

template <class T>
class MinPQ{
	public:
		MinPQ();//constructor
		void insert(T * key);
		void delMin();
		bool isEmpty(){return queuesize == 1;}//test if the queue is empty or not
		T* min(){return PQueue[1];}//return the minimum component
		

	private:
		int queuesize;//the size of the queue
		T* PQueue[360];//an pointer array used for inserting
		//the swim function swim an object to its proper position
		void swim(int k){
			while(k >1 && less(k, k/2)){
				exch(k, k/2);//parent of
				k = k/2;// node k is at k/2
			}
		}
		//the sink function sink a component to it's proper position
		void sink(int a, int b){
			//keep looing if a has a children
			while (2*a < b){
				int j = 2*a;
				if(j < b && less(j+1, j)) j++;//select the lowest child
				if(less(a,j)) break;// if the child is bigger than a stop the loop
				exch(a, j);//exchange a with its child
				a = j;// set a to its child's position
			}
		}
		//the less dunction test if the frist component is less than the second
		bool less(int i, int j){
			return PQueue[i]->CompareTo(PQueue[j]);
		}
		//the exch function change the key in the two position
		void exch(int x, int y){
			T* t = PQueue[x];
			PQueue[x] = PQueue[y];
			PQueue[y] = t;

		}

};

//the constructor set the queuesize to 0
template <class T>
MinPQ<T>::MinPQ(){
	queuesize = 0;//set to 0 because priority-queue starts at 1
}



//the insert function takes an T type variable as parameter
//and insert it into the PQ
template <class T>
void MinPQ<T>::insert(T * key){
	PQueue[++queuesize] = key;//inserting the key
	swim(queuesize);// keep the min heap construction

}




//the delMin function delete the first component in the PQ
template <class T>
void MinPQ<T>::delMin(){
	//loop if there are more than one component in the queue
	if(queuesize > 1){
	exch(1, queuesize);//switch the first with the last
	sink(1, queuesize -1);//keep the min heap construction
	--queuesize;//decrement the size
    }
} 



#endif  // MinPQ_H
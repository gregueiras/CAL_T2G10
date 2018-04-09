/*
 * Passenger.cpp
 *
 *  Created on: Mar 22, 2018
 *      Author: gregu
 */

#include "Passenger.h"

template<class T>
Passenger<T>::Passenger() : Person() {
	this->timeLimit = 0;
	this->destination = NULL;
	this->numPassengers = 0;
	this->source = NULL;
	this->pos = NULL;
	this->dropped = false;
	this->picked = false;
	this->prevPos = NULL;
	this->infoSource = -1;
	this->infoDestination = -1;
}

template<class T>
Passenger<T>::Passenger(int numP) : Person() {
	this->timeLimit = INT_MAX;
	this->numPassengers = numP;
	this->destination = NULL;
	this->source = NULL;
	this->pos = NULL;
	this->dropped = false;
	this->picked = false;
	this->prevPos = NULL;
	this->infoSource = -1;
	this->infoDestination = -1;
}

template<class T>
Passenger<T>::Passenger(int numP, Vertex<T>* source, Vertex<T>* destination) : Person() {
	this->timeLimit = INT_MAX;
	this->numPassengers = numP;
	this->source = source;
	this->destination = destination;
	this->pos = NULL;
	this->dropped = false;
	this->picked = false;
	this->prevPos = NULL;
	this->infoSource = source->getInfo();
	this->infoDestination = destination->getInfo();
}

template<class T>
Passenger<T>::Passenger(int numP, int tl, Vertex<T>* source, Vertex<T>* destination) : Person() {
	this->timeLimit = tl;
	this->numPassengers = numP;
	this->source = source;
	this->destination = destination;
	this->pos = NULL;
	this->dropped = false;
	this->picked = false;
	this->prevPos = NULL;
	this->infoSource = source->getInfo();
	this->infoDestination = destination->getInfo();
}

template<class T>
void Passenger<T>::addPassengers(int num) {
	this->numPassengers += num;
}

template<class T>
int Passenger<T>::getNum() {
	return this->numPassengers;;
}

template<class T>
bool Passenger<T>::writeToFile(ofstream *output) {
	if (output->is_open()) {
		*output << this->getName() << endl;
		*output << this->getAge() << " " << this->getNum() << " " << this->getTimeLimit() << " ";
		*output << this->getCurrentTime().getHour() << " " << this->getCurrentTime().getMinute() << endl;
		*output << this->getSource()->getInfo() << " " << this->getDestination()->getInfo() << endl;
	} else {
		return false;
	}
	return true;
}

template<class T>
Vertex<T>* Passenger<T>::getPos() {
	return pos;
}

template<class T>
void Passenger<T>::setPos(Vertex<T>* pos) {
	this->pos = pos;
}

template<class T>
Passenger<T>::~Passenger() {
	// TODO Auto-generated destructor stub
}

template<class T>
Passenger<T>::Passenger(string name, int age, int numP) : Person(name, age) {
	this->numPassengers = numP;
	this->source = nullptr;
	this->pos = NULL;
	this->destination = nullptr;
	this->picked = false;
	this->dropped = false;
	this->timeLimit = 0;
	this->prevPos = nullptr;
	this->infoSource = -1;
	this->infoDestination = -1;
}

template<class T>
Passenger<T>::Passenger(string name, int age, int numP, int tl) : Person(name, age,tl,Time(0,0)) {
	this->numPassengers = numP;
	this->source = nullptr;
	this->pos = NULL;
	this->destination = nullptr;
	this->picked = false;
	this->dropped = false;
	this->timeLimit = 0;
	this->prevPos = nullptr;
	this->infoSource = -1;
	this->infoDestination = -1;
}

template<class T>
Passenger<T>::Passenger(string name, int age, int numP, int tl, Time startTime, T source, T destination) : Person(name, age, tl, startTime) {
	this->numPassengers = numP;
	this->pos = NULL;
	this->picked = false;
	this->dropped = false;
	this->infoSource = source;
	this->infoDestination = destination;
	this->timeLimit = tl;
	this->prevPos = nullptr;
	this->destination = nullptr;
	this->source = nullptr;
}

template<class T>
Passenger<T>::Passenger(string name, int age, int numP, int tl, Time startTime) : Person(name, age,tl, startTime) {
	this->numPassengers = numP;
	this->source = nullptr;
	this->pos = NULL;
	this->destination = nullptr;
	this->picked = false;
	this->dropped = false;
	this->timeLimit = 0;
	this->prevPos = nullptr;
	this->infoSource = -1;
	this->infoDestination = -1;
}

template<class T>
Vertex<T>* Passenger<T>::getSource() {
	return this->source;
}

template<class T>
void Passenger<T>::setSource(Vertex<T>* pos) {
	this->source = pos;
}

template<class T>
Vertex<T>* Passenger<T>::getDestination() {
	return this->destination;
}

template<class T>
void Passenger<T>::setDestination(Vertex<T>* pos) {
	this->destination = pos;
}

template<class T>
Vertex<T>* Passenger<T>::getPrevPos() {
	return prevPos;
}

template<class T>
void Passenger<T>::setPrevPos(Vertex<T>* pos) {
	this->prevPos = pos;
}

template<class T>
Passenger<T>* Passenger<T>::clone() const
{
  return(new Passenger<T>(*this));
};

template class Passenger<int> ;

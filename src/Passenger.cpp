/*
 * Passenger.cpp
 *
 *  Created on: Mar 22, 2018
 *      Author: gregu
 */

#include "Passenger.h"

template<class T>
Passenger<T>::Passenger() :
		Person() {
	// TODO Auto-generated constructor stub
	this->destination = NULL;
	this->numPassengers = 0;
	this->source = NULL;
}

template<class T>
Passenger<T>::Passenger(int numP) :
		Person() {
	this->numPassengers = numP;
	this->destination = NULL;
	this->source = NULL;
}

template<class T>
Passenger<T>::Passenger(int numP, Vertex<T>* source, Vertex<T>* destination) :
		Person() {
	this->numPassengers = numP;
	this->source = source;
	this->destination = destination;
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
Passenger<T>::~Passenger() {
	// TODO Auto-generated destructor stub
}

template class Passenger<int>;




template<class T>
Passenger<T>::Passenger(string name, int age, int numP) :
		Person(name, age) {
	this->numPassengers = numP;
	this->source = source;
	this->destination = destination;
}

/*
 * Passenger.cpp
 *
 *  Created on: Mar 22, 2018
 *      Author: gregu
 */

#include "Passenger.h"

template <class T>
Passenger<T>::Passenger() {
	// TODO Auto-generated constructor stub

}

template<class T>
Passenger<T>::Passenger(int numP, Vertex<T>* source, Vertex<T>* destination)
{
	this->numPassengers = numP;
	this->source = source;
	this->destination = destination;
}

template<class T>
void Passenger<T>::addPassengers(int num) {
	this->numPassengers += num;
}

template <class T>
Passenger<T>::~Passenger() {
	// TODO Auto-generated destructor stub
}


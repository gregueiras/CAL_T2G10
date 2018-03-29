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
	this->pos = NULL;
}

template<class T>
Passenger<T>::Passenger(int numP) :
		Person() {
	this->numPassengers = numP;
	this->destination = NULL;
	this->source = NULL;
	this->pos = NULL;
}

template<class T>
Passenger<T>::Passenger(int numP, Vertex<T>* source, Vertex<T>* destination) :
		Person() {
	this->numPassengers = numP;
	this->source = source;
	this->destination = destination;
	this->pos = NULL;
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
Passenger<T>::Passenger(string name, int age, int numP) :
		Person(name, age) {
	this->numPassengers = numP;
	this->source = source;
	this->pos = NULL;
	this->destination = destination;
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

template class Passenger<int> ;

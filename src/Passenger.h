/*
 * Passenger.h
 *
 *  Created on: Mar 22, 2018
 *      Author: gregu
 */

#pragma once

#include "Person.h"
#include "Graph.h"

template<class T> class Vertex;

template<class T>
class Passenger: public Person {
	int numPassengers;
	vector<Vertex<T>*> path;
	Vertex<T>* source;
	Vertex<T>* destination;
public:
	Passenger();
	Passenger(int numP, Vertex<T>* source, Vertex<T>* destination);
	Passenger(int numP);
	Passenger(string name, int age, int numP);
	void addPassengers(int num);
	int getNum();

	virtual ~Passenger();
};



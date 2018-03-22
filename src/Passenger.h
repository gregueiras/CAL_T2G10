/*
 * Passenger.h
 *
 *  Created on: Mar 22, 2018
 *      Author: gregu
 */

#ifndef SRC_PASSENGER_H_
#define SRC_PASSENGER_H_

#include "Person.h"
#include "Graph.h"

template <class T>
class Passenger: public Person {
	int numPassengers;
	vector<Vertex<T*>> path;
	Vertex<T>* source;
	Vertex<T>* destination;
public:
	Passenger();
	Passenger(int numP, Vertex<T>* source, Vertex<T>* destination);
	void addPassengers(int num);
	virtual ~Passenger();
};

#endif /* SRC_PASSENGER_H_ */

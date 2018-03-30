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
	int timeLimit; //only being considered if route is deviated from the best found thru Dijsktra
	vector<Vertex<T>*> path;
	Vertex<T>* source;
	Vertex<T>* pos;
	Vertex<T>* destination;
public:
	Passenger();
	Passenger(int numP, Vertex<T>* source, Vertex<T>* destination);
	Passenger(int numP);
	Passenger(string name, int age, int numP);
	Passenger(string name, int age, int numP, int tl);
	Passenger(int numP, int tl, Vertex<T>* source, Vertex<T>* destination);
	void addPassengers(int num);
	int getNum();

	virtual ~Passenger();
	Vertex<T>* getPos();
	void setPos(Vertex<T>* pos);

	Vertex<T>* getSource();
	void setSource(Vertex<T>* pos);

	Vertex<T>* getDestination();
	void setDestination(Vertex<T>* pos);

	int getTimeLimit() const;
	void setTimeLimit(int timeLimit);
};

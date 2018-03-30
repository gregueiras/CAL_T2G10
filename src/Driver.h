/*
 * Driver.h
 *
 *  Created on: Mar 22, 2018
 *      Author: gregu
 */

#pragma once

#include <list>
#include <vector>
#include <map>
#include "Person.h"

#include "Passenger.h"
#include "Graph.h"
template<class T> class Passenger;
template<class T> class Vertex;

template<class T> struct ptr_less {
	bool operator()(Vertex<T>* lhs, Vertex<T>* rhs) const {
		return *lhs < *rhs;
	}
};

template<class T>
class Driver: public Person {
	int capacity; //passenger Capacity
	std::vector<Passenger<T>*> passengers;
	std::vector<int> capacityAtPath;
	std::multimap<Vertex<T>*, std::vector<Passenger<T>*>, ptr_less<T>> passengersPickedAt;
	std::map<Vertex<T>*, std::vector<Passenger<T>*>, ptr_less<T>> passengersDroppedAt;

	void clearPassengersPickedAt();
	void clearPassengersDroppedAt();
	void clearCapacityAtPath();
public:
	Driver();
	Driver(int timeLimit, int cap);
	Driver(string name, int age, int timeLimit, int cap);
	virtual ~Driver();

	void addPassenger(Passenger<T>* passenger);
	void updateFreeSpace();

	void addPassengersPickedAt(Vertex<T>* v,
			std::vector<Passenger<T>*> passengers);
	void addPassengersDroppedAt(Vertex<T>* v,
			std::vector<Passenger<T>*> passengers);

	int getCapacity();
	std::vector<int> getCapacityAtPath();

	void printPassengersPickedAt();
	void printPassengersDroppedAt();
	void printCapacityAtPath();

	void resetTravel();

};


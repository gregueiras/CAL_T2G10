#pragma once

#include "Passenger.h"
#include "Driver.h"

#include <unordered_set>

template <class T>
class RideShare
{
public:
	RideShare();
	RideShare(unordered_set<Passenger<T>*> passengers, unordered_set<Driver<T>*> drivers, Graph<T> graph);
	~RideShare(); 
	
	void addPassenger(Passenger<T>* passenger);
	void addDriver(Driver<T>* driver);
	void setGraph(Graph<T> graph);

	void DijkstraPeopleMultipleDrivers();

	bool addEdge(const T &sourc, const T &dest, double w);
	bool addVertex(const T &in, unsigned long x, unsigned long y);

private:
	unordered_set<Passenger<T>*> passengers;
	unordered_set<Driver<T>*> drivers;
	Graph<T> graph;

	unordered_set<Passenger<T>*> copyPassengers();
	Graph<T> copyGraph();
	void resetPassengers();

};

template<class T> struct p_less {
	bool operator()(int lhs, int rhs) const {
		return lhs > rhs;
	}
};

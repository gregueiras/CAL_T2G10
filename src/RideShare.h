#pragma once

#include "Passenger.h"
#include "Driver.h"
#include "graphviewer.h"

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
	void setPassengers(unordered_set<Passenger<T>> passengers);
	void setDrivers(unordered_set<Driver<T>> drivers);

	void DijkstraPeopleMultipleDrivers();

	bool addEdge(const T &sourc, const T &dest, double w);
	bool addVertex(const T &in, unsigned long x, unsigned long y);
	void checkSelectedMapConnectivity();
	void graphInit();

	bool PrintPassengerInfo(string name, int age);
	bool PrintDriverInfo(string name, int age);
	void PrintAllDriversInfo();

	void SetDriverPathColour(string name, int age);
	void SetPassengerPathColour(string name,int age);



private:
	unordered_set<Passenger<T>*> passengers;
	unordered_set<Driver<T>*> drivers;
	Graph<T> graph;

	
	void resetPassengers();
	void deletePassengers();
	void deleteDrivers();
	void deleteVertices();

};

template<class T> struct p_less {
	bool operator()(int lhs, int rhs) const {
		return lhs > rhs;
	}
};

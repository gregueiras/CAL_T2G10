#pragma once

#include <list>
#include <vector>
#include <map>
#include <fstream>
#include "Person.h"

#include "Passenger.h"
#include "Graph.h"
#include "matcher.h"

template<class T> class Passenger;
template<class T> class Vertex;

template<class T> struct ptr_less {
	bool operator()(Vertex<T>* lhs, Vertex<T>* rhs) const {
		return *lhs < *rhs;
	}
};

template<class T>
class Driver: public Person {
	int capacity; //car passengers capacity
	std::vector<Passenger<T>*> passengers;
	std::vector<int> capacityAtPath;
	std::multimap<Vertex<T>*, std::vector<Passenger<T>*>, ptr_less<T>> passengersPickedAt;
	std::map<Vertex<T>*, std::vector<Passenger<T>*>, ptr_less<T>> passengersDroppedAt;
	std::list<Vertex<T>*> path;
	std::list<string> streets;

	void clearPassengersPickedAt();
	void clearPassengersDroppedAt();
	void clearCapacityAtPath();

	int transportedPassengers;

	T source;
	T destination;
public:
	Driver();
	Driver(int cap, int lim);
	Driver(int cap, int lim, string name, int age, Time startTime);
	Driver(T src, T dest,int cap, int lim,string name, int age, Time startTime);
	virtual ~Driver();

	void setPath(std::list<Vertex<T>*> newPath);

	void addPassenger(Passenger<T>* passenger);
	void updateFreeSpace();
	void updateFreeSpace(Passenger<T> *p, list<Vertex<T>*> path);

	void addPassengersPickedAt(Vertex<T>* v,
			std::vector<Passenger<T>*> passengers);
	void addNewPassengersPickedAt(Vertex<T>* v,
			std::vector<Passenger<T>*> passengers);
	void addPassengersDroppedAt(Vertex<T>* v,
			std::vector<Passenger<T>*> passengers);
	void addNewPassengersDroppedAt(Vertex<T>* v,
			vector<Passenger<T>*> passengers);

	int getCapacity();

	std::vector<int> getCapacityAtPath();
	int getCapacityAtVertexOnPath(int index);

	std::multimap<Vertex<T>*, std::vector<Passenger<T>*>, ptr_less<T>> getPassengersPickedAt();

	void printPassengersPickedAt();
	void printPassengersDroppedAt();
	void printCapacityAtPath();
	void printPath();

	void resetTravel();
	void resetValues();

	int getTransportedPassengers() const;
	void increaseTransportedPassengers(int number);
	void increaseTransportedPassengers();
	void setTransportedPassengers(int tp);
	int getSource()const;
	int getDestination()const;
	bool writeToFile(ofstream *output);

	virtual Driver<T>* clone() const;

	void setPassengersDrivedBy();
	std::list<Vertex<T>*> getPath() const;

	void setStreets(std::list<string> streets) {
		this->streets = streets;
	}

	std::list<string> getStreets() {
		return this->streets;
	}

	int driverPassengerKmpMatcher(string pattern, vector<string> &names);

	void driverPassengerEditDistance(string pattern, map<string, int> &patternAndDistance, int maximumEditDistance);

	int driverStreetKmpMatcher(string pattern, vector<string> &names);

	void driverStreetEditDistance(string pattern, map<string, int> &patternAndDistance, int maximumEditDistance);
};

namespace std
{
	template<class T>
	struct hash<Driver<T>>
	{
		size_t
			operator()(const Driver<T> & obj) const
		{
			return hash<std::string>()(obj.getName());
		}
	};
}


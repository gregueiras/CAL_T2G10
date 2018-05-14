#pragma once

#include "Passenger.h"
#include "Driver.h"
#include "graphviewer.h"

#include <unordered_set>

template <class T>
class RideShare
{
	string name;
	unordered_set<Passenger<T>*> passengers;
	unordered_set<Driver<T>*> drivers;
	Graph<T> graph;

	void resetPassengers();

	bool readPassengersFromFile();
	bool readDriversFromFile();

	bool writePassengersToFile();
	bool writeDriversToFile();

	void deletePassengers();
	void deleteDrivers();
public:
	RideShare();
	RideShare(string n);
	RideShare(string n, unordered_set<Passenger<T>*> passengers, unordered_set<Driver<T>*> drivers, Graph<T> graph);
	~RideShare(); 

	void addPassenger(Passenger<T>* passenger);
	void addPassenger(T source, T destination, Passenger<T>* passenger);
	void addDriver(Driver<T>* driver);

	void DijkstraPeopleMultipleDrivers();

	bool addEdge(const T &sourc, const T &dest, double w, string name);
	bool addVertex(const T &in, unsigned long x, unsigned long y);
	void checkSelectedMapConnectivity();
	void graphInit();

	bool PrintPassengerInfo(string name, int age);
	bool PrintDriverInfo(string name, int age);
	void PrintAllDriversInfo();

	bool SetDriverPathColour(string name, int age);
	bool SetPassengerPathColour(string name,int age);

	bool writeToFile();
	bool readFromFile();

	void setPassengers(unordered_set<Passenger<T>> passengers);
	void setDrivers(unordered_set<Driver<T>> drivers);
	void setGraph(Graph<T> graph);
	void setName(std::string name);

	void setFromFile(std::string name);

	int driverPassengerkmpMatcher(string name, int age, string pattern);
	void driverPassengerEditDistance(string name, int age,string pattern,map<string,int> &patternAndDistance);
	void getAndPrintDriverPassengerEditDistance(string name, int age, string pattern, int maximumEditDistance);

	int streetkmpMatcher(string name, int age, string pattern);

	void streetEditDistance(string name, int age, string pattern, map<string, int>& patternAndDistance);

	void getAndPrintDriverStreetEditDistance(string name, int age, string pattern, int maximumEditDistance);

};

template<class T> struct p_less {
	bool operator()(int lhs, int rhs) const {
		return lhs > rhs;
	}
};

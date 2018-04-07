#include "RideShare.h"

using namespace std;
template <class T>
RideShare<T>::RideShare()
{
}

template<class T>
RideShare<T>::RideShare(unordered_set<Passenger<T>*> passengers, unordered_set<Driver<T>*> drivers, Graph<T> graph)
{
	this->passengers = passengers;
	this->drivers = drivers;
	this->graph = graph;
}

template <class T>
RideShare<T>::~RideShare()
{
}

template<class T>
void RideShare<T>::addPassenger(Passenger<T>* passenger)
{
	this->passengers.insert(passenger);
}

template<class T>
void RideShare<T>::addDriver(Driver<T>* driver)
{
	this->drivers.insert(driver);
}

template<class T>
void RideShare<T>::setGraph(Graph<T> graph)
{
	this->graph = graph;
}

template<class T>
Graph<T> RideShare<T>::copyGraph()
{
	return this->graph;
}

template<class T>
void RideShare<T>::resetPassengers()
{
	for (auto i = this->passengers.begin(); i != this->passengers.end(); ++i) {
		(*i)->setPicked(false);
		(*i)->setDropped(false);
		(*i)->setPos((*i)->getSource());
		(*i)->setCurrentTime((*i)->getStartTime());
	}
}

template<class T>
unordered_set<Passenger<T>*> RideShare<T>::copyPassengers()
{
	return this->passengers;
}

template<class T>
void RideShare<T>::DijkstraPeopleMultipleDrivers()
{
	this->graph.addPeople(passengers);

	if (drivers.size() == 1)
	{
		this->graph.calculateAndPrintPath((*drivers.begin())->getSource(), (*drivers.begin())->getDestination(), (*drivers.begin()), false);
		cout << endl;
		return;
	}

	multimap<T, Driver<T>*, p_less<T>> ordered_drivers;
	for (auto i = drivers.begin(); i != drivers.end(); i++)
	{
		cout << "1. " << (*i)->getName() << endl;
		if (this->graph.calculatePath((*i)->getSource(), (*i)->getDestination(), (*i)))
			ordered_drivers.insert(pair<int, Driver<int>*>((*i)->getTransportedPassengers(), (*i)));
		cout << endl << endl;

		this->resetPassengers();

	}
	for (auto i = ordered_drivers.begin(); i != ordered_drivers.end(); i++)
	{

		cout << "2." << i->second->getName() << endl;
		i->second->resetValues();
		this->graph.calculateAndPrintPath(i->second->getSource(), i->second->getDestination(), i->second, true);
		cout << endl;
	}
}

template<class T>
bool RideShare<T>::addEdge(const T &sourc, const T &dest, double w)
{
	return this->graph.addEdge(sourc,dest,w);
}

template<class T>
bool RideShare<T>::addVertex(const T &in, unsigned long x, unsigned long y)
{
	return this->graph.addVertex(in,x,y);
}



template class RideShare<int>;

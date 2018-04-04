/*
 * Driver.cpp
 *
 *  Created on: Mar 22, 2018
 *      Author: gregu
 */

#include "Driver.h"
#include <iostream>
template<class T>
Driver<T>::Driver() {
	this->capacity = 0;
}

template<class T>
Driver<T>::~Driver() {
	// TODO Auto-generated destructor stub
}

template<class T>
void Driver<T>::setPath(std::list<Vertex<T>*> newPath) {
	this->path = newPath;
}

template<class T>
void Driver<T>::addPassenger(Passenger<T>* passenger) {
	this->passengers.push_back(passenger);
}

template<class T>
void Driver<T>::addPassengersPickedAt(Vertex<T>* v,
		vector<Passenger<T>*> passengers) {
	//	auto ret = this->passengersPickedAt[v] = passengers;

	if (this->passengersPickedAt.count(v) != 0)
	{
		auto res = this->passengersPickedAt.find(v);
		auto temp = res->second;
		this->passengersPickedAt.erase(v);
		temp.insert(temp.end(), passengers.begin(), passengers.end());
		this->passengersPickedAt.insert(std::pair<Vertex<T>*, vector<Passenger<T>*> >(v, temp));
	} else
	this->passengersPickedAt.insert(
			std::pair<Vertex<T>*, vector<Passenger<T>*> >(v, passengers));
}

template<class T>
void Driver<T>::addNewPassengersPickedAt(Vertex<T>* v,
		vector<Passenger<T>*> passengers) {
	//	auto ret = this->passengersPickedAt[v] = passengers;
	auto it = this->passengersPickedAt.find(v);
	if (it != this->passengersPickedAt.end()) {
		passengers.insert(passengers.begin(), it->second.begin(),
				it->second.end());
		this->passengersPickedAt.erase(it);
	}
	this->passengersPickedAt.insert(
			std::pair<Vertex<T>*, vector<Passenger<T>*> >(v, passengers));
}

template<class T>
void Driver<T>::addPassengersDroppedAt(Vertex<T>* v,
		vector<Passenger<T>*> passengers) {
	auto ret = this->passengersDroppedAt[v] = passengers;
}

template<class T>
void Driver<T>::addNewPassengersDroppedAt(Vertex<T>* v,
		vector<Passenger<T>*> passengers) {
	auto it = this->passengersDroppedAt.find(v);
	if (it != this->passengersDroppedAt.end()) {
		passengers.insert(passengers.begin(), it->second.begin(),
				it->second.end());
		this->passengersDroppedAt.erase(it);
	}
	this->passengersDroppedAt.insert(
			std::pair<Vertex<T>*, vector<Passenger<T>*> >(v, passengers));
}

template<class T>
Driver<T>::Driver(int cap, int lim) : Person("",0,lim, Time(0,0)){
	this->capacity = cap;
	this->transportedPassengers = 0;
}

template<class T>
Driver<T>::Driver(int cap, int lim, string name, int age, Time startTime) :
		Person(name, age,lim, startTime) {
	this->capacity = cap;
	this->transportedPassengers = 0;
}


template<class T>
Driver<T>::Driver(T src, T dest, int cap, int lim, string name, int age, Time startTime) :
	Person(name, age, lim, startTime) {
	this->capacity = cap;
	this->source = src;
	this->destination = dest;
	this->transportedPassengers = 0;
}

template<class T>
void Driver<T>::updateFreeSpace() {
	unsigned int count = 0;
	set<Passenger<T>*> passengersDropped;

	for (auto i = this->passengersDroppedAt.cbegin();
			i != this->passengersDroppedAt.cend(); ++i) {
		for (auto j = i->second.begin(); j != i->second.end(); ++j) {
			(*j)->setPicked(false);
			(*j)->setDropped(false);
				
			passengersDropped.insert((*j));
		}
	}

	for (auto i = this->passengersPickedAt.begin();
			i != this->passengersPickedAt.end();) {
		
		for (auto j = i->second.begin(); j != i->second.end();) {
			if (!passengersDropped.count((*j))) {
				(*j)->setPos((*j)->getPrevPos());
				(*j)->setPicked(false);
				(*j)->setDropped(false);
				j = i->second.erase(j);
			}
			else
				++j;
		}


		if (i->second.empty())
			i = this->passengersPickedAt.erase(i);
		else
			++i;
		

	}

	this->capacityAtPath.push_back(this->capacity);
	for (auto i = this->path.cbegin(); i != this->path.cend(); ++i) {

		int numPicked = 0;
		int numDropped = 0;

		auto p = this->passengersPickedAt.find((*i));
		if (p != this->passengersPickedAt.end()) {
			std::vector<Passenger<T>*> picked = p->second;
			for (Passenger<T>* var : picked) {
				numPicked += var->getNum();
			}
		}

		auto d = this->passengersDroppedAt.find((*i));
		if (d != this->passengersDroppedAt.end()) {
			std::vector<Passenger<T>*> dropped = d->second;
			for (Passenger<T>* var : dropped) {
				numDropped += var->getNum();
			}
		}

		this->capacityAtPath[count] += numDropped - numPicked;
		if (count + 1 != this->path.size())
			this->capacityAtPath.push_back(this->capacityAtPath[count]);
		++count;

	}

}

template<class T>
void Driver<T>::updateFreeSpace(Passenger<T> *p, list<Vertex<T>*> path) {
	T source = p->getSource()->getInfo();
	T destination = p->getDestination()->getInfo();
	int p_size = p->getNum();

	bool pathStartFound = false;
	int index = 0;
	auto i = path.begin();

	for (; i != path.end(); i++, index++) {
		if ((*i)->getInfo() == destination) {
			break;
		}

		if ((*i)->getInfo() == source) {
			pathStartFound = true;
		}

		if (pathStartFound) {
			this->capacityAtPath.at(index) -= p_size;
		}

	}
}

template<class T>
int Driver<T>::getCapacity() {
	return this->capacity;
}

template<class T>
int Driver<T>::getTransportedPassengers() const
{
	return transportedPassengers;
}
template<class T>
void Driver<T>::increaseTransportedPassengers(int number)
{
	transportedPassengers += number;
}

template<class T>
void Driver<T>::increaseTransportedPassengers()
{
	transportedPassengers +=1;
}
template<class T>
void Driver<T>::setTransportedPassengers(int tp)
{
	transportedPassengers = tp;
}

template<class T>
int Driver<T>::getSource()const
{
	return source;
}
template<class T>
int Driver<T>::getDestination()const
{
	return destination;
}






template<class T>
std::vector<int> Driver<T>::getCapacityAtPath() {
	return this->capacityAtPath;
}

template<class T>
int Driver<T>::getCapacityAtVertexOnPath(int index) {
	return this->capacityAtPath.at(index);
}

template<class T>
std::multimap<Vertex<T>*, std::vector<Passenger<T>*>, ptr_less<T>> Driver<T>::getPassengersPickedAt()
{
	return this->passengersPickedAt;
}

template<class T>
void Driver<T>::printPassengersPickedAt() {
	for (auto i = this->passengersPickedAt.cbegin();
			i != this->passengersPickedAt.cend(); ++i) {
		cout << i->first->getInfo() << " ";
		for (auto j : i->second)
			cout << (*j) << " ";
		cout << endl;
	}
}

template<class T>
void Driver<T>::clearPassengersPickedAt() {
	this->passengersPickedAt.clear();
}

template<class T>
void Driver<T>::printPassengersDroppedAt() {
	for (auto i = this->passengersDroppedAt.cbegin();
			i != this->passengersDroppedAt.cend(); ++i) {
		cout << i->first->getInfo() << " ";
		for (auto j : i->second)
			cout << (*j) << " ";
		cout << endl;
	}
}

template<class T>
void Driver<T>::printCapacityAtPath() {
	for (auto i = this->capacityAtPath.begin(); i != capacityAtPath.end();
			i++) {
		cout << (*i) << " ";
	}
	cout << endl;
}

template<class T>
void Driver<T>::resetTravel() {
	this->clearPassengersDroppedAt();
	this->clearPassengersPickedAt();
	this->clearCapacityAtPath();
}

template<class T>
void Driver<T>::resetValues()
{
	this->resetTravel();
	this->transportedPassengers = 0;
}

template<class T>
void Driver<T>::clearPassengersDroppedAt() {
	this->passengersDroppedAt.clear();
}

template<class T>
void Driver<T>::clearCapacityAtPath() {
	this->capacityAtPath.clear();
}

template class Driver<int> ;

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
	// TODO Auto-generated constructor stub

}

template<class T>
Driver<T>::~Driver() {
	// TODO Auto-generated destructor stub
}

template<class T>
void Driver<T>::addPassenger(Passenger<T>* passenger) {
	this->passengers.push_back(passenger);
}

template<class T>
void Driver<T>::addPassengersPickedAt(Vertex<T>* v,
		vector<Passenger<T>*> passengers) {
//	auto ret = this->passengersPickedAt[v] = passengers;
	this->passengersPickedAt.insert(
			std::pair<Vertex<T>*, vector<Passenger<T>*> >(v, passengers));
}

template<class T>
void Driver<T>::addPassengersDroppedAt(Vertex<T>* v,
		vector<Passenger<T>*> passengers) {
	auto ret = this->passengersDroppedAt[v] = passengers;
}

template<class T>
Driver<T>::Driver(int cap) {
	this->capacity = cap;

}

template<class T>
void Driver<T>::updateFreeSpace() {
	unsigned int count = 0;

	for (auto i = this->passengersPickedAt.begin();
			i != this->passengersPickedAt.end();) {
		bool result = false;
		for (auto j : i->second)
			if (j->getPos() == i->first)
				result = true;

		if (result)
			this->passengersPickedAt.erase(i++);
		else
			++i;

	}

	this->capacityAtPath.push_back(this->capacity);
	for (auto i = this->passengersPickedAt.cbegin(), k =
			this->passengersDroppedAt.cbegin();
			count <= this->passengersPickedAt.size();) {
		if (count != 0)
			this->capacityAtPath.push_back(this->capacityAtPath[count - 1]); //inicializa novo elemento com capacidade anterior

		if (count >= 2)
			++k;

		if (count != this->passengersPickedAt.size()) //este vector nao inclui o ultimo ponto
			for (auto j : i->second) //ocupa os lugares dos passageiros que entraram naquele ponto
				//if (j->getPos() != i->first)
				this->capacityAtPath[count] -= j->getNum();

		if (count != 0) //este vector nao inclui o primeiro ponto
			for (auto j : k->second) //desocupa os lugares dos passageiros que sairam naquele ponto
				this->capacityAtPath[count] += j->getNum();

		++count;
		if (count != this->passengersPickedAt.size())
			++i;
	}
}

template<class T>
int Driver<T>::getCapacity() {
	return this->capacity;
}

template<class T>
std::vector<int> Driver<T>::getCapacityAtPath() {
	return this->capacityAtPath;
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
void Driver<T>::clearPassengersDroppedAt() {
	this->passengersDroppedAt.clear();
}

template<class T>
void Driver<T>::clearCapacityAtPath() {
	this->capacityAtPath.clear();
}

template class Driver<int> ;

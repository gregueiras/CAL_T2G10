/*
 * Passenger.h
 *
 *  Created on: Mar 22, 2018
 *      Author: gregu
 */

#pragma once

#include <fstream>

#include "Person.h"
#include "Graph.h"

template<class T> class Vertex;

template<class T>
class Passenger: public Person {
	int numPassengers;
	int timeLimit; //only being considered if route is deviated from the best found thru Dijsktra
	list<Vertex<T>*> path;
	Vertex<T>* source;
	Vertex<T>* pos;
	Vertex<T>* prevPos;
	Vertex<T>* destination;
	bool dropped;
	bool picked;
	T infoSource;
	T infoDestination;
public:
	Passenger();
	Passenger(int numP, Vertex<T>* source, Vertex<T>* destination);
	Passenger(int numP);
	Passenger(string name, int age, int numP);
	Passenger(string name, int age, int numP, int tl);
	Passenger(string name, int age, int numP, int tl, Time startTime);
	Passenger(string name, int age, int numP, int tl, Time startTime, T source, T destination);
	Passenger(int numP, int tl, Vertex<T>* source, Vertex<T>* destination);
	void addPassengers(int num);
	int getNum();
	bool writeToFile(ofstream *output);

//	virtual ~Passenger();
	Vertex<T>* getPos();
	void setPos(Vertex<T>* pos);

	Vertex<T>* getPrevPos();
	void setPrevPos(Vertex<T>* pos);

	Vertex<T>* getSource();
	void setSource(Vertex<T>* pos);

	Vertex<T>* getDestination();
	void setDestination(Vertex<T>* pos);

	void setPicked(bool newPicked) {
		this->picked = newPicked;
	}

	bool getDropped() {
		return this->dropped;
	}

	void setDropped(bool newDropped) {
		this->dropped = newDropped;
	}

	bool getPicked() {
		return this->picked;
	}

	bool operator<(Passenger<T>& p) const{
		return this->numPassengers < p.getNum();
	}

	void setPath(list<Vertex<T>*> path) {
		this->path = path;
	}

	list<Vertex<T>*> getPath() const {
		return this->path;
	}

	T getInfoSource() const {
		return this->infoSource;
	}

	T getInfoDestination() const {
		return this->infoDestination;
	}

	virtual Passenger<T>* clone() const
	{
		return(new Passenger<T>(*this));
	};
};

namespace std
{
	template<class T>
	struct hash<Passenger<T>>
	{
		size_t
			operator()(const Passenger<T> & obj) const
		{
			return hash<std::string>()(obj.getName());
		}
	};
}

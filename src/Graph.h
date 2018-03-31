/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#ifndef _HAS_ITERATOR_DEBUGGING
#define _HAS_ITERATOR_DEBUGGING 0
#endif // !1

#include <stddef.h>
#include <cmath>
#include <iostream>
#include <list>
#include <queue>
#include <vector>
#include <algorithm>

#include "Passenger.h"
#include "Person.h"
#include "Driver.h"

#pragma once
using namespace std;

template<class T> class Edge;
template<class T> class Graph;
template<class T> class Vertex;
template<class T> class Utili;
template<class T> class Passenger;
template<class T> class Driver;
#ifndef INT_MAX
#define INT_MAX 5000
#endif // !1

/****************** Provided structures  ********************/

template<class T>
class Vertex {
	T info;                // contents
	vector<Edge<T> > adj;  // list of outgoing edges
	bool visited;          // auxiliary field used by dfs and bfs
	int indegree;          // auxiliary field used by topsort
	bool processing;       // auxiliary field used by isDAG
	double distance;
	double time;
	Vertex *previous;
	vector<Passenger<T>*> pickedUp;

	void addEdge(Vertex<T> *dest, double w);
	void addEdge(Vertex<T> *dest, double w, int p);
	void addPeopleToEdge(Vertex<T>* vertex, Passenger<T>* passenger);
	//void getPeopleOnEdge
	void removePeopleFromEdge(Vertex<T>* vertex,
			vector<Passenger<T>*> passengers);
	bool removeEdgeTo(Vertex<T> *d);

public:
	Vertex(T in);
	friend class Graph<T> ;
	friend class Utili<T> ;
	T getInfo();
	vector<Edge<T>> getAdj();
	Edge<T> getAdjTo(T dest);
	void pickUp(Passenger<T>* p) {
		this->pickedUp.push_back(p);
	}
	bool operator<(const Vertex<T>& b) const {
		return this->info < b.info;
	}
	bool operator==(const Vertex<T>& b) const {
		return this->info == b.info;
	}
	bool operator!=(const Vertex<T>& b) const {
		return !(this == b);
	}
};

template<class T>
class Utili {
public:
	static Vertex<T>* remMin(vector<Vertex<T>*>& Q);
	static void printPath(const list<Vertex<T>*> path);
	static void removeFromVector(T* elem, vector<T*>& v);
};

//template<class T>
//struct OrderByWeight {
//	bool operator()(Vertex<T> const &a, Vertex<T> const &b) {
//		return a.distance < b.distance;
//	}
//};

template<class T>
class Edge {
	Vertex<T> * dest;      // destination vertex
	double weight = 0;         // edge weight
	int numP;
	vector<Passenger<T>*> waiting;
public:
	Edge();
	Edge(Vertex<T> *d, double w);
	Edge(Vertex<T> *d, double w, int p);

	string getVertexName() {
		return to_string(dest->getInfo());
	}

	void addPeople(int num) {
		numP += num;
	}

	void removePeople(int num) {
		numP -= num;
	}

	int getNumPeople() const {
		return numP;
	}

	double getWeight() const {
		return weight;
	}

	vector<Passenger<T>*> getWaiting() {
		return waiting;
	}

	bool operator<(const Edge<T>& e) const {
		return this->numP < e.getNumPeople();
	}

	friend class Graph<T> ;
	friend class Vertex<T> ;
};

template<class T>
class Graph {
	vector<Vertex<T> *> vertexSet;    // vertex set

	void dfsVisit(Vertex<T> *v, vector<T> & res) const;
	bool dfsIsDAG(Vertex<T> *v) const;
public:
	Vertex<T> *findVertex(const T &in) const;
	int getNumVertex() const;
	bool addVertex(const T &in);
	bool removeVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, double w);
	bool addEdge(const T &sourc, const T &dest, double w, int p);
	bool removeEdge(const T &sourc, const T &dest);
	vector<T> dfs() const;
	vector<T> bfs(const T &source) const;
	vector<T> topsort() const;
	int maxNewChildren(const T &source, T &inf) const;
	bool isDAG() const;
	double dijkstraDistance(T source, T destination);
	double dijkstraPath(T source, T destination, list<Vertex<T>*> &retPath);
	int dijkstraPeopleDistancePath(T source, T destination,
			list<Vertex<T>*> &rePath, vector<Passenger<T>*> &passengers,
			Driver<T>* driver);
	int dijkstraPeopleDistance(T source, T destination);
	bool addPeople(T source, T destination, int num);
	bool addPeople(T source, T destination, Passenger<T>* passenger);
	bool removePeople(vector<Passenger<T>*> passengers, list<Vertex<T>*> path);
	void calculateAndPrintPath(T source, T destination, Driver<T>* driver);

	void postProcessing(Driver<T>* driver, list<Vertex<T>*> path, vector<Passenger<int>*> &passengers);
	bool hasEnougthVacantSeatsOnPath(Driver<T>* driver, Passenger<T> *p, list<Vertex<T>*> path);
	int getPositionOnPath(T source, list<Vertex<T>*> path);
	T getTravelTime(T source, T destination, list<Vertex<T>*> path);

	vector<Passenger<T>*> secondTry(list<Vertex<T>*> path, Driver<T>* driver);
};

/****************** Provided constructors and functions ********************/

template<class T>
Vertex<T>::Vertex(T in) : info(in) {
	visited = false;
	indegree = 0;
	processing = false;
	distance = 0;
	time = 0;
	previous = NULL;
}

template<class T>
Edge<T>::Edge() :
dest(nullptr), weight(-1), numP(-1), waiting(vector<Passenger<T>*> { }) {
}


template<class T>
Edge<T>::Edge(Vertex<T> *d, double w) :
dest(d), weight(w), numP(0), waiting(vector<Passenger<T>*> { }) {
}

template<class T>
Edge<T>::Edge(Vertex<T> *d, double w, int p) :
dest(d), weight(w), numP(p), waiting(vector<Passenger<T>*> { }) {
}

template<class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template<class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
	for (auto v : vertexSet)
		if (v->info == in)
			return v;
	return nullptr;
}

/****************** 1a) addVertex ********************/

/*
 *  Adds a vertex with a given content/info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template<class T>
bool Graph<T>::addVertex(const T &in) {
	// TODO (4 lines)
	// HINT: use the findVertex function to check if a vertex already exists

	if (findVertex(in) != nullptr)
		return false;
	else {
		Vertex<T>* newV = new Vertex<T>(in);
		this->vertexSet.push_back(newV);
		return true;
	}
}

/****************** 1b) addEdge ********************/

/*
 * Adds an edge to a graph (this), given the contents of the source (sourc) and
 * destination (dest) vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template<class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
	// TODO (6 lines)
	// HINT: use findVertex to obtain the actual vertices
	// HINT: use the next function to actually add the edge

	Vertex<T>* tempSrc = findVertex(sourc);
	Vertex<T>* tempDest = findVertex(dest);
	if (tempSrc == nullptr || tempDest == nullptr)
		return false;
	else {
		tempSrc->addEdge(tempDest, w);
		return true;
	}
}

template<class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w, int p) {
	// TODO (6 lines)
	// HINT: use findVertex to obtain the actual vertices
	// HINT: use the next function to actually add the edge

	Vertex<T>* tempSrc = findVertex(sourc);
	Vertex<T>* tempDest = findVertex(dest);
	if (tempSrc == nullptr || tempDest == nullptr)
		return false;
	else {
		tempSrc->addEdge(tempDest, w, p);
		return true;
	}
}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template<class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
	// TODO (1 line)
	this->adj.push_back(Edge<T>(d, w));
}

template<class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w, int p) {
	// TODO (1 line)
	this->adj.push_back(Edge<T>(d, w, p));
}

/****************** 1c) removeEdge ********************/

/*
 * Removes an edge from a graph (this).
 * The edge is identified by the source (sourc) and destination (dest) contents.
 * Returns true if successful, and false if such edge does not exist.
 */
template<class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
	// TODO (5 lines)
	// HINT: Use "findVertex" to obtain the actual vertices.
	// HINT: Use the next function to actually remove the edge.

	Vertex<T>* tempSrc = findVertex(sourc);
	Vertex<T>* tempDest = findVertex(dest);
	if (tempSrc == nullptr || tempDest == nullptr)
		return false;
	else {
		return tempSrc->removeEdgeTo(tempDest);
	}

}

/*
 * Auxiliary function to remove an outgoing edge (with a given destination (d))
 * from a vertex (this).
 * Returns true if successful, and false if such edge does not exist.
 */
template<class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *d) {
	// TODO (6 lines)
	// HINT: use an iterator to scan the "adj" vector and then erase the edge.
	for (auto i = this->adj.begin(); i != this->adj.end(); i++) {
		if ((*i).dest == d) {
			this->adj.erase(i);
			return true;
		}
	}
	return false;
}

/****************** 1d) removeVertex ********************/

/*
 *  Removes a vertex with a given content (in) from a graph (this), and
 *  all outgoing and incoming edges.
 *  Returns true if successful, and false if such vertex does not exist.
 */
template<class T>
bool Graph<T>::removeVertex(const T &in) {
	// TODO (10 lines)
	// HINT: use an iterator to scan the "vertexSet" vector and then erase the vertex.
	// HINT: take advantage of "removeEdgeTo" to remove incoming edges.

	bool res = false;
	Vertex<T> * temp = findVertex(in);

	if (temp == nullptr)
		return false;

	for (auto i = this->vertexSet.begin(); i != this->vertexSet.end(); i++) {
		if ((*i)->info == in) {
			this->vertexSet.erase(i);
			res = true;
		} else
			//			this->removeEdge((*i)->info, in);
			(*i)->removeEdgeTo(temp);
	}

	return res;
}

/****************** 2a) dfs ********************/

/*
 * Performs a depth-first search (dfs) in a graph (this).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */
template<class T>
vector<T> Graph<T>::dfs() const {
	// TODO (7 lines)
	vector<T> res;

	for (auto i : this->vertexSet)
		i->visited = false;

	for (auto i : this->vertexSet) {
		if (i->visited == false)
			dfsVisit(i, res);
	}
	return res;
}

/*
 * Auxiliary function that visits a vertex (v) and its adjacent not yet visited, recursively.
 * Updates a parameter with the list of visited node contents.
 */
template<class T>
void Graph<T>::dfsVisit(Vertex<T> *v, vector<T> & res) const {
	// TODO (7 lines)
	v->visited = true;
	res.push_back(v->info);

	for (auto i : v->adj)
		if (!i.dest->visited)
			dfsVisit(i.dest, res);
}

/****************** 2b) bfs ********************/

/*
 * Performs a breadth-first search (bfs) in a graph (this), starting
 * from the vertex with the given source contents (source).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */
template<class T>
vector<T> Graph<T>::bfs(const T & source) const {
	// TODO (22 lines)
	// HINT: Use the flag "visited" to mark newly discovered vertices .
	// HINT: Use the "queue<>" class to temporarily store the vertices.
	vector<T> res;

	Vertex<T>* src = findVertex(source);
	//	if (src == nullptr)
	//		return nullptr;

	for (auto i : this->vertexSet)
		i->visited = false;

	queue<Vertex<T> *> tempQ;

	tempQ.push(src);

	while (!tempQ.empty()) {
		Vertex<T>* temp = tempQ.front();
		tempQ.pop();

		res.push_back(temp->info);

		for (auto i : temp->adj) {
			if (!i.dest->visited) {
				tempQ.push(i.dest);
				i.dest->visited = true;
			}
		}
	}
	return res;
}

/****************** 2c) toposort ********************/

/*
 * Performs a topological sorting of the vertices of a graph (this).
 * Returns a vector with the contents of the vertices by topological order.
 * If the graph has cycles, returns an empty vector.
 * Follows the algorithm described in theoretical classes.
 */

template<class T>
vector<T> Graph<T>::topsort() const {
	// TODO (26 lines)
	vector<T> res;

	for (auto i : this->vertexSet)
		i->indegree = 0;

	for (auto i : this->vertexSet)
		for (auto j : i->adj)
			j.dest->indegree++;

	queue<Vertex<T> *> C;

	for (auto i : this->vertexSet)
		if (i->indegree == 0)
			C.push(i);

	while (!C.empty()) {
		Vertex<T> * temp = C.front();
		C.pop();

		res.push_back(temp->info);

		for (auto i : temp->adj) {
			i.dest->indegree--;
			if (i.dest->indegree == 0)
				C.push(i.dest);
		}

		//		if (res.size() != this->getNumVertex())
		//			return vector<T> {};

	}

	return res;
}

/****************** 3a) maxNewChildren (HOME WORK)  ********************/

/*
 * Performs a breadth-first search in a graph (this), starting
 * from the vertex with the given source contents (source).
 * During the search, determines the vertex that has a maximum number
 * of new children (adjacent not previously visited), and returns the
 * contents of that vertex (inf) and the number of new children (return value).
 */

template<class T>
int Graph<T>::maxNewChildren(const T & source, T &inf) const {
	// TODO (28 lines, mostly reused)

	int max = { 0 };
	Vertex<T>* src = findVertex(source);
	if (src == nullptr)
		return nullptr;

	for (auto i : this->vertexSet)
		i->visited = false;

	queue<Vertex<T> *> tempQ;

	tempQ.push(src);

	while (!tempQ.empty()) {
		Vertex<T>* temp = tempQ.front();
		tempQ.pop();

		int tempM = { 0 };

		for (auto i : temp->adj) {
			if (!i.dest->visited) {
				tempQ.push(i.dest);
				i.dest->visited = true;
				tempM++;
			}
		}

		if (tempM > max) {
			max = tempM;
			inf = temp->info;
		}
	}
	return max;
}

/****************** 3b) isDAG   (HOME WORK)  ********************/

/*
 * Performs a depth-first search in a graph (this), to determine if the graph
 * is acyclic (acyclic directed graph or DAG).
 * During the search, a cycle is found if an edge connects to a vertex
 * that is being processed in the the stack of recursive calls (see theoretical classes).
 * Returns true if the graph is acyclic, and false otherwise.
 */

template<class T>
bool Graph<T>::isDAG() const {
	// TODO (9 lines, mostly reused)
	// HINT: use the auxiliary field "processing" to mark the vertices in the stack.

	for (auto i : this->vertexSet)
		i->visited = false;

	for (auto i : this->vertexSet) {
		if (i->visited == false) {
			if (!dfsIsDAG(i))
				return false;

		}

	}

	return true;
}

/**
 * Auxiliary function that visits a vertex (v) and its adjacent not yet visited, recursively.
 * Returns false (not acyclic) if an edge to a vertex in the stack is found.
 */
template<class T>
bool Graph<T>::dfsIsDAG(Vertex<T> *v) const {
	// TODO (12 lines, mostly reused)
	if (v->processing)
		return false;

	if (!v->visited) {
		v->processing = true;

		for (auto i : v->adj) {
			//			if (!i.dest->visited)
			if (dfsIsDAG(i.dest) == false)
				return false;
		}

		v->visited = true;
		v->processing = false;

	}

	return true;
}

template<class T>
Vertex<T>* Utili<T>::remMin(vector<Vertex<T> *>& Q) {
	Vertex<T>* temp = Q.front();
	auto minIndex = Q.begin();
	auto count = Q.begin();

	for (Vertex<T>* i : Q) {
		if (i->distance < temp->distance) {
			temp = i;
			minIndex = count;
		}
		count++;
	}

	Q.erase(minIndex);
	return temp;
}

template<class T>
void Utili<T>::removeFromVector(T* elem, vector<T*> &v) {
	for (auto i = v.begin(); i != v.end();) {
		if ((*i) == elem) {
			i = v.erase(i);
		} else
			++i;
	}
}

template<class T>
double Graph<T>::dijkstraDistance(T source, T destination) {

	list<Vertex<T>*> temp;
	return this->dijkstraPath(source, destination, temp);
}

template<class T>
int Graph<T>::dijkstraPeopleDistance(T source, T destination) {

	list<Vertex<T>*> temp;
	vector<Passenger<T>*> temp2;
	Driver<T> d;
	return this->dijkstraPeopleDistancePath(source, destination, temp, temp2,
			&d);
}

template<class T>
int Graph<T>::dijkstraPeopleDistancePath(T source, T destination,
		list<Vertex<T>*> &rePath, vector<Passenger<T>*> &passengers,
		Driver<T>* driver) {

	driver->resetTravel();

	Vertex<T> * start = nullptr;
	Vertex<T> * ending = nullptr;

	vector<Vertex<T>*> Q;

	int capacity = driver->getCapacity();

	for (unsigned int i = 0; i < this->vertexSet.size(); i++) {
		this->vertexSet[i]->distance = INT_MAX;
		this->vertexSet[i]->previous = nullptr;
		this->vertexSet[i]->pickedUp.clear();
		if (this->vertexSet[i]->info == source) {
			start = this->vertexSet[i];
		}
		if (this->vertexSet[i]->info == destination) {
			ending = this->vertexSet[i];
		}
		Q.push_back(this->vertexSet[i]);

	}

	start->distance = 0;
	start->time = 0;
	list<Vertex<T> *> path;
	while (!Q.empty()) {
		Vertex<T>* temp = Utili<T>::remMin(Q);

		int peopleT = 0;
		if (temp->info == ending->info) {
			cout << endl << "Distance: " << temp->distance << endl;

			while (temp->previous != nullptr) {
				cout << temp->time << "  ";
				path.push_front(temp);

				vector<Passenger<T>*> tempPass;

				for (unsigned int k = 0; k < temp->pickedUp.size(); k++) {

					temp->pickedUp[k]->setPos(temp);
					tempPass.push_back(temp->pickedUp[k]);

				}
				driver->addPassengersDroppedAt(temp, tempPass);
				tempPass.clear();

				while (!temp->pickedUp.empty()) {
					peopleT += temp->pickedUp[0]->getNum();
					passengers.push_back(temp->pickedUp[0]);
					driver->addPassenger(temp->pickedUp[0]);
					temp->pickedUp.erase(temp->pickedUp.begin());
				}

				temp = temp->previous;
			}

			path.push_front(temp);
			rePath = path;
			return peopleT;

		}

		Vertex<T>* temp1 = temp;
		int alreadyPicked = 0;

		while (temp1->previous != nullptr) {
			if (!temp1->pickedUp.empty())
				for (auto j : temp1->pickedUp)
					alreadyPicked += j->getNum();
			temp1 = temp1->previous;
		}

		for (unsigned int i = 0; i < temp->adj.size(); i++) {

			int lastAlreadyPicked = alreadyPicked;

			vector<Passenger<T>*> picked;
			int numPicked = 0;
			for (unsigned int j = 0; j < temp->adj[i].waiting.size(); j++) {
				if (temp->adj[i].waiting[j]->getPos() == temp
						&& (alreadyPicked + temp->adj[i].waiting[j]->getNum())
						<= capacity) {
					alreadyPicked += temp->adj[i].waiting[j]->getNum();
					numPicked += temp->adj[i].waiting[j]->getNum();
					picked.push_back(temp->adj[i].waiting[j]);
				}
			}

			double alt = (temp->distance
					+ temp->adj[i].weight / (pow(numPicked, 2) + 1));
			double time = temp->time + temp->adj[i].weight;

			//cout << "Time " << time << "  " << timeLimit << endl;
			if (alreadyPicked <= capacity && time <= driver->getMinLimit()
					&& alt < temp->adj[i].dest->distance) { //TODO Pensar melhor no alt, em por um OR em vez do AND, caso o caminho n melhore, mas temos que cumprir o tempo
				temp->adj[i].dest->distance = alt;
				temp->adj[i].dest->time = time;
				temp->adj[i].dest->previous = temp;

				temp->adj[i].dest->pickedUp = picked;
				if (!picked.empty())
					driver->addPassengersPickedAt(temp, picked);

			}
			alreadyPicked = lastAlreadyPicked;
		}
	}

	return 0;
}

template<class T>
double Graph<T>::dijkstraPath(T source, T destination,
		list<Vertex<T> *>& retPath) {

	Vertex<T> * start = nullptr;
	Vertex<T> * ending = nullptr;

	vector<Vertex<T>*> Q;

	for (unsigned int i = 0; i < this->vertexSet.size(); i++) {
		this->vertexSet[i]->distance = INT_MAX;
		this->vertexSet[i]->previous = nullptr;
		if (this->vertexSet[i]->info == source) {
			start = this->vertexSet[i];
		}
		if (this->vertexSet[i]->info == destination) {
			ending = this->vertexSet[i];
		}
		Q.push_back(this->vertexSet[i]);

	}
	start->distance = 0;
	list<Vertex<T> *> path;

	while (!Q.empty()) {
		Vertex<T>* temp = Utili<T>::remMin(Q);

		if (temp->info == ending->info) {
			while (temp->previous != nullptr) {
				path.push_front(temp);
				temp = temp->previous;
			}

			path.push_front(temp);
			retPath = path;
			return ending->distance;

		}

		for (unsigned int i = 0; i < temp->adj.size(); i++) {
			double alt = temp->distance + temp->adj[i].weight;

			if (alt < temp->adj[i].dest->distance) {
				temp->adj[i].dest->distance = alt;
				temp->adj[i].dest->previous = temp;
			}
		}
	}

	return 0;
}

template<class T>
bool Graph<T>::addPeople(T source, T destination, int num) {

	bool result = false;
	list<Vertex<T>*> path;
	this->dijkstraPath(source, destination, path);

	cout << num << " people added to path: " << endl;
	Utili<T>::printPath(path);

	for (auto i = path.begin(); i != path.end(); i++) {
		auto next = ++i;
		i--;

		if (next == path.end())
			break;

		(*i)->addPeopleToEdge((*next), num);

		result = true;
	}

	return result;
}

template<class T>
bool Graph<T>::addPeople(T source, T destination, Passenger<T>* passenger) {

	bool result = false;
	list<Vertex<T>*> path;
	this->dijkstraPath(source, destination, path);

	cout << (*passenger) << " (" << passenger->getNum() << ") added to path: "
			<< endl;
	passenger->setPos((*path.begin()));
	passenger->setSource((*path.begin()));
	passenger->setDestination(path.back());

	Utili<T>::printPath(path);

	for (auto i = path.begin(); i != path.end(); i++) {
		auto next = ++i;
		i--;

		if (next == path.end())
			break;

		(*i)->addPeopleToEdge((*next), passenger);

		result = true;
	}

	return result;
}

template<class T>
bool Graph<T>::removePeople(vector<Passenger<T>*> passengers,
		list<Vertex<T>*> path) {

	bool result = false;

	for (auto i = path.begin(); i != path.end(); i++) {
		auto j = i;
		auto next = ++j;

		if (next == path.end())
			break;

		(*i)->removePeopleFromEdge((*next), passengers);

		result = true;
	}

	return result;
}

template<class T>
void Graph<T>::calculateAndPrintPath(T source, T destination,Driver<T>* driver) {

	list<Vertex<int>*> path;
	vector<Passenger<int>*> passen;
	cout << endl
	<< this->dijkstraPeopleDistancePath(source, destination, path,
			passen, driver) << endl;

	driver->setPath(path);
	Utili<int>::printPath(path);

	for (auto i = passen.begin(); i != passen.end(); i++)
		cout << (*i)->getName() << " ";

	cout << endl;
	this->removePeople(passen, path);

	driver->updateFreeSpace();

	cout << "\nPicked: \n";
	driver->printPassengersPickedAt();

	cout << "Dropped: \n";
	driver->printPassengersDroppedAt();

	cout << "Cap at Path: " << endl;
	driver->printCapacityAtPath();

	cout << "\nPOSTPROCESSING START\n";

	postProcessing(driver, path, passen);
	this->removePeople(passen, path);

	cout << "\nPOSTPROCESSING END\n";
	for (auto i = passen.begin(); i != passen.end(); i++)
		cout << (*i)->getName() << " ";

	cout << "\nPicked: \n";
	driver->printPassengersPickedAt();

	cout << "Dropped: \n";
	driver->printPassengersDroppedAt();

	cout << "Cap at Path: " << endl;
	driver->printCapacityAtPath();

	cout << "PATH: ";
	Utili<int>::printPath(path);

	passen.clear();
	path.clear();
}

template<class T>
void Graph<T>::postProcessing(Driver<T>* driver, list<Vertex<T>*> path, vector<Passenger<int>*> &passengers) {

	for (auto i = path.begin(); i != path.end(); i++) {
		//i is the vertex in analysis
		//checking adjacent edges
		vector<Edge<T> > adj = (*i)->getAdj();
		sort(adj.rbegin(), adj.rend());
		for (unsigned int j = 0; j < adj.size(); ++j) {
			vector<Passenger<T>*> picked;
			//checking for for possible passengers on each edge
			vector<Passenger<T>*> waiting = adj.at(j).getWaiting();
			//sorting waiting passengers by number of passengers
			sort(waiting.begin(), waiting.end());
			for(unsigned int k = 0; k < waiting.size(); ++k) {
				cout << "Checking: " << (waiting.at(k))->getName() << " from " <<
						(*i)->getInfo() << " to " << adj.at(j).getVertexName() <<
						" :: TL: " << (waiting.at(k))->getTimeLimit()  << " Value: "
						<< (waiting.at(k))->getNum() << endl;
				int tTime = getTravelTime((*i)->getInfo(), (waiting.at(k))->getDestination()->getInfo(),path);
				vector<Passenger<T>*> droped;
				//if it is possible for the passenger to make that route
				if(tTime > 0 && tTime <= (waiting.at(k))->getTimeLimit()) {
					cout << "Passed time limit test: " << (waiting.at(k))->getName() << endl;
					//check if possible for the driver to take the passenger
					if(hasEnougthVacantSeatsOnPath(driver, waiting.at(k), path)) { //This option is prioritizing passengers register, so may not be best cost/efficiency solution
						//Add person to travel schedule
						cout << "Selected: " << (waiting.at(k))->getName() << endl;
						picked.push_back(waiting.at(k));
						droped.push_back(waiting.at(k));
						driver->addPassenger(waiting.at(k));
						driver->updateFreeSpace(waiting.at(k), path);
						passengers.push_back(waiting.at(k));
					} else { //Replace for better final result ?? No, give priority to weight
					}
				}
				if(!droped.empty()) {
					cout << "Added PassengersDroppedAt()" << endl;
					driver->addNewPassengersDroppedAt((waiting.at(k))->getDestination(), droped);
				}
			}
			if (!picked.empty()) {
				cout << "Added PassengersPickedAt()" << endl;
				driver->addNewPassengersPickedAt(*i, picked);
			}
		}
	}
}

template<class T>
bool Graph<T>::hasEnougthVacantSeatsOnPath(Driver<T>* driver, Passenger<T> *p, list<Vertex<T>*> path) {
	T source = p->getSource()->getInfo();
	T destination = p->getDestination()->getInfo();
	int p_size = p->getNum();

	bool hasEnougthSpace = false;
	bool pathStartFound = false;
	int index = 0;
	auto i = path.begin();

	for (; i != path.end() ; i++, index++) {
		if((*i)->getInfo() == destination) {
			break;
		}

		if((*i)->getInfo() == source) {
			pathStartFound = true;
			hasEnougthSpace = true;
		}
		if(pathStartFound) {
			if(driver->getCapacityAtVertexOnPath(index) < p_size) {
				hasEnougthSpace = false;
				break;
			}
		}

	}
	return hasEnougthSpace;
}

template<class T>
int Graph<T>::getPositionOnPath(T source, list<Vertex<T>*> path) {
	int pos = 0;
	for (auto i = path.begin(); i != path.end(); i++) {
		if((*i)->getInfo() == source) {
			return pos;
		}
		++pos;
	}
	return -1;
}

template<class T>
T Graph<T>::getTravelTime(T source, T destination, list<Vertex<T>*> path) {
	T travelTime = 0;

	bool pathStartFound = false;
	bool pathEndFound = false;
	for (auto i = path.begin(); i != path.end(); i++) {
		if((*i)->getInfo() == source) {
			pathStartFound = true;
		} else if((*i)->getInfo() == destination) {
			pathEndFound = true;
			break;
		}

		if(pathStartFound) {
			auto tmp = i;
			++tmp;
			if(tmp == path.end())
				break;
			travelTime += (*i)->getAdjTo((*tmp)->getInfo()).getWeight();
		}
	}

	if(pathStartFound && pathEndFound)
		return travelTime;
	else
		return -1;
}

template<class T>
void Vertex<T>::addPeopleToEdge(Vertex<T>* vertex, Passenger<T>* passenger) {
	for (unsigned int j = 0; j < this->adj.size(); j++) {

		if (this->adj.at(j).dest->getInfo() == vertex->getInfo()) {
			this->adj.at(j).addPeople(passenger->getNum());
			this->adj.at(j).waiting.push_back(passenger);
		}
	}
}

template<class T>
void Vertex<T>::removePeopleFromEdge(Vertex<T>* vertex,
		vector<Passenger<T>*> passengers) {
	for (unsigned int j = 0; j < this->adj.size(); j++) {

		if (this->adj.at(j).dest->getInfo() == vertex->getInfo()) {
			for (unsigned int k = 0; k < passengers.size(); k++) {
				//this->adj.at(j).removePeople(passengers.at(k)->getNum());
				Utili<Passenger<T>>::removeFromVector(passengers.at(k),
						this->adj.at(j).waiting);

			}
		}
	}
}

template<class T>
T Vertex<T>::getInfo() {
	return this->info;
}

template<class T>
vector<Edge<T> > Vertex<T>::getAdj() {
	return this->adj;
}

template<class T>
Edge<T> Vertex<T>::getAdjTo(T dest) {
	for (auto i : this->adj) {
		if (i.dest->info == dest)
			return i;
	}

	Edge<T> errorEdge = Edge<T>();
	return errorEdge;
}

template<class T>
void Utili<T>::printPath(const list<Vertex<T> *> path) {
	for (auto i = path.begin(); i != path.end(); i++) {
		cout << (*i)->getInfo() << " ";
	}
	cout << endl;
}

#endif /* GRAPH_H_ */

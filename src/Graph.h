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
#include <set>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <unordered_set>
#include <iomanip>

#include "Passenger.h"
#include "Person.h"
#include "Driver.h"
#include "MutablePriorityQueue.h"
#include "graphviewer.h"


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
class VertexPtr {
	Vertex<T> * v;
public:
	VertexPtr(Vertex<T> * v) {
		this->v=v;
	}
	bool operator<(const VertexPtr<T> &b) const {
		return (this->v)->info < (b.v)->info;
	}

	friend class Graph<T> ;
};

template class VertexPtr<int> ;

template<class T>
class Vertex {
	T info;                // contents
	unsigned long x;		//coordinate
	unsigned long y;		//coordinate
	vector<Edge<T> > adj;  // list of outgoing edges
	bool visited;          // auxiliary field used by dfs and bfs
	int indegree;          // auxiliary field used by topsort
	bool processing;       // auxiliary field used by isDAG
	set<VertexPtr<T>> notConected;// non-connected vertexes
	double distance;
	double time;
	Vertex *previous;
	int queueIndex = 0;
	vector<Passenger<T>*> pickedUp;

	void addEdge(Vertex<T> *dest, double w);
	void addEdge(Vertex<T> *dest, double w, int p);
	void addPeopleToEdge(Vertex<T>* vertex, Passenger<T>* passenger);
	//void getPeopleOnEdge
	void removePeopleFromEdge(Vertex<T>* vertex,
			Passenger<T>* passenger);
	bool removeEdgeTo(Vertex<T> *d);
	void updateVertexConnectivity(Graph<T> *g, Vertex<T> *v);
	bool writeVertexToFile(ofstream *output);

public:
	Vertex(T in, unsigned long x, unsigned long y);
	friend class Graph<T> ;
	friend class Utili<T> ;
	friend class MutablePriorityQueue<Vertex<T>>;

	T getInfo();
	unsigned long getX();
	unsigned long getY();
	vector<Edge<T>> getAdj();
	Edge<T> getAdjTo(T dest);
	void pickUp(Passenger<T>* p) {
		this->pickedUp.push_back(p);
	}
	bool operator<(const Vertex<T>& b) const {
		return this->distance < b.distance;
	}
	bool operator==(const Vertex<T>& b) const {
		return this->info == b.info;
	}
	bool operator!=(const Vertex<T>& b) const {
		return !(this == b);
	}

	friend class VertexPtr<T> ;
};

template<class T>
class Utili {
public:
	static Vertex<T>* remMin(vector<Vertex<T>*>& Q);
	static void printPath(const list<Vertex<T>*> path);
	static void removeFromVector(T* elem, vector<T*>& v);
	static void setPassengersPath(vector<Passenger<T>*> passengers, const list<Vertex<T>*> path);
};


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
	bool addVertex(const T &in, unsigned long x, unsigned long y);
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

	void removePeople(vector<Passenger<T>*> passengers);
	bool existsAndHasEnoughTime(T & source, T & destination, Person* driver,list<Vertex<int>*> &path);
	bool calculatePath(T source, T destination, Driver<T>* driver);
	void calculateAndPrintPath(T source, T destination, Driver<T>* driver, bool wasPreProcessed);

	void postProcessing(Driver<T>* driver, list<Vertex<T>*> path, vector<Passenger<int>*> &passengers);
	bool hasEnougthVacantSeatsOnPath(Driver<T>* driver, Passenger<T> *p, list<Vertex<T>*> path);
	int getPositionOnPath(T source, list<Vertex<T>*> path);
	double getTravelTime(T source, T destination, list<Vertex<T>*> path);

	vector<Passenger<T>*> secondTry(list<Vertex<T>*> path, Driver<T>* driver);
	void addGraphToViewer(GraphViewer *gv) const;
	void updateGraphConnectivity();
	void printNotConnected();

	bool writeToFile(string companyName);
	bool readFromFile(string companyName);

};


/****************** Provided constructors and functions ********************/

template<class T>
Vertex<T>::Vertex(T in, unsigned long x, unsigned long y) : info(in) {
	this->x = x;
	this->y = y;
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
bool Graph<T>::addVertex(const T &in, unsigned long x, unsigned long y) {
	// TODO (4 lines)
	// HINT: use the findVertex function to check if a vertex already exists

	if (findVertex(in) != nullptr)
		return false;
	else {
		Vertex<T>* newV = new Vertex<T>(in, x, y);
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
	else{
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

template<class T>
void Vertex<T>::updateVertexConnectivity(Graph<T> *g, Vertex<T> *v) {
	if(this->notConected.find(VertexPtr<T>(v)) != this->notConected.end()) {
		this->notConected.erase(VertexPtr<T>(v));
		for(unsigned int i = 0; i < v->adj.size(); i++) {
			updateVertexConnectivity(g, v->adj.at(i).dest);
		}
	}
}

template<class T>
bool Vertex<T>::writeVertexToFile(ofstream *output) {
	if (output->is_open()) {
		*output << "V " << this->info << " " << this->x << " " << this->y << endl;
		for(unsigned int i = 0; i < this->adj.size(); ++i) {
			*output << "\tE" << this->adj.at(i).dest->info << " " << this->adj.at(i).weight << endl;
		}
	} else
		return false;
	return true;
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

	for (auto i = this->vertexSet.begin(); i != this->vertexSet.end();) {
		if ((*i)->info == in) {
			i = this->vertexSet.erase(i);
			res = true;
		}
		else {
			//			this->removeEdge((*i)->info, in);
			(*i)->removeEdgeTo(temp);
			++i;
		}
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
void Utili<T>::setPassengersPath(vector <Passenger<T>*> passengers, const list<Vertex<T>*> path) {
	for (auto p = passengers.begin(); p != passengers.end(); ++p) {
		auto pathBegin = path.end();
		auto pathEnd = path.end();

		bool beginFound = false;
		bool endFound = false;

		for (auto i = path.begin(); i != path.end(); ++i) {
			if ((*i) == (*p)->getSource()) {
				pathBegin = i;
				beginFound = true;
			}

			else if ((*i) == (*p)->getPos()) {
				pathEnd = i;
				endFound = true;
			}

			if (pathEnd != path.end()) {
				++pathEnd;
				break;
			}

		}
		if (beginFound && endFound) {
			list<Vertex<T>*> passengerPath;
			passengerPath.insert(passengerPath.end(), pathBegin, pathEnd);
			(*p)->setPath(passengerPath);
		}
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

	//Vertex<T> * start = nullptr;
	Vertex<T> * ending = nullptr;

	//vector<Vertex<T>*> Q;
	MutablePriorityQueue<Vertex<T>> Q;


	int capacity = driver->getCapacity();

	for (unsigned int i = 0; i < this->vertexSet.size(); i++) {
		this->vertexSet[i]->distance = INT_MAX;
		this->vertexSet[i]->previous = nullptr;
		this->vertexSet[i]->pickedUp.clear();
		if (this->vertexSet[i]->info == source) {
			//start = this->vertexSet[i];
			this->vertexSet[i]->distance = 0;
			this->vertexSet[i]->time = 0;
		}
		if (this->vertexSet[i]->info == destination) {
			ending = this->vertexSet[i];
		}
		//Q.push_back(this->vertexSet[i]);
		Q.insert(vertexSet[i]);
	}

	if (ending == nullptr)
		return -1;

	list<Vertex<T> *> path;
	while (!Q.empty()) {
		//Vertex<T>* temp = Utili<T>::remMin(Q);
		Vertex<T>* temp = Q.extractMin();

		int peopleT = 0;
		if (temp->info == ending->info) { //fim do algoritmo, chegamos ao destino
			//cout << endl << "Distance: " << temp->distance << endl; //distancia final (pesada com os passageiros transportados)

			while (temp->previous != nullptr) { //percorre o caminho por ordem reversa
				//cout << temp->time << "  ";
				path.push_front(temp);

				vector<Passenger<T>*> tempPass;

				for (unsigned int k = 0; k < temp->pickedUp.size(); k++) {
					temp->pickedUp[k]->updateCurrentTime(temp->time);
					if (!temp->pickedUp[k]->getDropped()) {
						tempPass.push_back(temp->pickedUp[k]);
						temp->pickedUp[k]->setDropped(true);
					}

				}
				driver->addPassengersDroppedAt(temp, tempPass);

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
			driver->increaseTransportedPassengers(peopleT);
			return peopleT;

		}

		//Vertex<T>* temp1 = temp;
		int alreadyPicked = 0;

		set<Vertex<T>*> VertexFuturePath;

		//cout << "A: " << endl;
		//driver->printPassengersPickedAt(); cout << endl;

		auto pickedTemp = driver->getPassengersPickedAt();
		for (auto i = pickedTemp.cbegin(); i != pickedTemp.cend(); ++i)
		{
			for (auto j : i->second)
				if (j->getDestination() != j->getPos() && j->getDestination() != temp)
					alreadyPicked += j->getNum();
		}

		//cout << "ALREADY PICKED \n";
		//cout << temp->getInfo() << " cap " << alreadyPicked << endl;

		for (unsigned int i = 0; i < temp->adj.size(); i++) {

			int lastAlreadyPicked = alreadyPicked;

			driver->updateCurrentTime(temp->time);

			vector<Passenger<T>*> picked;
			int numPicked = 0;
			for (unsigned int j = 0; j < temp->adj[i].waiting.size(); j++) {

				if (temp->adj[i].waiting[j]->getPos() == temp
						&& (alreadyPicked + temp->adj[i].waiting[j]->getNum())
						<= capacity  && temp->adj[i].waiting[j]->getCurrentTime() <= driver->getCurrentTime()
						&& driver->getCurrentTime() < (temp->adj[i].waiting.at(j)->getStartTime() + Time(0, temp->adj[i].waiting.at(j)->getTimeLimit()))) {

					if (!temp->adj[i].waiting[j]->getPicked()) //this passenger is already in alreadyPicked
						alreadyPicked += temp->adj[i].waiting[j]->getNum();

					numPicked += temp->adj[i].waiting[j]->getNum();
					picked.push_back(temp->adj[i].waiting[j]);
				}
			}

			double alt = (temp->distance
					+ temp->adj[i].weight / (pow(numPicked, 2) + 1));
			double time = temp->time + temp->adj[i].weight;

			//cout << "Time " << time << "  " << driver->getMinLimit() << endl;
			if (alreadyPicked <= capacity && time <= driver->getTimeLimit()
					&& alt < temp->adj[i].dest->distance) { //TODO Pensar melhor no alt, em por um OR em vez do AND, caso o caminho n melhore, mas temos que cumprir o tempo
				temp->adj[i].dest->distance = alt;
				temp->adj[i].dest->time = time;
				temp->adj[i].dest->previous = temp;
				temp->adj[i].dest->pickedUp = picked;

				if (temp->adj[i].dest->queueIndex != 0)
					Q.decreaseKey(temp->adj[i].dest);

				for (auto m = picked.begin(); m != picked.end(); ) {
					(*m)->setPrevPos((*m)->getPos());
					(*m)->setPos(temp->adj[i].dest);

					if ((*m)->getPicked())
						m = picked.erase(m);
					else {
						(*m)->setPicked(true);
						++m;
					}

				}

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

	MutablePriorityQueue<Vertex<T>> Q;

	for (unsigned int i = 0; i < this->vertexSet.size(); i++) {
		this->vertexSet[i]->distance = INT_MAX;
		this->vertexSet[i]->previous = nullptr;

		if (this->vertexSet[i]->info == source) {
			start = this->vertexSet[i];
			this->vertexSet[i]->distance = 0;
		} else if (this->vertexSet[i]->info == destination) {
			ending = this->vertexSet[i];
		}
		//Q.push_back(this->vertexSet[i]);
		Q.insert(vertexSet[i]);

	}
	if (start == nullptr && ending == nullptr)
		return -3;
	if (start == nullptr)
		return -1;
	if (ending == nullptr)
		return -2;


	list<Vertex<T> *> path;


	while (!Q.empty()) {
		//Vertex<T>* temp = Utili<T>::remMin(Q);
		Vertex<T>* temp = Q.extractMin();

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
				if (temp->adj[i].dest->queueIndex != 0)
					Q.decreaseKey(temp->adj[i].dest);
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

	bool sFound = false;
	bool dFound = false;
	Vertex<T> *s;
	Vertex<T> *d;
	for(unsigned int i = 0; i < this->vertexSet.size(); ++i) {
		if(sFound && dFound) {
			break;
		} else if(this->vertexSet.at(i)->info == source) {
			s = this->vertexSet.at(i);
			sFound = true;
		} else if(this->vertexSet.at(i)->info == destination) {
			d = this->vertexSet.at(i);
			dFound = true;
		}
	}

	if(!(sFound && dFound)) {
		cout << "Source and/or Destination don't exist.\n";
		return false;
	}

	if(s->notConected.find(VertexPtr<T>(d)) != s->notConected.end()) {
		cout << "Source and Destination are not connected.\n";
		return false;
	}

	bool result = false;
	list<Vertex<T>*> path;
	if (!existsAndHasEnoughTime(source, destination, passenger,path))
		return false;

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

//template<class T>
//bool Graph<T>::removePeople(vector<Passenger<T>*> passengers,
//		list<Vertex<T>*> path) {
//
//	bool result = false;
//
//	for (auto i = path.begin(); i != path.end(); i++) {
//		auto j = i;
//		auto next = ++j;
//
//		if (next == path.end())
//			break;
//
//		(*i)->removePeopleFromEdge((*next), passengers);
//
//		result = true;
//	}
//
//	return result;
//}

template<class T>
void Graph<T>::removePeople(vector<Passenger<T>*> passengers)
{
	for (auto p = passengers.begin(); p != passengers.end(); ++p) {
		list<Vertex<T>*> pPath = (*p)->getPath();
		for (auto i = pPath.begin(); i != pPath.end(); ++i) {
			auto j = i;
			auto next = ++j;

			if (next == pPath.end())
				break;

			(*i)->removePeopleFromEdge((*next), (*p));
		}
	}
}

template<class T>
bool Graph<T>::existsAndHasEnoughTime(T &source, T &destination, Person* person, list<Vertex<int>*>& path)
{
	double tempDistance = this->dijkstraPath(source, destination,path);
	if (tempDistance == -1) {
		cout << source << " doesn't exist." << endl;
		return false;
	}
	else if (tempDistance == -2) {
		cout << destination << " doesn't exist." << endl;
		return false;
	}
	else if (tempDistance == -3) {
		cout << source << " and " << destination << " don't exist." << endl;
		return false;
	}
	else if (tempDistance == INT_MAX) {
		cout << source << " and " << destination << " are not connected. Invalid path" << endl;
		return false;
	}
	else if (tempDistance > person->getTimeLimit()) {
		cout << person->getName() << " has not enough time to go from " << source << " to " << destination << endl;
		return false;
	}
	return true;
}


template<class T>
bool Graph<T>::calculatePath(T source, T destination, Driver<T>* driver)
{
	list<Vertex<int>*> path;
	list<Vertex<int>*> tpath;
	vector<Passenger<int>*> passen;

	if (!existsAndHasEnoughTime(source, destination, driver, tpath))
		return false;


	this->dijkstraPeopleDistancePath(source, destination, path,
			passen, driver);

	//driver->setPath(path);
	//Utili<int>::setPassengersPath(passen, path);
	///*this->removePeople(passen, path);*/
	//this->removePeople(passen);

	//driver->updateFreeSpace();

	//postProcessing(driver, path, passen);
	////this->removePeople(passen, path);
	//this->removePeople(passen);

	//passen.clear();
	//path.clear();
	return true;
}


template<class T>
void Graph<T>::calculateAndPrintPath(T source, T destination,Driver<T>* driver, bool wasPreProcessed) {

	list<Vertex<int>*> path;
	list<Vertex<int>*> tpath;
	vector<Passenger<int>*> passen;

	if (!wasPreProcessed)
		if (!existsAndHasEnoughTime(source, destination, driver,tpath))
			return;

//	cout << endl
//			<< this->dijkstraPeopleDistancePath(source, destination, path,
//					passen, driver) << endl;

	dijkstraPeopleDistancePath(source, destination, path,passen, driver);

	Utili<int>::setPassengersPath(passen, path);

	driver->setPath(path);
	//Utili<int>::printPath(path);
	//
	////	for (auto i = passen.begin(); i != passen.end(); i++)
	////		cout << (*i)->getName() << " ";
	//
	cout << endl;
	//this->removePeople(passen, path);
	this->removePeople(passen);

	driver->updateFreeSpace();

//	cout << "\nPicked: \n";
//	driver->printPassengersPickedAt();
//
//	cout << "Dropped: \n";
//	driver->printPassengersDroppedAt();
//
//	cout << "Cap at Path: " << endl;
//	driver->printCapacityAtPath();
//
//	cout << "\nPOSTPROCESSING START\n";

	postProcessing(driver, path, passen);
	//this->removePeople(passen, path);
	this->removePeople(passen);
//
//	cout << "\nPOSTPROCESSING END\n";
//	//	for (auto i = passen.begin(); i != passen.end(); i++)
//	////		cout << (*i)->getName() << " ";
//
//	cout << "\nPicked: \n";
//	driver->printPassengersPickedAt();
//
//	cout << "Dropped: \n";
//	driver->printPassengersDroppedAt();
//
//	cout << "Cap at Path: " << endl;
//	driver->printCapacityAtPath();
//
//	cout << "PATH: ";
//	Utili<int>::printPath(path);

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
				//cout << "Checking: " << (waiting.at(k))->getName() << " from " <<
						//(*i)->getInfo() << " to " << adj.at(j).getVertexName() <<
						//" :: TL: " << (waiting.at(k))->getTimeLimit()  << " Value: "
						//<< (waiting.at(k))->getNum() << endl;
				int tTime = getTravelTime((*i)->getInfo(), (waiting.at(k))->getDestination()->getInfo(),path);
				vector<Passenger<T>*> droped;
				//to check the time
				Time driverTime(driver->getStartTime());
				driverTime.addMinutes( (*i)->time );
				//if it is possible for the passenger to make that route
				if(tTime > 0 && tTime <= (waiting.at(k))->getTimeLimit() && (waiting.at(k))->getCurrentTime() <= driverTime
						&& (waiting.at(k))->getPos() == (*i) && driver->getCurrentTime() < (waiting.at(k)->getStartTime() + Time(0,waiting.at(k)->getTimeLimit())))
				{
					//cout << "Passed time limit test: " << (waiting.at(k))->getName() << endl;
					//check if possible for the driver to take the passenger
					if(hasEnougthVacantSeatsOnPath(driver, waiting.at(k), path)) { //This option is prioritizing passengers register, so may not be best cost/efficiency solution
						//Add person to travel schedule
						//cout << "Selected: " << (waiting.at(k))->getName() << endl;
						picked.push_back(waiting.at(k));
						droped.push_back(waiting.at(k));
						driver->addPassenger(waiting.at(k));
						driver->updateFreeSpace(waiting.at(k), path);
						passengers.push_back(waiting.at(k));
						driver->increaseTransportedPassengers();
						waiting.at(k)->setPos(waiting.at(k)->getDestination());
					} else { //Replace for better final result ?? No, give priority to weight
					}
				}
				if(!droped.empty()) {
					//cout << "Added PassengersDroppedAt()" << endl;
					driver->addNewPassengersDroppedAt((waiting.at(k))->getDestination(), droped);
				}
			}
			if (!picked.empty()) {
				//cout << "Added PassengersPickedAt()" << endl;
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
double Graph<T>::getTravelTime(T source, T destination, list<Vertex<T>*> path) {
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
void Graph<T>::updateGraphConnectivity() {
	for(unsigned int i = 0; i < vertexSet.size(); ++i) {
		//add all vertexes to non connected
		for(unsigned int j = 0; j < vertexSet.size(); ++j) {
			vertexSet.at(i)->notConected.insert(vertexSet.at(j));
		}

		vertexSet.at(i)->updateVertexConnectivity(this, vertexSet.at(i));
	}

}

template<class T>
void Graph<T>::printNotConnected() {
	cout << "Not Connected Vertex:\n";
	for(unsigned int i = 0; i < vertexSet.size(); ++i) {
		cout << "Vertex " << vertexSet.at(i)->info << ": ";
		for(auto it = vertexSet.at(i)->notConected.begin(); it != vertexSet.at(i)->notConected.end(); ++it) {
			cout << (*it).v->info << "; ";
		}
		cout << endl;
	}
}

template<class T>
bool Graph<T>::writeToFile(string companyName) {
	bool result = true;
	string fileName = companyName + "Graph.txt";
	ofstream output(fileName);
	for(unsigned int i = 0; i < this->vertexSet.size(); ++i) {
		result &= this->vertexSet.at(i)->writeVertexToFile(&output);
	}

	output.close();
	return result;
}

template<class T>
bool Graph<T>::readFromFile(string companyName) {
	string file = companyName + "Graph.txt";
	string line;
	ifstream input;
	stringstream lineStream;

	input.open(file);
	if (input.is_open()) {
		while(!input.eof()) {
			char type;
			getline(input, line);
			lineStream.clear();
			lineStream.str(line);
			lineStream >> type;
			if(type == '\t')
				continue;
			T info;
			unsigned long x, y;

			lineStream >> info;
			lineStream >> x;
			lineStream >> y;
			this->addVertex(info, x, y);
		}

		input.clear();
		input.seekg(0, ios::beg);

		T source;
		while(!input.eof()) {
			char type;
			getline(input, line);
			lineStream.clear();
			lineStream.str(line);
			lineStream >> type;
			if(type == 'V') {
				lineStream >> source;
				continue;
			}
			T destination;
			double weight;

			lineStream >> destination;
			lineStream >> weight;
			this->addEdge(source, destination, weight);
		}
	} else {
		return false;
	}
	input.close();
	return true;
}

template<class T>
void Graph<T>::addGraphToViewer(GraphViewer *gv) const{
	int edgeId = 0;
	for(auto it1 = this->vertexSet.begin(); it1 != this->vertexSet.end(); ++it1) {
		gv->addNode((*it1)->info, (*it1)->x, (*it1)->y);

		for(auto it2 = (*it1)->adj.begin(); it2 != (*it1)->adj.end(); ++it2) {
			gv->addEdge(edgeId, (*it1)->info, (*it2).dest->info, EdgeType::DIRECTED);

			stringstream stream;
			stream << fixed << setprecision(2) << (*it2).weight;
			string s = stream.str();
			gv->setEdgeLabel(edgeId++, s);
		}
	}
}

template<class T>
void Vertex<T>::addPeopleToEdge(Vertex<T>* vertex, Passenger<T>* passenger) {
	for (unsigned int j = 0; j < this->adj.size(); j++) {

		if (this->adj.at(j).dest->getInfo() == vertex->getInfo()) {
			this->adj.at(j).addPeople(passenger->getNum());
			this->adj.at(j).waiting.push_back(passenger);
		}
		std::sort(this->adj.at(j).waiting.begin(), this->adj.at(j).waiting.end(),
				[](const auto& lhs, const auto& rhs) {
			return lhs->getNum() > rhs->getNum();
		});

	}
}




template<class T>
void Vertex<T>::removePeopleFromEdge(Vertex<T>* vertex,
		Passenger<T>* passenger) {
	for (unsigned int j = 0; j < this->adj.size(); j++) {

		if (this->adj.at(j).dest->getInfo() == vertex->getInfo()) {
			//this->adj.at(j).removePeople(passengers.at(k)->getNum());

			if (passenger->getName() == "Adam")
			{
				cout << "";
			}
			Utili<Passenger<T>>::removeFromVector(passenger,
					this->adj.at(j).waiting);


		}
	}
}

template<class T>
T Vertex<T>::getInfo() {
	return this->info;
}

template<class T>
unsigned long Vertex<T>::getX() {
	return this->x;
}

template<class T>
unsigned long Vertex<T>::getY() {
	return this->y;
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

/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <stddef.h>
#include <iostream>
#include <list>
#include <queue>
#include <vector>

#include "Passenger.h"

#pragma once
using namespace std;

template<class T> class Edge;
template<class T> class Graph;
template<class T> class Vertex;
template<class T> class Utili;
template<class T> class Passenger;
#define INT_MAX 5000

/****************** Provided structures  ********************/

template<class T>
class Vertex {
	T info;                // contents
	vector<Edge<T> > adj;  // list of outgoing edges
	bool visited;          // auxiliary field used by dfs and bfs
	int indegree;          // auxiliary field used by topsort
	bool processing;       // auxiliary field used by isDAG
	double distance;
	Vertex *previous;
	vector<Passenger<T>*> pickedUp;

	void addEdge(Vertex<T> *dest, double w);
	void addEdge(Vertex<T> *dest, double w, int p);
	void addPeopleToEdge(Vertex<T>* vertex, Passenger<T>* passenger);
	void removePeopleFromEdge(Vertex<T>* vertex, vector<Passenger<T>*> passengers);
	bool removeEdgeTo(Vertex<T> *d);
public:
	Vertex(T in);
	friend class Graph<T> ;
	friend class Utili<T> ;
	T getInfo();
	vector<Edge<T>> getAdj();
	Edge<T> getAdjTo(T dest);
};

template<class T>
bool operator==(const Vertex<T>& lhs, const Vertex<T>& rhs)
{
	return lhs.getInfo() == rhs.getInfo();
}

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
	Edge(Vertex<T> *d, double w);
	Edge(Vertex<T> *d, double w, int p);

	void addPeople(int num) {
		numP += num;
	}

	void removePeople(int num)
	{
		numP -= num;
	}

	int getNumPeople() const {
		return numP;
	}

	double getWeight() const {
		return weight;
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
	int dijkstraDistance(T source, T destination);
	int dijkstraPath(T source, T destination, list<Vertex<T>*> &retPath);
	int dijkstraPeopleDistancePath(T source, T destination,
			list<Vertex<T>*> &rePath, vector<Passenger<T>*> &passengers);
	int dijkstraPeopleDistance(T source, T destination);
	bool addPeople(T source, T destination, int num);
	bool addPeople(T source, T destination, Passenger<T>* passenger);
	bool removePeople(vector<Passenger<T>*> passengers, list<Vertex<T>*> path);
};

/****************** Provided constructors and functions ********************/

template<class T>
Vertex<T>::Vertex(T in) :
		info(in) {
}

template<class T>
Edge<T>::Edge(Vertex<T> *d, double w) :
		dest(d), weight(w), numP(0), waiting(NULL) {
}

template<class T>
Edge<T>::Edge(Vertex<T> *d, double w, int p) :
		dest(d), weight(w), numP(p), waiting(NULL) {
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
	return NULL;
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

	if (findVertex(in) != NULL)
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
	if (tempSrc == NULL || tempDest == NULL)
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
	if (tempSrc == NULL || tempDest == NULL)
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
	if (tempSrc == NULL || tempDest == NULL)
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

	if (temp == NULL)
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
//	if (src == NULL)
//		return NULL;

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
		return NULL;

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
void Utili<T>::removeFromVector(T* elem, vector<T*> &v)
{
	for(auto i = v.begin(); i != v.end(); i++)
	{
		if ((*i) == elem)
		{
			i = v.erase(i);
			i--;
		}
	}
}


template<class T>
int Graph<T>::dijkstraDistance(T source, T destination) {

	list<Vertex<T>*> temp;
	return this->dijkstraPath(source, destination, temp);
}

template<class T>
int Graph<T>::dijkstraPeopleDistance(T source, T destination) {

	list<Vertex<T>*> temp;
	vector<Passenger<T>*> temp2;
	return this->dijkstraPeopleDistancePath(source, destination, temp, temp2);
}

template<class T>
int Graph<T>::dijkstraPeopleDistancePath(T source, T destination,
		list<Vertex<T>*> &rePath, vector<Passenger<T>*> &passengers) {

	Vertex<T> * start;
	Vertex<T> * ending;

	vector<Vertex<T>*> Q;

	int capacity = 20;

	for (unsigned int i = 0; i < this->vertexSet.size(); i++) {
		this->vertexSet[i]->distance = INT_MAX;
		this->vertexSet[i]->previous = NULL;
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
	list<Vertex<T> *> path;
	while (!Q.empty()) {
		Vertex<T>* temp = Utili<T>::remMin(Q);

		int peopleT = 0;
		if (temp->info == ending->info) {
			cout << endl << "Distance: " << temp->distance << endl;
			while (temp->previous != NULL) {
				path.push_front(temp);
				while (!temp->pickedUp.empty()) {
					peopleT += temp->pickedUp[0]->getNum();
					passengers.push_back(temp->pickedUp[0]);
					temp->pickedUp.erase(temp->pickedUp.begin());
				}
//				cout << temp->info << " ";
				temp = temp->previous;
			}

			path.push_front(temp);
			rePath = path;
//			cout << temp->info << " " << endl;
			return peopleT;

		}

		for (unsigned int i = 0; i < temp->adj.size(); i++) {

			int alreadyPicked = 0;
			Vertex<T>* temp1 = temp;
			while (temp1->previous != NULL) {
				if (!temp1->pickedUp.empty())
					for (auto j : temp1->pickedUp)
						alreadyPicked += j->getNum();
				temp1 = temp1->previous;
			}
//			cout << temp->getInfo() << "  " << alreadyPicked << endl;

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

//			int alt = (temp->distance + temp->adj[i].weight / (temp->adj[i].numP + 1));
			double alt = (temp->distance + temp->adj[i].weight / (pow(numPicked,2) + 1));
//			if (numPicked > 5)
//				alt = alt*0.5;

			if (alreadyPicked <= capacity
					&& alt < temp->adj[i].dest->distance) {
				temp->adj[i].dest->distance = alt;
				temp->adj[i].dest->previous = temp;
//				temp->adj[i].dest->pickedUp = temp->adj[i].waiting;

				for (unsigned int k = 0; k < picked.size(); k++)
					picked[k]->setPos(temp);

				temp->adj[i].dest->pickedUp = picked;

			}
		}
	}

	return 0;
}

template<class T>
int Graph<T>::dijkstraPath(T source, T destination,
		list<Vertex<T> *>& retPath) {

	Vertex<T> * start;
	Vertex<T> * ending;

	vector<Vertex<T>*> Q;

	for (unsigned int i = 0; i < this->vertexSet.size(); i++) {
		this->vertexSet[i]->distance = INT_MAX;
		this->vertexSet[i]->previous = NULL;
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
			while (temp->previous != NULL) {
				path.push_front(temp);
//				cout << temp->info << " ";
				temp = temp->previous;
			}

			path.push_front(temp);
//			cout << temp->info << " " << endl;
			retPath = path;
			return ending->distance;

		}

		for (unsigned int i = 0; i < temp->adj.size(); i++) {
			int alt = temp->distance + temp->adj[i].weight;

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

	cout << (*passenger) << " added to path: " << endl;
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
bool Graph<T>::removePeople(vector<Passenger<T>*> passengers, list<Vertex<T>*> path) {

	bool result = false;

	for (auto i = path.begin(); i != path.end(); i++) {
		auto next = ++i;
		i--;

		if (next == path.end())
			break;

		(*i)->removePeopleFromEdge((*next), passengers);

		result = true;
	}

	return result;
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
void Vertex<T>::removePeopleFromEdge(Vertex<T>* vertex, vector<Passenger<T>*> passengers) {
	for (unsigned int j = 0; j < this->adj.size(); j++) {

		if (this->adj.at(j).dest->getInfo() == vertex->getInfo()) {
			for(unsigned int k = 0; k < passengers.size(); k++)
			{
				//this->adj.at(j).removePeople(passengers.at(k)->getNum());
				Utili<Passenger<T>>::removeFromVector(passengers.at(k),this->adj.at(j).waiting);

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

}

template<class T>
void Utili<T>::printPath(const list<Vertex<T> *> path) {
	for (auto i = path.begin(); i != path.end(); i++) {
		cout << (*i)->getInfo() << " ";
	}
	cout << endl;
}

#endif /* GRAPH_H_ */

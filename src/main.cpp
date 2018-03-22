/*
 * main.cpp
 *
 *  Created on: Mar 22, 2018
 *      Author: gregu
 */

#include <iostream>
#include <list>

#include "Graph.h"

using namespace std;

void testDijkstraDistance()
{

	cout << "Start\n";
	Graph<int> myGraph;
	myGraph.addVertex(0); myGraph.addVertex(1); myGraph.addVertex(2); myGraph.addVertex(3); myGraph.addVertex(4);
	myGraph.addVertex(5); myGraph.addVertex(6); myGraph.addVertex(7);
	myGraph.addEdge(0, 1, 20);
	myGraph.addEdge(0, 2, 10);
	myGraph.addEdge(0, 3, 14);
	myGraph.addEdge(1, 0, 20);
	myGraph.addEdge(1, 2, 5);
	myGraph.addEdge(1, 4, 5);
	myGraph.addEdge(2, 0, 10);
	myGraph.addEdge(2, 1, 5);
	myGraph.addEdge(2, 4, 5);
	myGraph.addEdge(2, 3, 14);
	myGraph.addEdge(2, 5, 20);
	myGraph.addEdge(2, 7, 25);
	myGraph.addEdge(3, 0, 14);
	myGraph.addEdge(3, 2, 14);
	myGraph.addEdge(3, 5, 8);
	myGraph.addEdge(4, 1, 5);
	myGraph.addEdge(4, 2, 5);
	myGraph.addEdge(4, 6, 8);
	myGraph.addEdge(5, 2, 20);
	myGraph.addEdge(5, 3, 8);
	myGraph.addEdge(5, 7, 10);
	myGraph.addEdge(6, 4, 8);
	myGraph.addEdge(6, 7, 8);
	myGraph.addEdge(7, 6, 8);
	myGraph.addEdge(7, 2, 25);
	myGraph.addEdge(7, 5, 10);

	list<Vertex<int>*> path;
	cout << myGraph.dijkstraPath(1, 6, path) << endl;
	for(auto i = path.begin(); i != path.end(); i++)
	{
		cout << (*i)->getInfo() << " ";
	}
	cout << endl;



}

void testDijkstraDistancePeople()
{

	cout << "Start\n";
	Graph<int> myGraph;
	myGraph.addVertex(0); myGraph.addVertex(1); myGraph.addVertex(2); myGraph.addVertex(3); myGraph.addVertex(4);
	myGraph.addVertex(5); myGraph.addVertex(6); myGraph.addVertex(7);
	myGraph.addEdge(0, 1, 20);
	myGraph.addEdge(0, 2, 10);
	myGraph.addEdge(0, 3, 14);
	myGraph.addEdge(1, 0, 20);
	myGraph.addEdge(1, 2, 5);
	myGraph.addEdge(1, 4, 5);
	myGraph.addEdge(2, 0, 10);
	myGraph.addEdge(2, 1, 5);
	myGraph.addEdge(2, 4, 5);
	myGraph.addEdge(2, 3, 14);
	myGraph.addEdge(2, 5, 20);
	myGraph.addEdge(2, 7, 25);
	myGraph.addEdge(3, 0, 14);
	myGraph.addEdge(3, 2, 14);
	myGraph.addEdge(3, 5, 8);
	myGraph.addEdge(4, 1, 5);
	myGraph.addEdge(4, 2, 5);
	myGraph.addEdge(4, 6, 8);
	myGraph.addEdge(5, 2, 20);
	myGraph.addEdge(5, 3, 8);
	myGraph.addEdge(5, 7, 10);
	myGraph.addEdge(6, 4, 8);
	myGraph.addEdge(6, 7, 8);
	myGraph.addEdge(7, 6, 8);
	myGraph.addEdge(7, 2, 25);
	myGraph.addEdge(7, 5, 10);

	if (!myGraph.addPeople(0, 4, 2))
		cout << "ERROR" << endl;
	if (!myGraph.addPeople(0, 7, 3))
		cout << "ERROR" << endl;

	cout << myGraph.findVertex(0)->getAdjTo(2).getNumPeople() << endl;
	cout << myGraph.findVertex(0)->getAdjTo(2).getWeight() << endl;

	cout << myGraph.dijkstraPeopleDistance(0, 6) << endl;
	cout << myGraph.dijkstraPeopleDistance(0, 2) << endl;
}

int main(void)
{
	testDijkstraDistancePeople();
}




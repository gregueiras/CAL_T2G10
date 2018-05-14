#include <iostream>
#include <list>
#include <vector>

#include "Graph.h"
#include "Passenger.h"
#include "graphviewer.h"
#include "RideShare.h"
#include "menu.h"

#include <unordered_set>
#include <cstdio>
#include <fstream>
#include <sstream>

using namespace std;

void testDijkstraDistance() {

	cout << "Start\n";
	Graph<int> myGraph;
	/*myGraph.addVertex(0, 10, 10);
	myGraph.addVertex(1, 0, 20);
	myGraph.addVertex(2, 15, 5);
	myGraph.addVertex(3, 20, 5);
	myGraph.addVertex(4, 20, 25);
	myGraph.addVertex(5, 35, 12);
	myGraph.addVertex(6, 33, 17);
	myGraph.addVertex(7, 50, 12);
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
	*/

	list<Vertex<int>*> path;
	cout << myGraph.dijkstraPath(1, 6, path) << endl;
	for (auto i = path.begin(); i != path.end(); i++) {
		cout << (*i)->getInfo() << " ";
	}
	cout << endl;

}

Graph<int> create_MyGraph()
{
	Graph<int> myGraph;
	/*myGraph.addVertex(0, 10, 10);
	myGraph.addVertex(1, 0, 20);
	myGraph.addVertex(2, 15, 5);
	myGraph.addVertex(3, 20, 5);
	myGraph.addVertex(4, 20, 25);
	myGraph.addVertex(5, 35, 12);
	myGraph.addVertex(6, 33, 17);
	myGraph.addVertex(7, 50, 12);
	myGraph.addVertex(9, 100, 100);
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
	myGraph.addEdge(5, 7, 2); //10
	myGraph.addEdge(6, 4, 8);
	myGraph.addEdge(6, 7, 8);
	myGraph.addEdge(7, 6, 8);
	myGraph.addEdge(7, 2, 25);
	myGraph.addEdge(7, 5, 10);
	//myGraph.addEdge(3, 10, 4);
	//myGraph.addEdge(10, 3, 4);
	*/
	myGraph.updateGraphConnectivity();
	myGraph.printNotConnected();


	Time t(12, 12);
	Passenger<int> *p1 = new  Passenger<int>("Jay", 20, 101, 20, t);
	Passenger<int> *p0 = new Passenger<int>("John", 20, 7, 20, t);
	Passenger<int> *p2 = new Passenger<int>("Ada", 22, 2, 20, Time(12, 10));
	Passenger<int> *p3 = new Passenger<int>("Mary", 30, 1, 20, Time(12, 40));
	Passenger<int> *p5 = new Passenger<int>("Bane", 20, 17, 20, Time(12, 42));
	Passenger<int> *p6 = new Passenger<int>("Kate", 20, 3, 20, t);
	Passenger<int> *p7 = new Passenger<int>("Nina", 20, 3, 20, t);
	Passenger<int> *p8 = new Passenger<int>("Adam", 20, 19, 50, t);

	if (!myGraph.addPeople(2, 3, p1)) //101
		cout << "ERROR" << endl;
	if (!myGraph.addPeople(0, 3, p2)) //2
		cout << "ERROR" << endl;
	if (!myGraph.addPeople(3, 5, p3)) //1
		cout << "ERROR" << endl;
	if (!myGraph.addPeople(2, 3, p0)) //7
		cout << "ERROR" << endl;
	if (!myGraph.addPeople(5, 7, p5)) //6
		cout << "ERROR" << endl;
	if (!myGraph.addPeople(2, 5, p6)) //3
		cout << "ERROR" << endl;
	if (!myGraph.addPeople(0, 2, p7)) //3
		cout << "ERROR" << endl;
	if (!myGraph.addPeople(3, 7, p8)) //19
		cout << "ERROR" << endl;

	//myGraph.readGraphFromFile("myGraph");

	return myGraph;
}

Graph<int> create_MyGraphNoPassengers()
{
	Graph<int> myGraph;
	/*myGraph.addVertex(0, 50, 300);
	myGraph.addVertex(1, 50, 100);
	myGraph.addVertex(2, 150, 200);
	myGraph.addVertex(3, 290, 300);
	myGraph.addVertex(4, 250, 100);
	myGraph.addVertex(5, 370, 250);
	myGraph.addVertex(6, 370, 100);
	myGraph.addVertex(7, 450, 170);
	myGraph.addVertex(9, 550, 300);
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
	myGraph.addEdge(5, 7, 2); //10
	myGraph.addEdge(6, 4, 8);
	myGraph.addEdge(6, 7, 8);
	myGraph.addEdge(7, 6, 8);
	myGraph.addEdge(7, 2, 25);
	myGraph.addEdge(7, 5, 10);
	//myGraph.addEdge(3, 10, 4);
	//myGraph.addEdge(10, 3, 4);
	*/
//	myGraph.updateGraphConnectivity();
//	myGraph.printNotConnected();


	return myGraph;
}

bool testDijkstraPeopleDriver(Driver<int>* driver)
{
	Graph<int> myGraph = create_MyGraph();
	return myGraph.calculatePath(driver->getSource(), driver->getDestination(), driver);
}

template<class T>
void graphInit(const Graph<T> &g) {
	GraphViewer *gv = new GraphViewer(600, 600, false);

	gv->setBackground("background.jpg");

	gv->createWindow(600, 600);


	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");

	g.addGraphToViewer(gv);

	gv->rearrange();
}

int main(void) {
	bool read = true;
	RideShare<int> rs;
	if(!read) {
		unordered_set<Driver<int>> drivers;

		Driver<int> bieira = Driver<int>(0,3,20, 40, "bieira", 20, Time(12, 12));
		Driver<int> gregueiras = Driver<int>(3,7,20, 40, "gregueiras", 22, Time(12, 45));
		Driver<int> susy = Driver<int>(0,7,20, 40, "susy", 22, Time(12, 12));
		drivers.insert(bieira);
		drivers.insert(gregueiras);
		drivers.insert(susy);

		unordered_set<Passenger<int>> passengers;

		Graph<int> myGraph = create_MyGraphNoPassengers();

		Time t(12, 12);
		Passenger<int> p0 = Passenger<int>("John", 20, 7, 20, t, 2, 3);
		Passenger<int> p1 = Passenger<int>("Jay", 20, 101, 20, t, 2, 3);
		Passenger<int> p2 = Passenger<int>("Ada", 22, 2, 20, Time(12, 10), 0, 3);
		Passenger<int> p3 = Passenger<int>("Mary", 30, 1, 20, Time(12, 40), 3, 5);
		Passenger<int> p5 = Passenger<int>("Bane", 20, 17, 20, Time(12, 42), 5, 7);
		Passenger<int> p6 = Passenger<int>("Kate", 20, 3, 20, t, 2, 5);
		Passenger<int> p7 = Passenger<int>("Nina", 20, 3, 20, t, 0, 2);
		Passenger<int> p8 = Passenger<int>("Adam", 20, 19, 50, t, 3, 7);

		passengers.insert(p0);
		passengers.insert(p1);
		passengers.insert(p2);
		passengers.insert(p3);
		passengers.insert(p5);
		passengers.insert(p6);
		passengers.insert(p7);
		passengers.insert(p8);

		rs.setName("rs");
		rs.setGraph(myGraph);
		rs.setPassengers(passengers);
		rs.setDrivers(drivers);

	}
		
	cout << endl;

	FirstMenu(rs);

	getchar(); 	return 0;
}

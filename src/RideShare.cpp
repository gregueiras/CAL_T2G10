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

	this->graph.addPeople(passengers);

}

template <class T>
RideShare<T>::~RideShare()
{
	this->deletePassengers();
	this->deleteDrivers();
}

template<class T>
void RideShare<T>::addPassenger(Passenger<T>* passenger)
{
	this->passengers.insert(passenger);
	this->graph.addPassenger(passenger);

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
void RideShare<T>::setPassengers(unordered_set<Passenger<T>> passengers)
{
	if (!this->passengers.empty())
		this->graph.removePeople(vector <Passenger<T>*>(this->passengers.begin(), this->passengers.end()));

	for (auto i = this->passengers.begin(); i != this->passengers.end(); ++i) {
		this->addPassenger((*i)->clone());
	}

	this->graph.addPeople(this->passengers);
}

template<class T>
void RideShare<T>::setDrivers(unordered_set<Driver<T>> drivers)
{
	for (auto i = this->drivers.begin(); i != this->drivers.end(); ++i) {
		
		this->addDriver((*i)->clone());
	}
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
void RideShare<T>::deletePassengers()
{
	for (auto i = this->passengers.begin(); i != this->passengers.end(); ++i) {
		delete (*i);
	}
}

template<class T>
void RideShare<T>::deleteDrivers()
{
	for (auto i = this->drivers.begin(); i != this->drivers.end(); ++i) {
		delete (*i);
	}
}

template<class T>
void RideShare<T>::deleteVertices()
{
}

template<class T>
void RideShare<T>::DijkstraPeopleMultipleDrivers()
{
	if (drivers.size() == 1)
	{
		this->graph.calculateAndPrintPath((*drivers.begin())->getSource(), (*drivers.begin())->getDestination(), (*drivers.begin()), false);
		cout << endl;
		return;
	}

	multimap<T, Driver<T>*, p_less<T>> ordered_drivers;
	for (auto i = drivers.begin(); i != drivers.end(); i++)
	{
		//cout << "1. " << (*i)->getName() << endl;
		if (this->graph.calculatePath((*i)->getSource(), (*i)->getDestination(), (*i)))
			ordered_drivers.insert(pair<int, Driver<int>*>((*i)->getTransportedPassengers(), (*i)));
		//cout << endl << endl;

		this->resetPassengers();

	}
	for (auto i = ordered_drivers.begin(); i != ordered_drivers.end(); i++)
	{
		//cout << "2." << i->second->getName() << endl;
		i->second->resetValues();
		this->graph.calculateAndPrintPath(i->second->getSource(), i->second->getDestination(), i->second, true);
		//cout << endl;
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


template<class T>
void RideShare<T>::checkSelectedMapConnectivity()
{
	graph.updateGraphConnectivity();
	graph.printNotConnected();
}

template<class T>
void RideShare<T>::graphInit() {
	GraphViewer* gv = new GraphViewer(600, 600, false);

	gv->setBackground("background.jpg");

	gv->createWindow(600, 600);


	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");

	graph.addGraphToViewer(gv);

	gv->rearrange();
}

template<class T>
void RideShare<T>::SetDriverPathColour(string name, int age)
{
	GraphViewer *gv = new GraphViewer(600, 600, false);
	gv->setBackground("background.jpg");
	gv->createWindow(600, 600);
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");
	graph.addGraphToViewer(gv);

	for (auto i = this->drivers.begin(); i != this->drivers.end(); i++)
	{
		if ((*i)->getName() == name && (*i)->getAge() == age)
		{
			list<Vertex<T>*> list = (*i)->getPath();
			for (auto j = list.begin(); j != list.end(); j++) {
					gv->setVertexColor((*j)->getInfo(), "magenta");
			}
			return;
		}
	}
}


template<class T>
void RideShare<T>::SetPassengerPathColour(string name, int age)
{
	GraphViewer *gv = new GraphViewer(600, 600, false);
	gv->setBackground("background.jpg");
	gv->createWindow(600, 600);
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");
	graph.addGraphToViewer(gv);

	for (auto i = this->passengers.begin(); i != this->passengers.end(); i++)
	{
		if ((*i)->getName() == name && (*i)->getAge() == age)
		{
			list<Vertex<T>*> list = (*i)->getPath();
			for (auto j = list.begin(); j != list.end(); j++) {
					gv->setVertexColor((*j)->getInfo(), "green");
			}
			return;
		}
	}
}



template<class T>
bool RideShare<T>::PrintPassengerInfo(string name, int age)
{
	for (auto i = passengers.begin(); i != passengers.end(); i++)
	{
		if ((*i)->getName() == name && (*i)->getAge() == age)
		{
			cout <<"Passenger: " << name << endl;
			cout << "Traveling with: " << (*i)->getNum() -1 << endl;
			cout << "Route : " ;
			Utili<T>::printPath((*i)->getPath());
			return true;
		}
	}
	return false;
}

template<class T>
bool RideShare<T>::PrintDriverInfo(string name, int age)
{
	for (auto i = drivers.begin(); i != drivers.end(); i++)
	{
		if ((*i)->getName() == name && (*i)->getAge() == age)
		{
			cout <<"Driver: " << name << endl;
			cout << "Vehicle capacity: " << (*i)->getCapacity() << endl;
			cout << "Route : " ;
			(*i)->printPath();
			cout << "\nPicked:" << endl;
			(*i)->printPassengersPickedAt();
			cout << "Dropped:" << endl;
			(*i)->printPassengersDroppedAt();
			cout << endl;
			return true;
		}
	}
	return false;
}

template<class T>
void RideShare<T>::PrintAllDriversInfo()
{
	for (auto i = drivers.begin(); i != drivers.end(); i++)
	{
		cout <<"Driver: " << (*i)->getName() << endl;
		cout << "Vehicle capacity: " << (*i)->getCapacity() << endl;
		cout << "Route : " ;
		(*i)->printPath();
		cout << "\nPicked:" << endl;
		(*i)->printPassengersPickedAt();
		cout << "Dropped:" << endl;
		(*i)->printPassengersDroppedAt();
		cout << endl << endl;
	}
}

template class RideShare<int>;

#include "RideShare.h"

using namespace std;
template <class T>
RideShare<T>::RideShare(){}

template <class T>
RideShare<T>::RideShare(string n)
{
	name = n;
	this->readFromFile();
}

template <class T>
void RideShare<T>::setFromFile(string name)
{
	this->name = name;
	this->readFromFile();
}

template<class T>
RideShare<T>::RideShare(string n, unordered_set<Passenger<T>*> passengers, unordered_set<Driver<T>*> drivers, Graph<T> graph)
{
	name = n;
	this->passengers = passengers;
	this->drivers = drivers;
	this->graph = graph;
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
void RideShare<T>::addPassenger(T source, T destination, Passenger<T>* passenger)
{
	this->passengers.insert(passenger);
	this->graph.addPeople(source, destination, passenger);
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
				auto next = ++j;
				--j;
				gv->setVertexColor((*j)->getInfo(), "magenta");
				if (next == list.end())
					break;
				else
				{
					for (unsigned int k = 0; k < (*j)->getAdj().size(); k++)
					{
						if ( (*j)->getAdj().at(k).getVertexName() == to_string((*next)->getInfo()))
							gv->setEdgeColor((*j)->getAdj().at(k).getEdgeId(), "magenta");
					}
				}
			}
			gv->rearrange();
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
				auto next = ++j;
				--j;
				gv->setVertexColor((*j)->getInfo(), "green");
				if (next == list.end())
					break;
				else
				{
					for (unsigned int k = 0; k < (*j)->getAdj().size(); k++)
					{
						if ( (*j)->getAdj().at(k).getVertexName() == to_string((*next)->getInfo()))
							gv->setEdgeColor((*j)->getAdj().at(k).getEdgeId(), "green");
					}
				}
			}
			gv->rearrange();
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

template<class T>
bool RideShare<T>::writePassengersToFile() {
	bool result = true;
	string fileName = name + "Passenger.txt";
	ofstream output(fileName);
	for(auto it = this->passengers.begin(); it != this->passengers.end(); ++it) {
		result &= (*it)->writeToFile(&output);
	}
	output.close();
	return result;
}

template<class T>
bool RideShare<T>::writeDriversToFile() {
	bool result = true;
	string fileName = name + "Driver.txt";
	ofstream output(fileName);
	for(auto it = this->drivers.begin(); it != this->drivers.end(); ++it) {
		result &= (*it)->writeToFile(&output);
	}
	output.close();
	return result;
}

template<class T>
bool RideShare<T>::writeToFile() {
	return this->graph.writeToFile(name) && this->writePassengersToFile() && this->writeDriversToFile();
}

template<class T>
bool RideShare<T>::readPassengersFromFile() {
	unordered_set <Passenger<T>> passengers;
	string fileName = name + "Passenger.txt";
	ifstream input;
	istringstream lineStream;
	input.open(fileName);
	if (input.is_open()) {
		while(!input.eof()) {
			string line, name;
			int age, num, tl, h, m;
			T source, destination;
			getline(input, name);
			if(name.empty())
				break;
			getline(input, line);
			lineStream.clear();
			lineStream.str(line);
			lineStream >> age;
			lineStream >> num;
			lineStream >> tl;
			lineStream >> h;
			lineStream >> m;
			getline(input, line);
			lineStream.clear();
			lineStream.str(line);
			lineStream >> source;
			lineStream >> destination;
			Passenger<T> p = Passenger<T>(name, age, num, tl, Time(h,m), source, destination);
			/*cout << "Passenger read: *" << name << "* " << age << " " << num << " " << tl << " " << h << " " << m << " " <<
					source << " " << destination << endl;*/
			/*this->addPassenger(source, destination, p);*/
			passengers.insert(p);

		}
	} else
		return false;
	input.close();
	this->setPassengers(passengers);
	return true;
}

template<class T>
bool RideShare<T>::readDriversFromFile() {
	unordered_set <Driver<T>> drivers;
	string fileName = name + "Driver.txt";
	ifstream input;
	istringstream lineStream;
	input.open(fileName);
	if (input.is_open()) {
		while(!input.eof()) {
			string line, name;
			int age, cap, tl, h, m;
			T source, destination;
			getline(input, name);
			if(name.empty())
				break;
			getline(input, line);
			lineStream.clear();
			lineStream.str(line);
			lineStream >> age;
			lineStream >> cap;
			lineStream >> tl;
			lineStream >> h;
			lineStream >> m;
			getline(input, line);
			lineStream.clear();
			lineStream.str(line);
			lineStream >> source;
			lineStream >> destination;
			Driver<T> d = Driver<T>(source, destination, cap, tl, name, age, Time(h, m));
			/*cout << "Driver read: *" << name << "* " << age << " " << cap << " " << tl << " " << h << " " << m << " " <<
					source << " " << destination << endl;*/
			//this->addDriver(d);
			drivers.insert(d);
		}
	} else
		return false;
	input.close();
	this->setDrivers(drivers);
	return true;
}

template<class T>
bool RideShare<T>::readFromFile() {
	return this->graph.readFromFile(name) && this->readPassengersFromFile() && this->readDriversFromFile();
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
void RideShare<T>::setPassengers(unordered_set<Passenger<T>> passengers)
{
	if (!this->passengers.empty())
		this->graph.removePeople(vector <Passenger<T>*>(this->passengers.begin(), this->passengers.end()));
	
	for (auto i = passengers.begin(); i != passengers.end(); ++i) {
		this->addPassenger((*i).clone());

	}
	
//this->graph.addPeople(this->passengers);
	
}

template<class T>
void RideShare<T>::setDrivers(unordered_set<Driver<T>> drivers)
{
	for (auto i = drivers.begin(); i != drivers.end(); ++i) {

		this->addDriver((*i).clone());

	}
}

template<class T>
void RideShare<T>::setName(std::string name) {
	this->name = name;
}
template class RideShare<int>;

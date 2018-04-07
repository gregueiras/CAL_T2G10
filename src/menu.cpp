
#include "menu.h"
using namespace std;

void cleanfunction()
{
	cin.ignore();
	cin.clear();
}

int getIntInInterval(int lower, int upper)
{
	int num;
	bool validInput;
	do
	{
		validInput = true;
		cin >> num;
		if (cin.fail())
		{
			validInput = false;

			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Invalid Input!" << endl;

		}
		else if (!(num <= upper && num >= lower))
		{
			validInput = false;
			cout << "Invalid Choice!" << endl;
		}
	} while (!validInput);

	return num;
}

int getInt()
{
	int num;
	cin >> num;

	if (cin.fail() || num < 0)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Invalid Input!\n";
		return -1;
	}
	return num;
}

double getDouble()
{
	double num;
	cin >> num;

	if (cin.fail() || num < 0)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Invalid Input!\n";
		return -1;
	}
	return num;
}

string getFileName()
{
	string filename;
	cin >> filename;
	if (filename.size() <= 3)
	{
		filename += ".txt";
	}
	else if (filename.substr(filename.size() - 4, 4).compare(".txt") != 0)
		filename += ".txt";

	return filename;
}

void FirstMenu(RideShare<int> &rideShare)
{
	bool endInput = false;
	cout << "Welcome" << endl;

	do
	{
		cout
		<< "1- Driver sign up" << endl
		<< "2- Passenger sign up" << endl
		<< "3- View graph" << endl
		<< "4- Quit" << endl
		<< "Select one" << endl;
		switch (getIntInInterval(1, 4))
		{
		case 1:
			DriverSignUpMenu(rideShare);
			break;
		case 2:
			PassengerSignUpMenu(rideShare);
			break;
		case 3:
			//DISPLAY GRAPH
			break;
		case 4:
			endInput = true;
			break;
		}
	} while(!endInput);
}



void DriverSignUpMenu(RideShare<int> &rideShare)
{
	string name;
	int age;
	int timeLimit;
	int capacity;
	int src, dest;
	int hour, minutes;
	cleanfunction();
	cout << "Name? (first and last) " << endl;
	getline(cin, name);
	cout << "Age? " << endl;
	age = getIntInInterval(18,70);
	cout << "Starting location? " << endl;
	src = getInt();
	if (src == -1) return;
	cout << "Destination? " << endl;
	dest = getInt();
	if (dest == -1) return;
	cout << "Starting hour: " << endl;
	cout << "Hour?  ";
	hour = getIntInInterval(0,23);
	cout << "Minutes?  ";
	minutes = getIntInInterval(0,59);
	cout << "Time limit for the itinerary?" << endl;
	timeLimit = getInt();
	if (timeLimit == -1) return;
	cout << "Vehicle capacity? " << endl;
	capacity = getInt();
	if (capacity == -1) return;
	Driver<int> *driver = new Driver<int>(src,dest,capacity,timeLimit,name,age,Time(hour,minutes));
	rideShare.addDriver(driver);
	cout << "Calculating route..." << endl;
	rideShare.DijkstraPeopleMultipleDrivers();
	DriverRouteOptionsMenu(driver);
}



void PassengerSignUpMenu(RideShare<int> &rideShare)
{
	string name;
	int age;
	int timeLimit;
	int numberPeople;
	int src, dest;
	int hour, minutes;
	cleanfunction();
	cout << "Name? (first and last) " << endl;
	getline(cin, name);
	cout << "Age? " << endl;
	age = getIntInInterval(18,70);
	cout << "Starting location? " << endl;
	src = getInt();
	if (src == -1) return;
	cout << "Destination? " << endl;
	dest = getInt();
	if (dest == -1) return;
	cout << "Starting hour: " << endl;
	cout << "Hour?  ";
	hour = getIntInInterval(0,23);
	cout << "Minutes?  ";
	minutes = getIntInInterval(0,59);
	cout << "Time limit for the itinerary?" << endl;
	timeLimit = getInt();
	if (timeLimit == -1) return;
	cout << "Number of people traveling? " << endl;
	numberPeople = getInt();
	if (numberPeople == -1) return;
	Passenger<int> *passenger = new Passenger<int>(name,age,numberPeople, timeLimit,Time(hour,minutes),src,dest);
	rideShare.addPassenger(passenger);
	cout << "Calculating route..." << endl;
	rideShare.DijkstraPeopleMultipleDrivers();
	PassengerRouteOptionsMenu(passenger);
}

void DriverRouteOptionsMenu(Driver<int> *driver)
{
	cout
	<< "1- Print route information" << endl
	<< "2- View route "	<< endl
	<< "3- Print passenger list" << endl
	<< "4- Go back" << endl
	<< "Select one" << endl;

	switch(getIntInInterval(1,4))
	{
	case 1:
		//FUNCTION THAT PRINTS THE ROUTE INFORMATION
		break;
	case 2:
		//FUNCTION THAT DISPLAYS THE ROUTE
		break;
	case 3:
		//FUNCTION THAT PRINTS PASSANGER LIST
		break;
	case 4:
		return;
		break;
	}
}

void PassengerRouteOptionsMenu(Passenger<int> *passenger)
{
	cout
	<< "1- Print route information" << endl
	<< "2- View route "	<< endl
	<< "3- Go back" << endl
	<< "Select one" << endl;

	switch(getIntInInterval(1,3))
	{
	case 1:
		//FUNCTION THAT PRINTS THE ROUTE INFORMATION
		break;
	case 2:
		//FUNCTION THAT DISPLAYS THE ROUTE
		break;
	case 3:
		return;
		break;
	}
}



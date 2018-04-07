
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
		<< "1- Driver options" << endl
		<< "2- Passenger options" << endl
		<< "3- Quit" << endl
		<< "Select one" << endl;
		switch (getIntInInterval(1, 3))
		{
		case 1:
			DriverOptionsMenu(rideShare);
			break;
		case 2:
			PassengerOptionsMenu(rideShare);
			break;
		case 3:
			endInput = true;
			break;
		}
	} while(!endInput);
}

void DriverOptionsMenu(RideShare<int> &rideShare)
{
	cout
		<< "1- Sign in " << endl
		<< "2- Sign up " << endl
		<< "3- Go back" << endl
		<< "Select one" << endl;

		switch(getIntInInterval(1,3))
		{
		case 1:
			DriverSignInMenu(rideShare);
			break;
		case 2:
			DriverSignUpMenu(rideShare);
			break;
		case 3:
			return FirstMenu(rideShare);
			break;
		}
}

void PassengerOptionsMenu(RideShare<int> &rideShare)
{

	cout
		<< "1- Sign in " << endl
		<< "2- Sign up " << endl
		<< "3- Go back" << endl
		<< "Select one" << endl;

		switch(getIntInInterval(1,3))
		{
		case 1:
			PassengerSignInMenu(rideShare);
			break;
		case 2:
			PassengerSignUpMenu(rideShare);
			break;
		case 3:
			return FirstMenu(rideShare);
			break;
		}
}



#include <string>
#include <iostream>
#include <vector>
#include "RideShare.h"

void cleanfunction();

int getIntInInterval(int lower, int upper);

int getInt();

double getDouble();

string getFileName();

void FirstMenu(RideShare<int> &rideShare);

void DriverSignUpMenu(RideShare<int> &rideShare);

void PassengerSignUpMenu(RideShare<int> &rideShare);

void DriverRouteOptionsMenu(Driver<int> *driver);

void PassengerRouteOptionsMenu(Passenger<int> *passenger);

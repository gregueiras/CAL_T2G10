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

void SelectMapMenu(RideShare<int> &rideShare);

void AddVertexMenu(RideShare<int> &rideShare);

void AddEdgeMenu(RideShare<int> &rideShare);

void AddPassengerMenu(RideShare<int> &rideShare);

void AddDriverMenu(RideShare<int> &rideShare);

void DriverSignUpMenu(RideShare<int> &rideShare);

void PassengerSignUpMenu(RideShare<int> &rideShare);

void GenerateRoutesMenu(RideShare<int> &rideShare);

void AddVertexSubMenu(RideShare<int> &rideShare);

void AddEdgeSubMenu(RideShare<int> &rideShare);

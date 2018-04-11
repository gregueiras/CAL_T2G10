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
#include <chrono>

using namespace std; //usada apenas para fins estatísticos
//int main() {
//	
//	ofstream myfile;
//	myfile.open("Stats.txt");
//
//	vector<double> times3;
//	vector<double> times10;
//	vector<double> times20;
//
//	for (auto i = 0; i < 500; i++) {
//		RideShare<int> rideShare;
//		rideShare.setFromFile("10x10");
//
//		auto start = std::chrono::high_resolution_clock::now();
//		rideShare.DijkstraPeopleMultipleDrivers();
//		auto finish = std::chrono::high_resolution_clock::now();
//		std::chrono::duration<double> elapsed = finish - start;
//
//		times10.push_back(elapsed.count());
//	}
//	
//	for (auto i = 0; i < 500; i++) {
//		RideShare<int> rideShare;
//		rideShare.setFromFile("rs");
//
//		auto start = std::chrono::high_resolution_clock::now();
//		rideShare.DijkstraPeopleMultipleDrivers();
//		auto finish = std::chrono::high_resolution_clock::now();
//		std::chrono::duration<double> elapsed = finish - start;
//
//		times3.push_back(elapsed.count());
//	}
//
//	myfile << "3x3,10x10" << endl;
//	for (auto i = 0; i < 5000; i++) {
//		myfile << times3[i] << "," << times10[i] << endl;
//	}
//	myfile.close();
//	return 0;
//}

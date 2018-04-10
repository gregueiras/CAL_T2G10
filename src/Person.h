/*
 * Person.h
 */

#ifndef PERSON_H_
#define PERSON_H_

#include <string>
#include "Time.h"
#include "exceptions.h"
using namespace std;

class Person { //Shouldn't be abstract??
	string name;
	int age;
	Time startTime;
	Time currentTime;
	int timeLimit;
public:
	Person();
	Person (string n, int a);
	Person (string n, int a, int tl, Time st);
	string getName() const;
	int getAge() const;
	Time getStartTime() const;
	Time getCurrentTime() const;
	void setCurrentTime(Time cT);
	void updateCurrentTime(int minutes);
	bool operator== (const Person &p2) const;
	bool operator< (const Person &p2) const;
	int getTimeLimit() const;
	void setTimeLimit(int timeLimit);
	//virtual bool writeToFile(string file);
	friend ostream & operator << (ostream &os, Person &p);
};

#endif /* NETWORK_H_ */

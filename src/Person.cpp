/*
 * Person.cpp
 */

#include "Person.h"


Person::Person(string n, int a): name(n) {
	startTime = Time(0,0);
	timeLimit = 0;
	if (a < 18 || a > 70)
		throw InvalidAgeException();
	else
		age = a;
}

Person::Person(){
	timeLimit = 0;
	age = 0;
}

Person::Person(string n, int a, int tl, Time st): name(n), startTime(st), currentTime(st){
	if (tl <= 0)
		throw InvalidTimeLimitException();
	else
		timeLimit = tl;
	if (a < 18 || a > 70)
		throw InvalidAgeException();
	else
		age = a;
}

string Person::getName() const {
	return name;
}

int Person::getAge() const
{
	return this->age;
}

Time Person::getStartTime() const {
	return startTime;
}

Time Person::getCurrentTime() const {
	return currentTime;
}

void Person::setCurrentTime(Time cT)
{
	this->currentTime = cT;
}

void Person::updateCurrentTime(int minutes)
{
	currentTime = startTime + Time(0,minutes);
}


int Person::getTimeLimit() const {
	return timeLimit;
}

void Person::setTimeLimit(int timeLimit) {
	this->timeLimit = timeLimit;
}

bool Person::operator== (const Person &p2) const {
	return (name==p2.name && age==p2.age);
}

bool Person::operator<(const Person & p2) const
{
	return this->name < p2.name;
}

ostream & operator << (ostream &os, Person &p) {
   os << p.getName();
   return os;
}

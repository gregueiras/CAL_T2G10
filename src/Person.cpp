/*
 * Person.cpp
 */

#include "Person.h"

Person::Person(string n, int a): name(n), age(a) {}
Person::Person(){}
Person::Person(string n, int a, Time st): name(n), age(a), startTime(st), currentTime(st){}

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

void Person::updateCurrentTime(int minutes)
{
	currentTime = startTime + Time(0,minutes);
}

bool Person::operator == (const Person &p2) const {
	return (name==p2.name && age==p2.age);
}

ostream & operator << (ostream &os, Person &p) {
   os << p.getName();
   return os;
}

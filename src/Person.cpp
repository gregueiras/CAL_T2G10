/*
 * Person.cpp
 */

#include "Person.h"

Person::Person(string n, int a, int t): name(n), age(a), timeLimit(t) {}
Person::Person(){}
Person:: Person(int timeLimit) : name(" "), age(0), timeLimit(timeLimit){}

string Person::getName() const {
	return name;
}

int Person::getTimeLimit() const {
	return timeLimit;
}


bool Person::operator == (const Person &p2) const {
	return (name==p2.name && age==p2.age);
}

ostream & operator << (ostream &os, Person &p) {
   os << p.getName();
   return os;
}

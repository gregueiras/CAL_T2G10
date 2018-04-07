/*
 * Time.cpp
 *
 *  Created on: Mar 25, 2018
 *      Author: gregu
 */

#include "Time.h"
#include <cmath>

Time::Time() {
	this->hour = -1;
	this->minute = -1;
}

Time::Time(int hour, int minute) {
	this->hour = (hour + (minute / 60)) % 24;
	this->minute = minute % 60;
}

int Time::getHour() const {
	return hour;
}

void Time::setHour(int hour) {
	this->hour = hour;
}

int Time::getMinute() const {
	return minute;
}

void Time::setMinute(int minute) {
	this->minute = minute;
}

void Time::addMinutes(int minutes)
{
	hour = (hour + (minute + minutes)/ 60) % 24;
	minute = (minute + minutes) % 60;
}

Time::~Time() {
	// TODO Auto-generated destructor stub
}


Time operator+(Time lhs, const Time& rhs) {
	return Time(lhs.getHour() + rhs.getHour(),
			lhs.getMinute() + rhs.getMinute());
}

bool operator<(const Time& lhs, const Time& rhs) {
	if (lhs.getHour() == rhs.getHour())
		return (lhs.getMinute() < rhs.getMinute());
	else
		return (lhs.getHour() < rhs.getHour());
}

bool operator==(const Time& lhs, const Time& rhs) {
	return (lhs.getHour() == rhs.getHour() && lhs.getMinute() == rhs.getMinute());
}


Time operator+(Time lhs, const int& rhs) {
	return Time(lhs.getHour(), lhs.getMinute() + rhs);
}



bool operator!=(const Time& lhs, const Time& rhs)
{
	return !operator==(lhs, rhs);
}

bool operator> (const Time& lhs, const Time& rhs)
{
	return  operator< (rhs, lhs);
}
bool operator<=(const Time& lhs, const Time& rhs)
{
	return !operator> (lhs, rhs);
}
bool operator>=(const Time& lhs, const Time& rhs)
{
	return !operator< (lhs, rhs);
}

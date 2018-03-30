/*
 * Time.cpp
 *
 *  Created on: Mar 25, 2018
 *      Author: gregu
 */

#include "Time.h"

Time::Time() {
	// TODO Auto-generated constructor stub

}

Time::Time(int hour, int minute) {
	this->hour = (hour + (minute / 60)) % 24;
	this->minute = minute % 24;
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

Time::~Time() {
	// TODO Auto-generated destructor stub
}

inline Time operator+(Time lhs, const Time& rhs) {
	return Time(lhs.getHour() + rhs.getHour(),
			lhs.getMinute() + rhs.getMinute());
}

inline bool operator<(const Time& lhs, const Time& rhs) {
	if (lhs.getHour() == rhs.getHour())
		return (lhs.getMinute() < rhs.getMinute());
	else
		return (lhs.getHour() < rhs.getHour());
}

inline bool operator==(const Time& lhs, const Time& rhs) {
	return (lhs.getHour() == rhs.getHour() && lhs.getHour() == rhs.getHour());
}


inline Time operator+(Time lhs, const int& rhs) {
	return Time(lhs.getHour(), lhs.getMinute() + rhs);
}


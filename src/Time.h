/*
 * Time.h
 *
 *  Created on: Mar 25, 2018
 *      Author: gregu
 */

#ifndef SRC_TIME_H_
#define SRC_TIME_H_

class Time {
	int hour;
	int minute;
public:
	Time();
	Time(int hour, int minute);
	virtual ~Time();
	int getHour() const;
	void setHour(int hour);
	int getMinute() const;
	void setMinute(int minute);
};

Time operator+(Time lhs, const int& rhs);
Time operator+(Time lhs, const Time& rhs);
bool operator==(const Time& lhs, const Time& rhs);
bool operator!=(const Time& lhs, const Time& rhs){return !operator==(lhs,rhs);}
bool operator< (const Time& lhs, const Time& rhs);
bool operator> (const Time& lhs, const Time& rhs){return  operator< (rhs,lhs);}
bool operator<=(const Time& lhs, const Time& rhs){return !operator> (lhs,rhs);}
bool operator>=(const Time& lhs, const Time& rhs){return !operator< (lhs,rhs);}

#endif /* SRC_TIME_H_ */

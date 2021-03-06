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
	void addMinutes(int minutes);
};

Time operator+(Time lhs, const int& rhs);
Time operator+(Time lhs, const Time& rhs);
bool operator==(const Time& lhs, const Time& rhs);
bool operator!=(const Time& lhs, const Time& rhs);
bool operator< (const Time& lhs, const Time& rhs);
bool operator> (const Time& lhs, const Time& rhs);
bool operator<=(const Time& lhs, const Time& rhs);
bool operator>=(const Time& lhs, const Time& rhs);

#endif /* SRC_TIME_H_ */

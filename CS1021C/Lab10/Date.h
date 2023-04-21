#ifndef DATE_HPP
#define DATE_HPP

#include <iostream>

class Date {
public:
	int getDay();
	int getMonth();
	int getYear();
	void setDay(int newDay);
	void setMonth(int newMonth);
	void setYear(int newYear);
	friend std::ostream& operator<<(std::ostream& os, const Date& dt);
	Date();
private:
	int year;
	int month;
	int day;
};

#endif

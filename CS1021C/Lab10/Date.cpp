#include "Date.h"
#include <iostream>

Date::Date() : year(0), month(0), day(0) {}

int Date::getDay() { return day; }
int Date::getMonth() { return month; }
int Date::getYear() { return year; }

void Date::setDay(int newDay) {
	day = newDay;
}
void Date::setMonth(int newMonth) {
	month = newMonth;
}
void Date::setYear(int newYear) {
	year = newYear;
}

std::ostream& operator<<(std::ostream& os, const Date& dt)
{
	os << dt.year << "-" << dt.month << "-" << dt.day;
	return os;
}
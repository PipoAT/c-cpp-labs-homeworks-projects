#include "LocationDateLength.h"
#include "Date.h"
#include "Location.h"


Date LocationDateLength::getDate() { return dt; }
Location LocationDateLength::getLocation() { return lc; }
int LocationDateLength::getLength() { return length; }

void LocationDateLength::setLength(int newLength) {
	length = newLength;
}

int LocationDateLength::operator-(LocationDateLength daylength_a) {
	return length - daylength_a.getLength();
}

LocationDateLength::LocationDateLength() :dt(), lc() {}

LocationDateLength::LocationDateLength(Date newDT, Location newLC) : dt(newDT), lc(newLC) {}
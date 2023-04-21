#include "Location.h"

Location::Location() :latitude(0), longitude(0) {}

double Location::getLatitude() { return latitude; }
double Location::getLongitude() { return longitude; }

void Location::setLatitude(double newLatitude) {
	latitude = newLatitude;
}
void Location::setLongitude(double newLongitude) {
	longitude = newLongitude;
}

#ifndef LOCATIONDATELENGTH_H
#define LOCATIONDATELENGTH_H

#include "Date.h"
#include "Location.h"



class LocationDateLength {
public:
	Date getDate();
	Location getLocation();
	int getLength();
	void setLength(int newLength);
	int operator-(LocationDateLength daylength_a);
	LocationDateLength();
	LocationDateLength(Date newDT, Location newLC);
private:
	Date dt;
	Location lc;
	int length;
};
#endif
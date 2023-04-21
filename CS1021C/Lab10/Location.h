#ifndef LOCATION_CPP
#define LOCATION_CPP

class Location {
public:
	double getLatitude();
	double getLongitude();
	void setLatitude(double newLatitude);
	void setLongitude(double newLongitude);
	Location();
private:
	double latitude;
	double longitude;
};

#endif

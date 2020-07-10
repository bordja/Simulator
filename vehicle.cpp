#include "vehicle.h"

Vehicle::Vehicle()
{
    this->location = Point(0,0,SpatialReference::wgs84());
    this->id = -1;
}

Vehicle::Vehicle(double y, double x, int id){
    this->location = Point(y,x,SpatialReference::wgs84());
    this->id = id;
}

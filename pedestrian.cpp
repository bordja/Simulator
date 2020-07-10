#include "pedestrian.h"

Pedestrian::Pedestrian()
{
    this->location = Point(0,0, SpatialReference::wgs84());
    this->id = 0;
}

Pedestrian::Pedestrian(double y, double x, int id){
    this->location = Point(y,x, SpatialReference::wgs84());
    this->id = id;
}

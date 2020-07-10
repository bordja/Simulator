#include "pole.h"

Pole::Pole(){
    this->location = Point(0,0,SpatialReference::wgs84());
    this->id = -1;
}
Pole::Pole(double y, double x, int id)
{
    this->location = Point(y,x,SpatialReference::wgs84());
    this->id = id;
}

#ifndef PEDESTRIAN_H
#define PEDESTRIAN_H

#include "mapobject.h"
class Pedestrian : public MapObject
{
public:
    Pedestrian();
    Pedestrian(double y, double x, int id);
};

#endif // PEDESTRIAN_H

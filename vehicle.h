#ifndef VEHICLE_H
#define VEHICLE_H

#include "mapobject.h"

using namespace Esri::ArcGISRuntime;
class Vehicle : public MapObject
{
public:
    Vehicle();
    Vehicle(double y, double x, int id);
};

#endif // VEHICLE_H

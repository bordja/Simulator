#ifndef VEHICLE_H
#define VEHICLE_H

#include "mapobject.h"

using namespace Esri::ArcGISRuntime;
class Vehicle : public MapObject
{
public:
    Vehicle();
    Vehicle(double x, double y, int id);
    SimpleMarkerSymbol *getPoint_symbol() const;
    void setPoint_symbol(SimpleMarkerSymbol *value);

private:
    SimpleMarkerSymbol* point_symbol;
};

#endif // VEHICLE_H

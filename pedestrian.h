#ifndef PEDESTRIAN_H
#define PEDESTRIAN_H

#include "mapobject.h"
using namespace Esri::ArcGISRuntime;
class Pedestrian : public MapObject
{
public:
    Pedestrian();
    Pedestrian(double y, double x, int id);
    SimpleMarkerSymbol *getPoint_symbol() const;
    void setPoint_symbol(SimpleMarkerSymbol *value);

private:
    SimpleMarkerSymbol* point_symbol;
};

#endif // PEDESTRIAN_H

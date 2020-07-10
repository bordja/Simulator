#ifndef MAPOBJECT_H
#define MAPOBJECT_H

#include "Point.h"
using namespace Esri::ArcGISRuntime;
class MapObject
{
public:
    Point getLocation();
    int getId();
protected:
    Point location;
    int id;
};

#endif // MAPOBJECT_H

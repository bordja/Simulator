#ifndef POLE_H
#define POLE_H
#include "mapobject.h"
using namespace Esri::ArcGISRuntime;
class Pole : public MapObject
{
public:
    Pole();
    Pole(double y,double x, int id);
};

#endif // POLE_H

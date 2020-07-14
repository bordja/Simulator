#ifndef POLE_H
#define POLE_H
#include "mapobject.h"
#define POLE_NUM 32

using namespace Esri::ArcGISRuntime;
class Pole : public MapObject
{
public:
    Pole();
    Pole(double y,double x, int id);
    //Pole(Pole& p);
    SimpleMarkerSymbol *getPoint_symbol() const;
    void setPoint_symbol(SimpleMarkerSymbol *value);

private:
    SimpleMarkerSymbol* point_symbol;
};
extern QList <Pole*> poles;
#endif // POLE_H

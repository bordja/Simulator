#include "mapobject.h"

Point MapObject::getLocation(){
    return this->location;
}
int MapObject::getId(){
    return this->id;
}

void MapObject::setGraphicPoint(SimpleMarkerSymbol* symbol)
{
    this->graphicPoint = new Graphic(this->location,symbol,this);
}

void MapObject::setId(int id)
{
    this->id = id;
}

Graphic* MapObject::getGraphicPoint()
{
    return this->graphicPoint;
}

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

bool MapObject::getInReferenceRegion() const
{
    return inReferenceRegion;
}

void MapObject::setInReferenceRegion(bool value)
{
    inReferenceRegion = value;
}

unsigned int MapObject::getXPixPosition() const
{
    return xPixPosition;
}

void MapObject::setXPixPosition(unsigned int value)
{
    xPixPosition = value;
}

unsigned int MapObject::getYPixPosition() const
{
    return yPixPosition;
}

void MapObject::setYPixPosition(unsigned int value)
{
    yPixPosition = value;
}

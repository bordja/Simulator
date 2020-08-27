#include "vehicle.h"

Vehicle::Vehicle()
{
    this->location = Point(0,0,SpatialReference::wgs84());
    this->id = -1;
    this->point_symbol = new SimpleMarkerSymbol(SimpleMarkerSymbolStyle::Circle, QColor(Qt::green), 7, this);
    this->inReferenceRegion = false;
    this->xPixPosition = 0;
    this->yPixPosition = 0;
}

Vehicle::Vehicle(double x, double y, int id){
    this->location = Point(x,y,SpatialReference::wgs84());
    this->id = id;
    this->point_symbol = new SimpleMarkerSymbol(SimpleMarkerSymbolStyle::Circle, QColor(Qt::green), 7, this);
    this->setGraphicPoint(this->point_symbol);
    this->inReferenceRegion = false;
    this->xPixPosition = 0;
    this->yPixPosition = 0;
}

SimpleMarkerSymbol *Vehicle::getPoint_symbol() const
{
    return point_symbol;
}

void Vehicle::setPoint_symbol(SimpleMarkerSymbol *value)
{
    point_symbol = value;
}

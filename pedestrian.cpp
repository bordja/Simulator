#include "pedestrian.h"

Pedestrian::Pedestrian()
{
    this->location = Point(0,0, SpatialReference::wgs84());
    this->id = 0;
    this->point_symbol = new SimpleMarkerSymbol(SimpleMarkerSymbolStyle::Circle, QColor(Qt::red), 7, this);
}

Pedestrian::Pedestrian(double x, double y, int id){
    this->location = Point(x,y, SpatialReference::wgs84());
    this->id = id;
    this->point_symbol = new SimpleMarkerSymbol(SimpleMarkerSymbolStyle::Circle, QColor(Qt::red), 7, this);
    this->setGraphicPoint(this->point_symbol);
}

SimpleMarkerSymbol *Pedestrian::getPoint_symbol() const
{
    return point_symbol;
}

void Pedestrian::setPoint_symbol(SimpleMarkerSymbol *value)
{
    point_symbol = value;
}

#include "pole.h"
QList <Pole*> poles;

Pole::Pole(){
    this->location = Point(0,0,SpatialReference::wgs84());
    this->id = -1;
    this->point_symbol = new SimpleMarkerSymbol(SimpleMarkerSymbolStyle::Diamond, QColor(Qt::yellow), 10, this);
}
Pole::Pole(double y, double x, int id)
{
    this->location = Point(y,x,SpatialReference::wgs84());
    this->id = id;
    this->point_symbol = new SimpleMarkerSymbol(SimpleMarkerSymbolStyle::Diamond, QColor(Qt::yellow), 10, this);
    this->setGraphicPoint(this->point_symbol);
}

SimpleMarkerSymbol *Pole::getPoint_symbol() const
{
    return point_symbol;
}

void Pole::setPoint_symbol(SimpleMarkerSymbol *value)
{
    point_symbol = value;
}

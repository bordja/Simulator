#ifndef MAPOBJECT_H
#define MAPOBJECT_H

#include "Point.h"
#include "GraphicsOverlay.h"
#include "SimpleMarkerSymbol.h"
using namespace Esri::ArcGISRuntime;
class MapObject: public QObject
{
    Q_OBJECT
public:
    Point getLocation();
    int getId();
    void setGraphicPoint(SimpleMarkerSymbol*);
    void setId(int id);
    Graphic *getGraphicPoint();

protected:
    Point location;
    Graphic* graphicPoint;
    int id;
};

#endif // MAPOBJECT_H

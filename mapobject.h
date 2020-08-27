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

    bool getInReferenceRegion() const;
    void setInReferenceRegion(bool value);

    unsigned int getXPixPosition() const;
    void setXPixPosition(unsigned int value);

    unsigned int getYPixPosition() const;
    void setYPixPosition(unsigned int value);

protected:
    Point location;
    unsigned int xPixPosition;
    unsigned int yPixPosition;
    Graphic* graphicPoint;
    int id;
    bool inReferenceRegion;
};

#endif // MAPOBJECT_H

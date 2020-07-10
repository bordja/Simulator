#ifndef POLEARRAY_H
#define POLEARRAY_H

#include "pole.h"
#include "GraphicsOverlay.h"
#include "SimpleMarkerSymbol.h"
#define POLE_NUM 32
using namespace Esri::ArcGISRuntime;
class PoleArray : public QObject
{
    Q_OBJECT
public:
    PoleArray();
    Graphic** getGraphicPoints();
    int getArraySize();
signals:
    void polesCreated(Graphic** graphicPoints, int size);
private:
    Pole poles[POLE_NUM];
    Graphic* graphicPoints [POLE_NUM];
    SimpleMarkerSymbol* point_symbol;
};

#endif // POLEARRAY_H

#ifndef FRAMEDATA_H
#define FRAMEDATA_H

#define MAX_PEDESTRIAN 50
#define MAX_VEHICLE 100
#define FRAME_SIZE 612

#include<QtGlobal>
#include "GraphicsOverlay.h"
#include "SimpleMarkerSymbol.h"
#include "vehicle.h"
#include "pedestrian.h"
using namespace Esri::ArcGISRuntime;
class FrameData
{
public:
    FrameData();
    void setTimestamp(quint64 timestamp);
    void setPedestrianNum(quint16 numPedestrian);
    void setVehicleNum(quint16 numVehicle);
    void incrementCurrentFrame();
    void setNumberOfFrames(quint16);
    quint16 getCurrentFrameNum();
    quint16 getNumberOfFrames();
    void printFrameData();
    quint16 getNumPedestrian() const;
    quint16 getNumVehicle() const;
    void appendVehicle(Vehicle* v);
    void appendPedestrian(Pedestrian* p);

    QList <Vehicle*> vehicles;
    QList <Pedestrian*> pedestrians;
private:
    quint64 timestamp;
    quint16 numPedestrian;
    quint16 numVehicle;
    quint16 currentFrame;
    quint16 numberOfFrames;
};

#endif // FRAMEDATA_H

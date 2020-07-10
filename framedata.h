#ifndef FRAMEDATA_H
#define FRAMEDATA_H

#define MAX_PEDESTRIAN 50
#define MAX_VEHICLE 100

#include<QtGlobal>
#define FRAME_SIZE 612
class FrameData
{
public:
    FrameData();
    void setTimestamp(quint64 timestamp);
    void setPedestrianNum(quint16 numPedestrian);
    void setVehicleNum(quint16 numVehicle);
    void setPedestrianRel(quint16* pedestrianRel);
    void setVehicleRel(quint16* vehicleRel);
    void incrementCurrentFrame();
    void setNumberOfFrames(quint16);
    quint16 getCurrentFrameNum();
    quint16 getNumberOfFrames();
    void printFrameData();
private:
    quint64 timestamp;
    quint16 numPedestrian;
    quint16 numVehicle;
    quint16 pedestrianRel[2 * MAX_PEDESTRIAN];
    quint16 vehicleRel[2 * MAX_VEHICLE];
    quint16 currentFrame;
    quint16 numberOfFrames;

};

#endif // FRAMEDATA_H

#include "framedata.h"
#include "collector.h"
#include <QDebug>
FrameData::FrameData()
{
    this->currentFrame = 0;
    pedestrians = new QList<Pedestrian*>;
    vehicles = new QList<Vehicle*>;
}

void FrameData::setTimestamp(quint64 timestamp){
    this->timestamp = timestamp;
}

void FrameData::setPedestrianNum(quint16 numPedestrian){
    this->numPedestrian = numPedestrian;
}

void FrameData::setVehicleNum(quint16 numVehicle){
    this->numVehicle = numVehicle;
}

void FrameData::printFrameData(){
    qDebug()<<"-------- FRAME"<<this->getCurrentFrameNum()<<"---------";
    qDebug()<<"Timestamp:\t\t"<<this->timestamp;
    qDebug()<<"Pedestrian number:\t"<<this->numPedestrian;
    qDebug()<<"Veicle number:\t"<<this->numVehicle;
    qDebug()<<"-------------------------------";
}

quint16 FrameData::getNumPedestrian() const
{
    return numPedestrian;
}

quint16 FrameData::getNumVehicle() const
{
    return numVehicle;
}

void FrameData::appendVehicle(Vehicle* v)
{
    this->vehicles->append(v);
}

void FrameData::appendPedestrian(Pedestrian *p)
{
    this->pedestrians->append(p);
}

quint64 FrameData::getTimestamp() const
{
    return timestamp;
}

void FrameData::incrementCurrentFrame(){
    this->currentFrame++;
}

void FrameData::setCurrentFrameToZero()
{
    this->currentFrame = 0;
}

quint16 FrameData::getCurrentFrameNum(){
    return this->currentFrame;
}

void FrameData::setNumberOfFrames(quint16 num){
    this->numberOfFrames = num;
}

quint16 FrameData::getNumberOfFrames(){
    return this->numberOfFrames;
}

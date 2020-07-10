#include "framedata.h"
#include <QDebug>
FrameData::FrameData()
{
    this->currentFrame = 0;
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

void FrameData::setPedestrianRel(quint16 *pedestrianRel){
    for(int i = 0; i < MAX_PEDESTRIAN; i++){
        this->pedestrianRel[i] = pedestrianRel[i];
    }
}

void FrameData::setVehicleRel(quint16 *vehicleRel){
    for(int i = 0; i < MAX_VEHICLE; i++){
        this->vehicleRel[i] = vehicleRel[i];
    }
}

void FrameData::printFrameData(){
    qDebug()<<"-------- FRAME"<<this->getCurrentFrameNum()<<"---------";
    qDebug()<<"Timestamp:\t\t"<<this->timestamp;
    qDebug()<<"Pedestrian number:\t"<<this->numPedestrian;
    /*for(int i = 0 ; i < MAX_PEDESTRIAN; i++){
        qDebug()<<"X"<<i<<":"<<pedestrianRel[i*2];
        qDebug()<<"Y"<<i<<":"<<pedestrianRel[i*2 + 1];
    }*/
    qDebug()<<"Veicle number:\t"<<this->numVehicle;
    /*for(int i = 0 ; i < MAX_VEHICLE; i++){
        qDebug()<<"X"<<i<<":"<<vehicleRel[i*2];
        qDebug()<<"Y"<<i<<":"<<vehicleRel[i*2 + 1];
    }*/
    qDebug()<<"-------------------------------";
}

void FrameData::incrementCurrentFrame(){
    this->currentFrame++;
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

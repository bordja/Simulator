#include "collector.h"
#include <QDebug>
#include <QDataStream>
#include "header.h"
#include "framedata.h"

Header headers[FILE_NUM];
FrameData frames[FILE_NUM];

Collector::Collector()
{
    this->inFiles[0] = new QFile("E:/Qt/workspace/Simulator/data/perspective_out_1");
    if (this->inFiles[0]->open(QIODevice::ReadOnly)) {
        qDebug()<<"Opened "<<this->inFiles[0]->fileName();
        frames[0].setNumberOfFrames((this->inFiles[0]->size() - HEADER_SIZE)/FRAME_SIZE);
    }

    this->inFiles[1] = new QFile("E:/Qt/workspace/Simulator/data/perspective_out_2");
    if (this->inFiles[1]->open(QIODevice::ReadOnly)) {
        qDebug()<<"Opened "<<this->inFiles[1]->fileName();
        frames[1].setNumberOfFrames((this->inFiles[1]->size() - HEADER_SIZE)/FRAME_SIZE);
    }

    this->inFiles[2] = new QFile("E:/Qt/workspace/Simulator/data/perspective_out_3");
    if (this->inFiles[2]->open(QIODevice::ReadOnly)) {
        qDebug()<<"Opened "<<this->inFiles[2]->fileName();
        frames[2].setNumberOfFrames((this->inFiles[2]->size() - HEADER_SIZE)/FRAME_SIZE);
    }

    this->inFiles[3] = new QFile("E:/Qt/workspace/Simulator/data/perspective_out_4");
    if (this->inFiles[3]->open(QIODevice::ReadOnly)) {
        qDebug()<<"Opened "<<this->inFiles[3]->fileName();
        frames[3].setNumberOfFrames((this->inFiles[3]->size() - HEADER_SIZE)/FRAME_SIZE);
    }
    connect(this,&Collector::frameRead,this,&Collector::readDataFromFile);
}

void Collector::readDataFromFile(int fileID){

    this->inFiles[fileID]->seek(HEADER_SIZE + FRAME_SIZE * frames[fileID].getCurrentFrameNum());

    quint64 timestamp;
    quint16 numPedestrian;
    quint16 numVehicle;
    quint16 pedestrianRel[2 * MAX_PEDESTRIAN];
    quint16 vehicleRel[2 * MAX_VEHICLE];

    QDataStream dataCollector(this->inFiles[fileID]);
    //int toSkip = HEADER_SIZE + FRAME_SIZE * frames[fileID].getCurrentFrameNum();
    //dataCollector.skipRawData(toSkip);
    dataCollector.setByteOrder(QDataStream::LittleEndian);

    dataCollector>>timestamp;
    dataCollector>>numPedestrian;
    for(int i = 0; i < MAX_PEDESTRIAN; i++){
        dataCollector>>pedestrianRel[i*2];
        dataCollector>>pedestrianRel[i*2+1];
    }
    qDebug()<<"Position "<<this->inFiles[fileID]->pos();
    dataCollector>>numVehicle;
    for(int i = 0; i < MAX_VEHICLE; i++){
        dataCollector>>vehicleRel[i*2];
        dataCollector>>vehicleRel[i*2+1];
    }

    frames[fileID].setTimestamp(timestamp);
    frames[fileID].setPedestrianNum(numPedestrian);
    frames[fileID].setVehicleNum(numVehicle);
    frames[fileID].setPedestrianRel(pedestrianRel);
    frames[fileID].setVehicleRel(vehicleRel);
    frames[fileID].printFrameData();

    if(frames[fileID].getCurrentFrameNum() != frames[fileID].getNumberOfFrames()){
        frames[fileID].incrementCurrentFrame();
        emit frameRead(fileID);
    }

}

void Collector::readFileHeader(int fileID){
    QDataStream inData(this->inFiles[fileID]);
    inData.setByteOrder(QDataStream::LittleEndian);

    quint8 cam_ID;
    quint32 pole1_ID;
    quint32 pole2_ID;
    quint32 pole3_ID;
    quint32 pole4_ID;
    quint16 pole1_rel_x;
    quint16 pole1_rel_y;
    quint16 pole2_rel_x;
    quint16 pole2_rel_y;
    quint16 pole3_rel_x;
    quint16 pole3_rel_y;
    quint16 pole4_rel_x;
    quint16 pole4_rel_y;

    inData>>cam_ID;
    inData>>pole1_ID;
    inData>>pole2_ID;
    inData>>pole3_ID;
    inData>>pole4_ID;
    inData>>pole1_rel_x;
    inData>>pole1_rel_y;
    inData>>pole2_rel_x;
    inData>>pole2_rel_y;
    inData>>pole3_rel_x;
    inData>>pole3_rel_y;
    inData>>pole4_rel_x;
    inData>>pole4_rel_y;

    headers[fileID].setCam_ID(cam_ID);
    headers[fileID].setPole1_ID(pole1_ID);
    headers[fileID].setPole2_ID(pole2_ID);
    headers[fileID].setPole3_ID(pole3_ID);
    headers[fileID].setPole4_ID(pole4_ID);
    headers[fileID].setPole1_rel_X(pole1_rel_x);
    headers[fileID].setPole1_rel_Y(pole1_rel_y);
    headers[fileID].setPole2_rel_X(pole2_rel_x);
    headers[fileID].setPole2_rel_Y(pole2_rel_y);
    headers[fileID].setPole3_rel_X(pole3_rel_x);
    headers[fileID].setPole3_rel_Y(pole3_rel_y);
    headers[fileID].setPole4_rel_X(pole4_rel_x);
    headers[fileID].setPole4_rel_Y(pole4_rel_y);
    headers[fileID].printHeader();

}

Collector::~Collector(){
    for(int i = 0 ;i < FILE_NUM;i++){
        this->inFiles[i]->close();
    }
}

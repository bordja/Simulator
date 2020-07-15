#include "collector.h"
#include <QDebug>
#include <QDataStream>
#include <QThread>
Collector::Collector(Simulator& simulator)
{
    this->files[0].setFileDescriptor(new QFile("E:/Qt/workspace/Simulator/data/out_perspective_dets_v3/perspective_out_1"));
    if (this->files[0].openFile()) {
        qDebug()<<"Opened "<<this->files[0].getFileDescriptor()->fileName()<<"FILE ID: "<<this->files[0].getId();
        this->files[0].getFrameData().setNumberOfFrames((this->files[0].getFileDescriptor()->size() - HEADER_SIZE)/FRAME_SIZE);
    }
    connect(&files[0],&File::dataReady,&simulator, &Simulator::updateDynamicGraphic);
    connect(&simulator,&Simulator::graphicUpdated,this, &Collector::readDataFromFile);

    this->files[1].setFileDescriptor(new QFile("E:/Qt/workspace/Simulator/data/out_perspective_dets_v3/perspective_out_2"));
    if (this->files[1].openFile()) {
        qDebug()<<"Opened "<<this->files[1].getFileDescriptor()->fileName()<<"FILE ID: "<<this->files[1].getId();
        this->files[1].getFrameData().setNumberOfFrames((this->files[1].getFileDescriptor()->size() - HEADER_SIZE)/FRAME_SIZE);
    }
    connect(&files[1],&File::dataReady,&simulator, &Simulator::updateDynamicGraphic);

    this->files[2].setFileDescriptor(new QFile("E:/Qt/workspace/Simulator/data/out_perspective_dets_v3/perspective_out_3"));
    if (this->files[2].openFile()) {
        qDebug()<<"Opened "<<this->files[2].getFileDescriptor()->fileName()<<"FILE ID: "<<this->files[2].getId();
        this->files[2].getFrameData().setNumberOfFrames((this->files[2].getFileDescriptor()->size() - HEADER_SIZE)/FRAME_SIZE);
    }
    connect(&files[2],&File::dataReady,&simulator, &Simulator::updateDynamicGraphic);

    this->files[3].setFileDescriptor(new QFile("E:/Qt/workspace/Simulator/data/out_perspective_dets_v3/perspective_out_4"));
    if (this->files[3].openFile()) {
        qDebug()<<"Opened "<<this->files[3].getFileDescriptor()->fileName()<<"FILE ID: "<<this->files[3].getId();
        this->files[3].getFrameData().setNumberOfFrames((this->files[3].getFileDescriptor()->size() - HEADER_SIZE)/FRAME_SIZE);
    }
    connect(&files[3],&File::dataReady,&simulator, &Simulator::updateDynamicGraphic);
}

void Collector::readDataFromFile(int fileID){
    QThread::msleep(100);
    quint64 timestamp;
    quint16 numPedestrian;
    quint16 numVehicle;
    quint16 pedestrianRel[2 * MAX_PEDESTRIAN];
    quint16 vehicleRel[2 * MAX_VEHICLE];

//    quint16 tmp_x;
//    quint16 tmp_y;
//    int k = 0;
    this->files[fileID].getFileDescriptor()->seek(HEADER_SIZE + FRAME_SIZE * files[fileID].getFrameData().getCurrentFrameNum());

    QDataStream dataCollector(this->files[fileID].getFileDescriptor());

    dataCollector.setByteOrder(QDataStream::LittleEndian);

    dataCollector>>timestamp;
    dataCollector>>numPedestrian;

    for(int i = 0; i < MAX_PEDESTRIAN; i++){
//        dataCollector>>tmp_x;
//        dataCollector>>tmp_y;
//        if(tmp_x < 1920 && tmp_y < 1080){
//            pedestrianRel[k*2] = tmp_x;
//            pedestrianRel[k*2+1] = tmp_y;
//            k++;
//        }
//        else{
//            numPedestrian--;
//        }
        dataCollector>>pedestrianRel[i*2];
        dataCollector>>pedestrianRel[i*2+1];
    }

    dataCollector>>numVehicle;

//    k = 0;
    for(int i = 0; i < MAX_VEHICLE; i++){
//        dataCollector>>tmp_x;
//        dataCollector>>tmp_y;
//        if(tmp_x < 1920 && tmp_y < 1080){
//            vehicleRel[k*2] = tmp_x;
//            vehicleRel[k*2+1] = tmp_y;
//            k++;
//        }
//        else{
//            numVehicle--;
//        }
        dataCollector>>vehicleRel[i*2];
        dataCollector>>vehicleRel[i*2+1];
    }

    files[fileID].getFrameData().setTimestamp(timestamp);
    files[fileID].getFrameData().setPedestrianNum(numPedestrian);
    files[fileID].getFrameData().setVehicleNum(numVehicle);
    //files[fileID].getFrameData().printFrameData();

    if(files[fileID].getFrameData().getCurrentFrameNum() != files[fileID].getFrameData().getNumberOfFrames()){
        files[fileID].getFrameData().incrementCurrentFrame();
        files[fileID].calculateCoordinates(pedestrianRel,numPedestrian,vehicleRel,numVehicle);
    }
    else{
        emit finished();
    }
}

void Collector::readFileHeader(int fileID){
    QDataStream dataCollector(this->files[fileID].getFileDescriptor());
    dataCollector.setByteOrder(QDataStream::LittleEndian);

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

    dataCollector>>cam_ID;
    dataCollector>>pole1_ID;
    dataCollector>>pole2_ID;
    dataCollector>>pole3_ID;
    dataCollector>>pole4_ID;
    dataCollector>>pole1_rel_x;
    dataCollector>>pole1_rel_y;
    dataCollector>>pole2_rel_x;
    dataCollector>>pole2_rel_y;
    dataCollector>>pole3_rel_x;
    dataCollector>>pole3_rel_y;
    dataCollector>>pole4_rel_x;
    dataCollector>>pole4_rel_y;

    files[fileID].getHeader().setCam_ID(cam_ID);
    files[fileID].getHeader().calculateParameters(pole3_ID,pole4_ID,pole1_ID,pole3_rel_x,pole3_rel_y,pole4_rel_x,pole4_rel_y,pole1_rel_x,pole1_rel_y);
    files[fileID].getHeader().printHeader();
}

File* Collector::getFile(int id)
{
    return &(this->files[id]);
}

void Collector::start()
{
    this->readFileHeader(3);
    this->readDataFromFile(3);
}

Collector::~Collector(){
    for(int i = 0 ;i < FILE_NUM;i++){
        this->files[i].getFileDescriptor()->close();
    }
}

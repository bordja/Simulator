#include "collector.h"
#include <QDebug>
#include <QDataStream>
#include <QThread>

#define FPS_60 16.66666F

quint64 currentTimestamp;
Collector::Collector(Simulator& simulator)
{
    this->files[0] = new File();
    this->files[1] = new File();
    this->files[2] = new File();
    this->files[3] = new File();

    this->files[0]->setFileDescriptor(new QFile("E:/Qt/workspace/Simulator/data/out_perspective_dets_v5/out_perspective_1"));
    if (this->files[0]->openFile()) {
        qDebug()<<"Opened "<<this->files[0]->getFileDescriptor()->fileName()<<"FILE ID: "<<this->files[0]->getId();
        this->files[0]->getFrameData().setNumberOfFrames((this->files[0]->getFileDescriptor()->size() - HEADER_SIZE)/FRAME_SIZE);
    }

    this->files[1]->setFileDescriptor(new QFile("E:/Qt/workspace/Simulator/data/out_perspective_dets_v5/out_perspective_2"));
    if (this->files[1]->openFile()) {
        qDebug()<<"Opened "<<this->files[1]->getFileDescriptor()->fileName()<<"FILE ID: "<<this->files[1]->getId();
        this->files[1]->getFrameData().setNumberOfFrames((this->files[1]->getFileDescriptor()->size() - HEADER_SIZE)/FRAME_SIZE);
    }

    this->files[2]->setFileDescriptor(new QFile("E:/Qt/workspace/Simulator/data/out_perspective_dets_v5/out_perspective_3"));
    if (this->files[2]->openFile()) {
        qDebug()<<"Opened "<<this->files[2]->getFileDescriptor()->fileName()<<"FILE ID: "<<this->files[2]->getId();
        this->files[2]->getFrameData().setNumberOfFrames((this->files[2]->getFileDescriptor()->size() - HEADER_SIZE)/FRAME_SIZE);
    }

    this->files[3]->setFileDescriptor(new QFile("E:/Qt/workspace/Simulator/data/out_perspective_dets_v5/out_perspective_4"));
    if (this->files[3]->openFile()) {
        qDebug()<<"Opened "<<this->files[3]->getFileDescriptor()->fileName()<<"FILE ID: "<<this->files[3]->getId();
        this->files[3]->getFrameData().setNumberOfFrames((this->files[3]->getFileDescriptor()->size() - HEADER_SIZE)/FRAME_SIZE);
    }

    connect(&simulator,&Simulator::graphicUpdated,this, &Collector::readFiles);
    connect(this, &Collector::dataReady,&simulator,&Simulator::updateDynamicGraphic);
}

void Collector::readDataFromFile(int fileID){
    QThread::msleep(70);
    quint64 timestamp;
    quint16 numPedestrian;
    quint16 numVehicle;
    quint16 pedestrianRel[2 * MAX_PEDESTRIAN];
    quint16 vehicleRel[2 * MAX_VEHICLE];

    this->files[fileID]->getFileDescriptor()->seek(HEADER_SIZE + FRAME_SIZE * files[fileID]->getFrameData().getCurrentFrameNum());

    QDataStream dataCollector(this->files[fileID]->getFileDescriptor());

    dataCollector.setByteOrder(QDataStream::LittleEndian);

    dataCollector>>timestamp;
    dataCollector>>numPedestrian;

    for(int i = 0; i < MAX_PEDESTRIAN; i++){

        dataCollector>>pedestrianRel[i*2];
        dataCollector>>pedestrianRel[i*2+1];
    }

    dataCollector>>numVehicle;

    for(int i = 0; i < MAX_VEHICLE; i++){

        dataCollector>>vehicleRel[i*2];
        dataCollector>>vehicleRel[i*2+1];
    }

    files[fileID]->getFrameData().setTimestamp(timestamp);
    files[fileID]->getFrameData().setPedestrianNum(numPedestrian);
    files[fileID]->getFrameData().setVehicleNum(numVehicle);

    if(files[fileID]->getFrameData().getCurrentFrameNum() != files[fileID]->getFrameData().getNumberOfFrames()){
        files[fileID]->getFrameData().incrementCurrentFrame();
        files[fileID]->calculateCoordinates(pedestrianRel,numPedestrian,vehicleRel,numVehicle);
    }
    else{
        emit finished();
    }
}

void Collector::readFileHeader(int fileID){
    QDataStream dataCollector(this->files[fileID]->getFileDescriptor());
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

    files[fileID]->getHeader().setCam_ID(cam_ID);
    files[fileID]->getHeader().calculateParameters(pole3_ID,pole4_ID,pole1_ID,pole3_rel_x,pole3_rel_y,pole4_rel_x,pole4_rel_y,pole1_rel_x,pole1_rel_y);
    files[fileID]->getHeader().printHeader();
}

File* Collector::getFile(int id)
{
    return (this->files[id]);
}

void Collector::start()
{
    for(int i = 0; i < FILE_NUM; i++){
        this->files[i]->setActive(false);
        this->readFileHeader(i);
    }
    initTimestamps();
    readFiles();
}

void Collector::initTimestamps(){

    quint64 timestamps [FILE_NUM];
    quint64 minTimestamp;
    for(int i = 0; i < FILE_NUM; i++){
        readDataFromFile(i);
        timestamps[i] = this->files[i]->getFrameData().getTimestamp();
        this->files[i]->getFrameData().setCurrentFrameToZero(); //readDataFromFile is incrementing current frame; needs to be set to 0
    }
    minTimestamp = timestamps[0];
    for(int i = 1; i < FILE_NUM; i++){
        if(minTimestamp > timestamps[i]){
            minTimestamp = timestamps[i];
        }
    }
    currentTimestamp = minTimestamp;
    updateActiveFiles();
}

void Collector::readFiles()
{
    updateCurrentTime();
    updateActiveFiles();

    for(int i = 0; i < FILE_NUM; i++){
        if(this->files[i]->getActive()){
            readDataFromFile(i);
        }
    }

    //printActive();
    emit dataReady(this->files);

}

void Collector::updateActiveFiles()
{
    for(int i = 0; i < FILE_NUM; i++){
        if(this->files[i]->getFrameData().getTimestamp() - currentTimestamp < FPS_60){
            this->files[i]->setActive(true);
        }
    }
}

void Collector::updateCurrentTime()
{
    quint64 timestamps [FILE_NUM];
    int k = 0;
    quint64 minTimestamp;
    for(int i = 0; i < FILE_NUM; i++){
        timestamps[i] = 0;
        if(this->files[i]->getActive()){
            this->files[i]->getFileDescriptor()->seek(HEADER_SIZE + FRAME_SIZE * files[i]->getFrameData().getCurrentFrameNum());
            QDataStream dataCollector(this->files[i]->getFileDescriptor());
            dataCollector.setByteOrder(QDataStream::LittleEndian);
            dataCollector>>timestamps[k];
            k++;
        }
    }
    minTimestamp = timestamps[0];
    for(int i = 1; i < k; i++){
        if(minTimestamp > timestamps[i]){
            minTimestamp = timestamps[i];
        }
    }
    currentTimestamp = minTimestamp;
}

void Collector::printActive()
{
    bool activeFiles[FILE_NUM];
    for(int i = 0; i < FILE_NUM; i++){
        activeFiles[i] = this->files[i]->getActive();
    }
    qDebug()<<"[ "<<activeFiles[0]<<", "<<activeFiles[1]<<", "<<activeFiles[2]<<", "<<activeFiles[3]<<", "<<" ]";
}
Collector::~Collector(){
    for(int i = 0 ;i < FILE_NUM;i++){
        this->files[i]->getFileDescriptor()->close();
    }
}

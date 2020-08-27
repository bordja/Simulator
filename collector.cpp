#include "collector.h"
#include <QDebug>
#include <QDataStream>
#include <QThread>
#include <QtMath>

#define FPS_60 16.66666F
#define METER 0.000012399150693404L
quint64 currentTimestamp;
Collector::Collector(Simulator& simulator)
{
    this->files[0] = new File();
    this->files[1] = new File();
    this->files[2] = new File();
    this->files[3] = new File();

    this->files[0]->setFileDescriptor(new QFile("E:/Qt/workspace/Simulator/data/out_perspective_dets_v6/out_perspective_1"));
    if (this->files[0]->openFile()) {
        qDebug()<<"Opened "<<this->files[0]->getFileDescriptor()->fileName()<<"FILE ID: "<<this->files[0]->getId();
        this->files[0]->getFrameData().setNumberOfFrames((this->files[0]->getFileDescriptor()->size() - HEADER_SIZE)/FRAME_SIZE);
    }

    this->files[1]->setFileDescriptor(new QFile("E:/Qt/workspace/Simulator/data/out_perspective_dets_v6/out_perspective_2"));
    if (this->files[1]->openFile()) {
        qDebug()<<"Opened "<<this->files[1]->getFileDescriptor()->fileName()<<"FILE ID: "<<this->files[1]->getId();
        this->files[1]->getFrameData().setNumberOfFrames((this->files[1]->getFileDescriptor()->size() - HEADER_SIZE)/FRAME_SIZE);
    }

    this->files[2]->setFileDescriptor(new QFile("E:/Qt/workspace/Simulator/data/out_perspective_dets_v6/out_perspective_3"));
    if (this->files[2]->openFile()) {
        qDebug()<<"Opened "<<this->files[2]->getFileDescriptor()->fileName()<<"FILE ID: "<<this->files[2]->getId();
        this->files[2]->getFrameData().setNumberOfFrames((this->files[2]->getFileDescriptor()->size() - HEADER_SIZE)/FRAME_SIZE);
    }

    this->files[3]->setFileDescriptor(new QFile("E:/Qt/workspace/Simulator/data/out_perspective_dets_v6/out_perspective_4"));
    if (this->files[3]->openFile()) {
        qDebug()<<"Opened "<<this->files[3]->getFileDescriptor()->fileName()<<"FILE ID: "<<this->files[3]->getId();
        this->files[3]->getFrameData().setNumberOfFrames((this->files[3]->getFileDescriptor()->size() - HEADER_SIZE)/FRAME_SIZE);
    }

    finalPedestrians = new QList<Pedestrian*>;
    finalVehicles = new QList<Vehicle*>;

    connect(&simulator,&Simulator::graphicUpdated,this, &Collector::readFiles);
    connect(this, &Collector::dataReady,&simulator,&Simulator::updateDynamicGraphic);
    connect(this, &Collector::fileEnd, this, &Collector::checkSimulationFinished);
}

void Collector::readDataFromFile(int fileID){
    QThread::msleep(15);
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
        files[fileID]->setActive(false);
        emit fileEnd();
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
    int activeCnt = 0;
    int activeIdx;
    updateCurrentTime();
    updateActiveFiles();

    for(int i = 0; i < FILE_NUM; i++){
        if(this->files[i]->getActive()){
            readDataFromFile(i);
            activeCnt++;
            activeIdx = i;
        }
    }
    if(activeCnt > 1){
        if(this->files[0]->getActive()){
            if(this->files[1]->getActive()){
                mergeDoublesAlg(0,1);
            }
            if(this->files[2]->getActive()){
                mergeDoublesAlg(0,2);
            }
            if(this->files[3]->getActive()){
                mergeDoublesAlg(0,3);
            }
        }

        if(this->files[1]->getActive()){
            if(this->files[2]->getActive()){
                mergeDoublesAlg(1,2);
            }
            if(this->files[3]->getActive()){
                mergeDoublesAlg(1,3);
            }
        }
        if(this->files[2]->getActive()){
            if(this->files[3]->getActive()){
                mergeDoublesAlg(2,3);
            }
        }
    }else{
        emit dataReady(this->getFile(activeIdx)->getFrameData().pedestrians,this->getFile(activeIdx)->getFrameData().vehicles);
        return;
    }

    emit dataReady(finalPedestrians, finalVehicles);

}

void Collector::checkSimulationFinished()
{
    bool simulationEnd = true;
    for(int i = 0; i < FILE_NUM; i++){
        if(this->files[i]->getActive()){
            simulationEnd = false;
        }
    }
    if(simulationEnd){
        emit finished();
    }
}

void Collector::updateActiveFiles()
{
    for(int i = 0; i < FILE_NUM; i++){
        if((qint64)(this->files[i]->getFrameData().getTimestamp() - currentTimestamp) < FPS_60){
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

void Collector::mergeDoublesAlg(int i, int j)
{
    //Pedestrians
    QList<Pedestrian*>::iterator it0 = this->getFile(i)->getFrameData().pedestrians->begin();
    for(;it0!= this->getFile(i)->getFrameData().pedestrians->end();it0++){

        QList<Pedestrian*>::iterator it1 = this->getFile(j)->getFrameData().pedestrians->begin();

        for(;it1!= this->getFile(j)->getFrameData().pedestrians->end();it1++){
            if(euclidDistanceP(*it1, *it0) < METER){
                if((*it0)->getInReferenceRegion() || (*it1)->getInReferenceRegion()){
                    if((*it0)->getInReferenceRegion() && (*it1)->getInReferenceRegion()){
                        finalPedestrians->append(mindegyP((*it0),(*it1)));
                        it0 = this->getFile(i)->getFrameData().pedestrians->erase(it0);
                        it1 = this->getFile(j)->getFrameData().pedestrians->erase(it1);
                        it0--;
                        it1--;
                    }
                    else{
                        if((*it0)->getInReferenceRegion()){
                            finalPedestrians->append(*it0);
                            it1 = this->getFile(j)->getFrameData().pedestrians->erase(it1);
                            it1--;
                        }
                        else{
                            finalPedestrians->append(*it1);
                            it0 = this->getFile(i)->getFrameData().pedestrians->erase(it0);
                            it0--;
                        }
                    }
                }
                else{
                    finalPedestrians->append(mindegyP((*it0),(*it1)));
                    it0 = this->getFile(i)->getFrameData().pedestrians->erase(it0);
                    it1 = this->getFile(j)->getFrameData().pedestrians->erase(it1);
                    it0--;
                    it1--;
                }
            }else{
                finalPedestrians->append(*it0);
            }
        }
    }
    //Vehicles
    QList<Vehicle*>::iterator itv0 = this->getFile(i)->getFrameData().vehicles->begin();
    for(;itv0!= this->getFile(i)->getFrameData().vehicles->end();itv0++){

        QList<Vehicle*>::iterator itv1 = this->getFile(j)->getFrameData().vehicles->begin();

        for(;itv1!= this->getFile(j)->getFrameData().vehicles->end();itv1++){
            if(euclidDistanceV(*itv1, *itv0) < (METER * 3)){
                if((*itv0)->getInReferenceRegion() || (*itv1)->getInReferenceRegion()){
                    if((*itv0)->getInReferenceRegion() && (*itv1)->getInReferenceRegion()){
                        finalVehicles->append(mindegyV((*itv0),(*itv1)));
                        itv0 = this->getFile(i)->getFrameData().vehicles->erase(itv0);
                        itv1 = this->getFile(j)->getFrameData().vehicles->erase(itv1);
                        itv0--;
                        itv1--;
                    }
                    else{
                        if((*itv0)->getInReferenceRegion()){
                            finalVehicles->append(*itv0);
                            itv1 = this->getFile(j)->getFrameData().vehicles->erase(itv1);
                            itv1--;
                        }
                        else{
                            finalVehicles->append(*itv1);
                            itv0 = this->getFile(i)->getFrameData().vehicles->erase(itv0);
                            itv0--;
                        }
                    }
                }
                else{
                    finalVehicles->append(mindegyV((*itv0),(*itv1)));
                    itv0 = this->getFile(i)->getFrameData().vehicles->erase(itv0);
                    itv1 = this->getFile(j)->getFrameData().vehicles->erase(itv1);
                    itv0--;
                    itv1--;
                }
            }else{
                finalVehicles->append(*itv0);
            }
        }
    }
}

double Collector::euclidDistanceP(Pedestrian *p1, Pedestrian *p2)
{
    return qSqrt(qPow((p2->getLocation().x()) - (p1->getLocation().x()),2) + qPow((p2->getLocation().y()) - (p1->getLocation().y()),2));
}

double Collector::euclidDistanceV(Vehicle *v1, Vehicle *v2)
{
    return qSqrt(qPow((v2->getLocation().x()) - (v1->getLocation().x()),2) + qPow((v2->getLocation().y()) - (v1->getLocation().y()),2));
}

Pedestrian *Collector::mindegyP(Pedestrian *p1, Pedestrian *p2)
{
    double newX = (p1->getLocation().x() + p2->getLocation().x())/2;
    double newY = (p1->getLocation().y() + p2->getLocation().y())/2;
    Pedestrian* p = new Pedestrian(newX,newY,0);
    return p;
}

Vehicle *Collector::mindegyV(Vehicle *v1, Vehicle *v2)
{
    double newX = (v1->getLocation().x() + v2->getLocation().x())/2;
    double newY = (v1->getLocation().y() + v2->getLocation().y())/2;
    Vehicle* v = new Vehicle(newX,newY,0);
    return v;
}

Collector::~Collector(){
    for(int i = 0 ;i < FILE_NUM;i++){
        this->files[i]->getFileDescriptor()->close();
    }
}

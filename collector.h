#ifndef COLLECTOR_H
#define COLLECTOR_H

#include <QtGlobal>
#include "file.h"
#include "Simulator.h"
#define FILE_NUM 4

class Collector : public QObject
{
    Q_OBJECT
public:
    Collector(Simulator&);
    ~Collector();

    void readFileHeader(int fileID);
    File* getFile(int id);
    void start();
    void initTimestamps();
    void readDataFromFile(int fileID);
    void updateActiveFiles();
    void updateCurrentTime();
    void printActive();
    void mergeDoublesAlg(int,int);
    double euclidDistanceP(Pedestrian* p1,Pedestrian* p2);
    double euclidDistanceV(Vehicle* v1, Vehicle* v2);
    Pedestrian* mindegyP(Pedestrian* p1,Pedestrian* p2);
    Vehicle* mindegyV(Vehicle* v1, Vehicle* v2);
    QList<Pedestrian*>* finalPedestrians;
    QList<Vehicle*>* finalVehicles;

private:
    File* files[FILE_NUM];
signals:
    void finished();
    void dataReady(QList<Pedestrian*>*, QList<Vehicle*>*);
    void fileEnd();
public slots:
    void readFiles();
    void checkSimulationFinished();
};

#endif // COLLECTOR_H

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
private:
    File* files[FILE_NUM];
signals:
    void finished();
    void dataReady(File** f);
    void fileEnd();
public slots:
    void readFiles();
    void checkSimulationFinished();
};

#endif // COLLECTOR_H

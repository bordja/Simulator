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
private:
    File files[FILE_NUM];
signals:
    void finished();
public slots:
    void readDataFromFile(int fileID);
    void readData();
};

#endif // COLLECTOR_H

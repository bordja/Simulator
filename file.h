#ifndef FILE_H
#define FILE_H

#include "header.h"
#include "framedata.h"
#include <QFile>
class File : public QObject
{
    Q_OBJECT
public:
    File();
    File(int id);
    void setFileDescriptor(QFile*);
    bool openFile();
    Header& getHeader();
    FrameData& getFrameData();
    QFile* getFileDescriptor();
    int getId();
    void calculateCoordinates(quint16* pedestrianCoors, int pedestrianNum, quint16* vehicleCoords, int vehicleNum);
signals:
    void dataReady(File* f);
private:
    QFile* fileDescriptor;
    Header header;
    FrameData data;
    int id;
};

#endif // FILE_H

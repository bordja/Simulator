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
    bool getActive() const;
    void setActive(bool value);
    void setPedestrianInRef(Pedestrian* p);
    void setVehicleInRef(Vehicle* v);
private:
    QFile* fileDescriptor;
    Header header;
    FrameData data;
    bool active;
    int id;
};

#endif // FILE_H

#ifndef COLLECTOR_H
#define COLLECTOR_H

#include <QFile>
#include <QtGlobal>

#define FILE_NUM 4
#define HEADER_SIZE 33
class Collector : public QObject
{
    Q_OBJECT
public:
    Collector();
    ~Collector();

    void readFileHeader(int fileID);
private:
    QFile* inFiles[FILE_NUM];

signals:
    void frameRead(int);
public slots:
    void readDataFromFile(int fileID);

};

#endif // COLLECTOR_H

#include "file.h"
#include "header.h"
static int counter = 0;

File::File()
{
    this->id = counter;
    counter++;
}

void File::setFileDescriptor(QFile *fileDescriptor){
    this->fileDescriptor = fileDescriptor;
}

bool File::openFile(){
    return this->fileDescriptor->open(QIODevice::ReadOnly);
}

Header& File::getHeader(){
    return this->header;
}

FrameData& File::getFrameData(){
    return this->data;
}

QFile* File::getFileDescriptor(){
    return this->fileDescriptor;
}

int File::getId(){
    return this->id;
}

void File::calculateCoordinates(quint16 *pedestrianCoors, int pedestrianNum, quint16 *vehicleCoords, int vehicleNum){
    qint16 x_temp;
    qint16 y_temp;
    qint16 delta_x;
    qint16 delta_y;

    if(!(this->getFrameData().pedestrians.isEmpty())){
        this->getFrameData().pedestrians.clear();
    }
    if(!(this->getFrameData().vehicles.isEmpty())){
        this->getFrameData().vehicles.clear();
    }
    double xAbs_temp = this->getHeader().getOx_abs();
    double yAbs_temp = this->getHeader().getOy_abs();
    for(int i = 0; i < pedestrianNum; i++){
        x_temp = pedestrianCoors[i * 2];
        y_temp = 1080 - pedestrianCoors[i * 2 + 1];
        delta_x = x_temp - this->getHeader().getOx();
        delta_y = y_temp - this->getHeader().getOy();

        xAbs_temp+=((delta_x * this->getHeader().getPx_x()) + (delta_y * this->getHeader().getPy_x()));
        yAbs_temp+=((delta_x * this->getHeader().getPx_y()) + (delta_y * this->getHeader().getPy_y()));
        Pedestrian* p = new Pedestrian(yAbs_temp,xAbs_temp,i);
        this->getFrameData().appendPedestrian(p);
    }

    for(int i = 0; i < vehicleNum; i++){
        x_temp = vehicleCoords[i * 2];
        y_temp = 1080 - vehicleCoords[i * 2 + 1];
        delta_x = x_temp - this->getHeader().getOx();
        delta_y = y_temp - this->getHeader().getOy();

        xAbs_temp+=((delta_x * this->getHeader().getPx_x()) + (delta_y * this->getHeader().getPy_x()));
        yAbs_temp+=((delta_x * this->getHeader().getPx_y()) + (delta_y * this->getHeader().getPy_y()));
        Vehicle* v = new Vehicle(yAbs_temp,xAbs_temp,i);
        this->getFrameData().appendVehicle(v);
    }
    emit dataReady(this);
}

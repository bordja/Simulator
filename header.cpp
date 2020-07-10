#include "header.h"
#include <QDebug>
Header::Header()
{

}
void Header::setCam_ID(qint8 cam_ID){
    this->cam_ID = cam_ID;
}

void Header::setPole1_ID(qint32 pole1_ID){
    this->pole1_ID = pole1_ID;
}

void Header::setPole2_ID(qint32 pole2_ID){
    this->pole2_ID = pole2_ID;
}

void Header::setPole3_ID(qint32 pole3_ID){
    this->pole3_ID = pole3_ID;
}

void Header::setPole4_ID(qint32 pole4_ID){
    this->pole4_ID = pole4_ID;
}

void Header::setPole1_rel_X(qint16 pole1_rel_x){
    this->pole1_rel_x = pole1_rel_x;
}

void Header::setPole1_rel_Y(qint16 pole1_rel_y){
    this->pole1_rel_y = pole1_rel_y;
}

void Header::setPole2_rel_X(qint16 pole2_rel_x){
    this->pole2_rel_x = pole2_rel_x;
}

void Header::setPole2_rel_Y(qint16 pole2_rel_y){
    this->pole2_rel_y = pole2_rel_y;
}

void Header::setPole3_rel_X(qint16 pole3_rel_x){
    this->pole3_rel_x = pole3_rel_x;
}

void Header::setPole3_rel_Y(qint16 pole3_rel_y){
    this->pole3_rel_y = pole3_rel_y;
}

void Header::setPole4_rel_X(qint16 pole4_rel_x){
    this->pole4_rel_x = pole4_rel_x;
}

void Header::setPole4_rel_Y(qint16 pole4_rel_y){
    this->pole4_rel_y = pole4_rel_y;
}

void Header::printHeader(){
    qDebug()<<"--------HEADER---------";
    qDebug()<<"CAM ID\t"<<this->cam_ID;
    qDebug()<<"POLE 1 ID\t"<<this->pole1_ID;
    qDebug()<<"\t"<<this->pole1_rel_x;
    qDebug()<<"\t"<<this->pole1_rel_y;
    qDebug()<<"POLE 2 ID\t"<<this->pole2_ID;
    qDebug()<<"\t"<<this->pole2_rel_x;
    qDebug()<<"\t"<<this->pole2_rel_y;
    qDebug()<<"POLE 3 ID\t"<<this->pole3_ID;
    qDebug()<<"\t"<<this->pole3_rel_x;
    qDebug()<<"\t"<<this->pole3_rel_y;
    qDebug()<<"POLE 4 ID\t"<<this->pole4_ID;
    qDebug()<<"\t"<<this->pole4_rel_x;
    qDebug()<<"\t"<<this->pole4_rel_y;
    qDebug()<<"------------------------";

}

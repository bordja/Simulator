#include "header.h"
#include <QDebug>

Header::Header()
{

}

void Header::calculateParameters(quint32 pole0_ID, quint32 poleDx_ID, quint32 poleDy_ID, quint16 pole0_rel_x, quint16 pole0_rel_y, quint16 poleDx_rel_x, quint16 poleDx_rel_y, quint16 poleDy_rel_x, quint16 poleDy_rel_y)
{
    this->setOx(pole0_rel_x);
    this->setOy(1080 - pole0_rel_y);
    this->setOx_abs(this->getPoleFromId(pole0_ID).x());
    this->setOy_abs(this->getPoleFromId(pole0_ID).y());
    qDebug()<<"Pole0_ID\t"<<pole0_ID;
    qDebug()<<"PoleDx_ID\t"<<poleDx_ID;
    qDebug()<<"PoleDy_ID\t"<<poleDy_ID;
    quint16 Ax = poleDx_rel_x;
    quint16 Ay = 1080 - poleDx_rel_y;
    double Ax_abs = this->getPoleFromId(poleDx_ID).x();
    double Ay_abs = this->getPoleFromId(poleDx_ID).y();


    quint16 delta_x = Ax - this->Ox;

    quint16 Bx = poleDy_rel_x;
    quint16 By = 1080 - poleDy_rel_y;
    double Bx_abs = this->getPoleFromId(poleDy_ID).x();
    double By_abs = this->getPoleFromId(poleDy_ID).y();


    quint16 delta_y = By - this->Oy;

    this->setPx_x((Ax_abs - Ox_abs)/delta_x);
    this->setPx_y((Ay_abs - Oy_abs)/delta_x);
    this->setPy_x((Bx_abs - Ox_abs)/delta_y);
    this->setPy_y((By_abs - Oy_abs)/delta_y);

}

void Header::printHeader(){
    qDebug()<<"--------HEADER---------";
    qDebug()<<"CAM ID\t"<<this->cam_ID;
    qDebug()<<"Px_x\t"<<this->getPx_x();
    qDebug()<<"Px_y\t"<<this->getPx_y();
    qDebug()<<"Py_x\t"<<this->getPy_x();
    qDebug()<<"Py_y\t"<<this->getPy_y();
    qDebug()<<"------------------------";

}

quint16 Header::getOx() const
{
    return Ox;
}

void Header::setOx(const quint16 &value)
{
    Ox = value;
}

quint16 Header::getOy() const
{
    return Oy;
}

void Header::setOy(const quint16 &value)
{
    Oy = value;
}

double Header::getPx_x() const
{
    return px_x;
}

void Header::setPx_x(double value)
{
    px_x = value;
}

double Header::getPx_y() const
{
    return px_y;
}

void Header::setPx_y(double value)
{
    px_y = value;
}

double Header::getPy_x() const
{
    return py_x;
}

void Header::setPy_x(double value)
{
    py_x = value;
}

double Header::getPy_y() const
{
    return py_y;
}

void Header::setPy_y(double value)
{
    py_y = value;
}

quint8 Header::getCam_ID() const
{
    return cam_ID;
}

void Header::setCam_ID(const quint8 &value)
{
    cam_ID = value;
}

double Header::getOx_abs() const
{
    return Ox_abs;
}

void Header::setOx_abs(double value)
{
    Ox_abs = value;
}

double Header::getOy_abs() const
{
    return Oy_abs;
}

void Header::setOy_abs(double value)
{
    Oy_abs = value;
}

Point Header::getPoleFromId(int id)
{
    QList<Pole*>::const_iterator it = poles.begin();

    for(;it!=poles.end();++it){
        if((*it)->getId() == id){
            return (*it)->getLocation();
        }
    }
}

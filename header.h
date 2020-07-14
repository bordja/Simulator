#ifndef HEADER_H
#define HEADER_H

#include<QtGlobal>
#include "pole.h"
#define HEADER_SIZE 33

class Header
{
public:
    Header();
    void calculateParameters(quint32 pole0_ID, quint32 poleDx_ID, quint32 poleDy_ID, quint16 pole0_rel_x, quint16 pole0_rel_y, quint16 poleDx_rel_x, quint16 poleDx_rel_y, quint16 poleDy_rel_x, quint16 poleDy_rel_y);
    void printHeader();

    quint16 getOx() const;
    void setOx(const quint16 &value);

    quint16 getOy() const;
    void setOy(const quint16 &value);

    double getPx_x() const;
    void setPx_x(double value);

    double getPx_y() const;
    void setPx_y(double value);

    double getPy_x() const;
    void setPy_x(double value);

    double getPy_y() const;
    void setPy_y(double value);

    quint8 getCam_ID() const;
    void setCam_ID(const quint8 &value);

    double getOx_abs() const;
    void setOx_abs(double value);

    double getOy_abs() const;
    void setOy_abs(double value);

    Point getPoleFromId(int id);

private:
    quint8 cam_ID;
    quint16 Ox;
    quint16 Oy;
    double Ox_abs;
    double Oy_abs;
    double px_x;
    double px_y;
    double py_x;
    double py_y;

};
#endif // HEADER_H

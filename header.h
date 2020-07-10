#ifndef HEADER_H
#define HEADER_H
#include<QtGlobal>

class Header
{
public:
    Header();
    void setCam_ID(qint8 cam_ID);
    void setPole1_ID(qint32 pole1_ID);
    void setPole2_ID(qint32 pole2_ID);
    void setPole3_ID(qint32 pole3_ID);
    void setPole4_ID(qint32 pole4_ID);
    void setPole1_rel_X(qint16 pole1_rel_x);
    void setPole1_rel_Y(qint16 pole1_rel_y);
    void setPole2_rel_X(qint16 pole2_rel_x);
    void setPole2_rel_Y(qint16 pole2_rel_y);
    void setPole3_rel_X(qint16 pole3_rel_x);
    void setPole3_rel_Y(qint16 pole3_rel_y);
    void setPole4_rel_X(qint16 pole4_rel_x);
    void setPole4_rel_Y(qint16 pole4_rel_y);
    void printHeader();

private:
    quint8 cam_ID;
    quint32 pole1_ID;
    quint32 pole2_ID;
    quint32 pole3_ID;
    quint32 pole4_ID;
    quint16 pole1_rel_x;
    quint16 pole1_rel_y;
    quint16 pole2_rel_x;
    quint16 pole2_rel_y;
    quint16 pole3_rel_x;
    quint16 pole3_rel_y;
    quint16 pole4_rel_x;
    quint16 pole4_rel_y;
};
#endif // HEADER_H

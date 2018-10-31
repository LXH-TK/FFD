#ifndef CONTROLPOINT_H
#define CONTROLPOINT_H

#include <QVector>
#include <QVector3D>

typedef struct Point {
    QVector3D pos;
    QVector3D oriPos;
    QVector3D color;
} mPoint;

class controlPoint {
public:
    controlPoint();
    //初始化控制点并可以改变
    void init(int x, int y, int z, float s);
    QVector3D getPosition(int x, int y, int z);
    ~controlPoint();
    int get_x();
    int get_y();
    int get_z();
    float getSize();
    void updateControlPoint(int x, int y, int z);
    void updateControlPointPos(QVector3D p, QVector3D delta);
    void setColor(int x, int y, int z, QVector3D color);
    QVector3D getColor(int x, int y, int z);
    
private:
    QVector<QVector<QVector<mPoint> > > mPoints;
    int num_x, num_y, num_z;
    float size;
};

#endif // CONTROLPOINT_H

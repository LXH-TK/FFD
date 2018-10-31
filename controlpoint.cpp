#include "controlpoint.h"

controlPoint::controlPoint() {
    init(2, 2, 2, 0.5);
}

controlPoint::~controlPoint() {
}

void controlPoint::init(int x, int y, int z, float s) {
    num_x = x;  num_y = y;  num_z = z;
    size = s;
    for(int i=0;i<x;i++) {
        //一面控制点
        QVector<QVector<mPoint> > ppp;
        for(int j=0;j<y;j++) {
            //一行控制点
            QVector<mPoint> pp;
            //分配网格参数坐标
            for(int k=0;k<z;k++) {
                QVector3D position(-s + 2 * s / (x-1) * i,
                                   -s + 2 * s / (y-1) * j,
                                   -s + 2 * s / (z-1) * k);
                QVector3D color(0, 1, 0);
                mPoint p;
                p.pos = position;
                p.oriPos = position;
                p.color = color;
                pp.append(p);
            }
            ppp.append(pp);
        }
        mPoints.append(ppp);
    }
}

QVector3D controlPoint::getPosition(int x, int y, int z) {
    QVector3D result;
    result = mPoints[x][y][z].pos;
    return result;
}

int controlPoint::get_x() {
    return num_x;
}

int controlPoint::get_y() {
    return num_y;
}

int controlPoint::get_z() {
    return num_z;
}

float controlPoint::getSize() {
    return size;
}

void controlPoint::updateControlPoint(int x, int y, int z) {
    num_x = x;
    num_y = y;
    num_z = z;
    float s = 0.5;
    mPoints.clear();
    for(int i=0;i<x;i++) {
        QVector<QVector<mPoint> > ppp;
        for(int j=0;j<y;j++) {
            QVector<mPoint> pp;
            for(int k=0;k<z;k++) {
                QVector3D position(-s + 2 * s / (x-1) * i,
                                   -s + 2 * s / (y-1) * j,
                                   -s + 2 * s / (z-1) * k);
                QVector3D color(0, 1, 0);
                mPoint p;
                p.pos = position;
                p.oriPos = position;
                p.color = color;
                pp.append(p);
            }
            ppp.append(pp);
        }
        mPoints.append(ppp);
    }
}

void controlPoint::updateControlPointPos(QVector3D p, QVector3D delta) {
    mPoints[int(p.x())][int(p.y())][int(p.z())].pos = mPoints[int(p.x())][int(p.y())][int(p.z())].oriPos + delta;
}

void controlPoint::setColor(int x, int y, int z, QVector3D color) {
    mPoints[x][y][z].color = color;
}

QVector3D controlPoint::getColor(int x, int y, int z) {
    return mPoints[x][y][z].color;
}

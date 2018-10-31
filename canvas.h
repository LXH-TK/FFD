#ifndef CANVAS_H
#define CANVAS_H

#include <QMouseEvent>
#include <QGLWidget>
#include <QString>
#include <QVector3D>
#include "objloader.h"
#include "controlpoint.h"

class Canvas : public QGLWidget {
public:
    explicit Canvas(QGLWidget *parent = 0);
    ~Canvas();
    //载入obj文件
    void open(QString fileName);
    //是否显示lines
    void setShowLines();
    //根据Slider的变化调整点
    void updateControlPoint(int x, int y, int z);
    //调整所选控制点
    void updateCurPoint(int x, int y, int z);
    //调整控制点位置
    void updateCurPointPos(int x, int y, int z);
    //调整obj大小
    void setScale(float s);
    //调整obj位置
    void setTranslate(QVector3D t);

private:
    objLoader mobjLoader;
    bool mouse_down;
    QPoint originPoint;
    float rotateX;
    float rotateY;
    bool showLines;
    int numPoint;

    controlPoint *mcontrolPoint;
    //更新obj形状
    void updateobj();
    //更新控制点状态
    void updatepoints(QVector3D mcurPoint, QVector3D p);
    //Bernstein函数
    //参考https://luvinahlc.github.io/2015/11/06/Deformation
    float Bernstein(int L, int i, float x);
    //转化为网格坐标
    QVector3D convert(QVector3D p);
    //转化为世界坐标
    QVector3D revert(QVector3D p);
    QVector3D beginPoint;
    QVector3D curPoint;

    //缩小/移动obj使之在控制点中心
    float scale;
    QVector3D translate;

protected:
    void initializeGL();
    void paintGL();
    //控制物体的旋转
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif // CANVAS_H

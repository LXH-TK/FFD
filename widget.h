#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFileDialog>
#include "canvas.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget {
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_openButton_clicked();
    void on_lineButton_clicked();
    //切分
    void on_xSlider_valueChanged();
    void on_ySlider_valueChanged();
    void on_zSlider_valueChanged();
    //选择控制点
    void on_xspinBox_valueChanged(int);
    void on_yspinBox_valueChanged(int);
    void on_zspinBox_valueChanged(int);
    //控制点坐标移动
    void on_xpointSlider_valueChanged();
    void on_ypointSlider_valueChanged();
    void on_zpointSlider_valueChanged();
    //调整obj
    void on_scaleobjSlider_valueChanged();
    void on_xobjSlider_valueChanged();
    void on_yobjSlider_valueChanged();
    void on_zobjSlider_valueChanged();

private:
    Ui::Widget *ui;
    Canvas mCanvas;
};

#endif // WIDGET_H

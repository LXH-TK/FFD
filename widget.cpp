#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget) {
    ui->setupUi(this);
    ui->layout->addWidget(&mCanvas);
}

Widget::~Widget() {
    delete ui;
}

void Widget::on_openButton_clicked() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("open file"),
                                                    " ",  tr("obj_file(*.obj)"));
    mCanvas.open(fileName);
}

void Widget::on_lineButton_clicked() {
    if(ui->lineButton->text() == "不显示线框") {
        mCanvas.setShowLines();
        ui->lineButton->setText("显示线框");
    }
    else {
        mCanvas.setShowLines();
        ui->lineButton->setText("不显示线框");
    }
}

void Widget::on_xSlider_valueChanged() {
    ui->xValue->setText(QString::number(ui->xSlider->value()));
    mCanvas.updateControlPoint(ui->xSlider->value(), ui->ySlider->value(), ui->zSlider->value());
}

void Widget::on_ySlider_valueChanged() {
    ui->yValue->setText(QString::number(ui->ySlider->value()));
    mCanvas.updateControlPoint(ui->xSlider->value(), ui->ySlider->value(), ui->zSlider->value());
}

void Widget::on_zSlider_valueChanged() {
    ui->zValue->setText(QString::number(ui->zSlider->value()));
    mCanvas.updateControlPoint(ui->xSlider->value(), ui->ySlider->value(), ui->zSlider->value());
}

void Widget::on_xspinBox_valueChanged(int) {
    mCanvas.updateCurPoint(ui->xspinBox->value(), ui->yspinBox->value(), ui->zspinBox->value());
    ui->xpointSlider->setValue(50);
    ui->ypointSlider->setValue(50);
    ui->zpointSlider->setValue(50);
}

void Widget::on_yspinBox_valueChanged(int) {
    mCanvas.updateCurPoint(ui->xspinBox->value(), ui->yspinBox->value(), ui->zspinBox->value());
    ui->xpointSlider->setValue(50);
    ui->ypointSlider->setValue(50);
    ui->zpointSlider->setValue(50);
}

void Widget::on_zspinBox_valueChanged(int) {
    mCanvas.updateCurPoint(ui->xspinBox->value(), ui->yspinBox->value(), ui->zspinBox->value());
    ui->xpointSlider->setValue(50);
    ui->ypointSlider->setValue(50);
    ui->zpointSlider->setValue(50);
}

void Widget::on_xpointSlider_valueChanged() {
    mCanvas.updateCurPointPos(ui->xpointSlider->value(), ui->ypointSlider->value(), ui->zpointSlider->value());
}

void Widget::on_ypointSlider_valueChanged() {
    mCanvas.updateCurPointPos(ui->xpointSlider->value(), ui->ypointSlider->value(), ui->zpointSlider->value());
}

void Widget::on_zpointSlider_valueChanged() {
    mCanvas.updateCurPointPos(ui->xpointSlider->value(), ui->ypointSlider->value(), ui->zpointSlider->value());
}

void Widget::on_scaleobjSlider_valueChanged() {
    mCanvas.setScale((ui->scaleobjSlider->value()+50) / 100.0);
}

void Widget::on_xobjSlider_valueChanged() {
    mCanvas.setTranslate(QVector3D((ui->xobjSlider->value()-50) / 100.0,
                                   (ui->yobjSlider->value()-50) / 100.0,
                                   (ui->zobjSlider->value()-50) / 100.0));
}

void Widget::on_yobjSlider_valueChanged() {
    mCanvas.setTranslate(QVector3D((ui->xobjSlider->value()-50) / 100.0,
                                   (ui->yobjSlider->value()-50) / 100.0,
                                   (ui->zobjSlider->value()-50) / 100.0));
}


void Widget::on_zobjSlider_valueChanged() {
    mCanvas.setTranslate(QVector3D((ui->xobjSlider->value()-50) / 100.0,
                                   (ui->yobjSlider->value()-50) / 100.0,
                                   (ui->zobjSlider->value()-50) / 100.0));
}

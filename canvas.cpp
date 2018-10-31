#include "canvas.h"

Canvas::Canvas(QGLWidget *parent) : QGLWidget(parent) {
    mouse_down = false;
    rotateX = rotateY = 0;
    mcontrolPoint = new controlPoint();
    curPoint = QVector3D(0, 0, 0);
    mcontrolPoint->setColor(0, 0, 0, QVector3D(1, 0, 0));
    scale = 1.0;
    translate = QVector3D(0 ,0, 0);
    showLines = true;
    numPoint = 8;
}

void Canvas::open(QString fileName) {
    mobjLoader = objLoader(fileName.toStdString());
}

void Canvas::setShowLines() {
    showLines = !showLines;
    updateGL();
}

Canvas::~Canvas() {
}

void Canvas::initializeGL() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glEnable(GL_DEPTH_TEST);

    GLfloat light_position[] = { 0.4, 0.5, -0.8, 0.0 };
    GLfloat light_ambient [] = { 0.8, 0.4, 0.8, 1.0 };
    GLfloat light_diffuse [] = { 0.5, 0.6, 1.0, 1.0 };
    GLfloat light_specular[] = { 0.8, 0.8, 0.8, 1.0 };

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT , light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE , light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
}

void glQuad(QVector3D A, QVector3D B, QVector3D C, QVector3D D) {
    glBegin(GL_QUADS);
    glVertex3f(A.x(), A.y(), A.z());
    glVertex3f(B.x(), B.y(), B.z());
    glVertex3f(C.x(), C.y(), C.z());
    glVertex3f(D.x(), D.y(), D.z());
    glEnd();
}

void Canvas::paintGL() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glRotatef(rotateX, 1, 0, 0);
    glRotatef(rotateY, 0, 1, 0);

    //draw lines
    glLineWidth(2.0f);
    glColor3d(0.5, 0.5, 0.5);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    int X = mcontrolPoint->get_x();
    int Y = mcontrolPoint->get_y();
    int Z = mcontrolPoint->get_z();
    //基础点八个
    QVector3D A = mcontrolPoint->getPosition(0, 0, 0);
    QVector3D B = mcontrolPoint->getPosition(0, 0, Z-1);
    QVector3D C = mcontrolPoint->getPosition(0, Y-1, Z-1);
    QVector3D D = mcontrolPoint->getPosition(0, Y-1, 0);
    QVector3D E = mcontrolPoint->getPosition(X-1, 0, 0);
    QVector3D F = mcontrolPoint->getPosition(X-1, 0, Z-1);
    QVector3D G = mcontrolPoint->getPosition(X-1, Y-1, Z-1);
    QVector3D H = mcontrolPoint->getPosition(X-1, Y-1, 0);
    if(showLines) {
        //其他点
        for(int i=1;i<X-1;i++) {
            QVector3D temp1 = mcontrolPoint->getPosition(i, 0, 0);
            QVector3D temp2 = mcontrolPoint->getPosition(i, 0, Z-1);
            QVector3D temp3 = mcontrolPoint->getPosition(i, Y-1, Z-1);
            QVector3D temp4 = mcontrolPoint->getPosition(i, Y-1, 0);
            glQuad(temp1, temp2, temp3, temp4);
        }
        for(int i=1;i<Y-1;i++) {
            QVector3D temp1 = mcontrolPoint->getPosition(0, i, 0);
            QVector3D temp2 = mcontrolPoint->getPosition(0, i, Z-1);
            QVector3D temp3 = mcontrolPoint->getPosition(X-1, i, Z-1);
            QVector3D temp4 = mcontrolPoint->getPosition(X-1, i, 0);
            glQuad(temp1, temp2, temp3, temp4);
        }
        for(int i=1;i<Z-1;i++) {
            QVector3D temp1 = mcontrolPoint->getPosition(0, 0, i);
            QVector3D temp2 = mcontrolPoint->getPosition(X-1, 0, i);
            QVector3D temp3 = mcontrolPoint->getPosition(X-1, Y-1, i);
            QVector3D temp4 = mcontrolPoint->getPosition(0, Y-1, i);
            glQuad(temp1, temp2, temp3, temp4);
        }
    }
    //基础线框
    glQuad(A, B, C, D);
    glQuad(B, F, G, C);
    glQuad(C, G, H, D);
    glQuad(D, H, E, A);
    glQuad(E, F, B, A);
    glQuad(F, E, H, G);
    //draw points
    glPointSize(10.0f);
    glBegin(GL_POINTS);
    for(int i=0;i<mcontrolPoint->get_x();i++) {
        for(int j=0;j<mcontrolPoint->get_y();j++) {
            for(int k=0;k<mcontrolPoint->get_z();k++) {
                glColor3d(mcontrolPoint->getColor(i, j, k).x(),
                          mcontrolPoint->getColor(i, j, k).y(),
                          mcontrolPoint->getColor(i, j, k).z());
                glVertex3f(mcontrolPoint->getPosition(i, j, k).x(),
                           mcontrolPoint->getPosition(i, j, k).y(),
                           mcontrolPoint->getPosition(i, j, k).z());
            }
        }
    }
    glEnd();
    //draw obj
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glTranslatef(translate.x(), translate.y(), translate.z());
    glScalef(scale, scale, scale);
    mobjLoader.Draw_obj();
}

float Canvas::Bernstein(int L, int i, float x) {
    int p = L - i;
    float q = 1 - x;
    int LL = 1;
    int ii = 1;
    int pp = 1;
    float xi = 1;
    float qp = 1;
    for(int num=1;num<=L;num++){
        if(num <= i) { ii *= num; xi *= x;}
        if(num <= p) { pp *= num; qp *= q;}
        LL *= num;
    }
    float res = (LL*xi*qp) / (ii*pp);
    return res;
}

void Canvas::updateobj() {
    int L = mcontrolPoint->get_x();
    int M = mcontrolPoint->get_y();
    int N = mcontrolPoint->get_z();
    for(int num=0;num<(int)mobjLoader.vSets.size();num++) {
        QVector3D objPoint = convert(QVector3D(
                                         mobjLoader.tempvSets[num][0],
                                         mobjLoader.tempvSets[num][1],
                                         mobjLoader.tempvSets[num][2]));
        QVector3D newPoint = QVector3D(0, 0, 0);
        //求变化后的新坐标
        for(int i=0;i<L;i++)
            for(int j=0;j<M;j++)
                for(int k=0;k<N;k++) {
                    //获取控制点新坐标
                    QVector3D control_cvtP = convert(mcontrolPoint->getPosition(i, j, k));
                    float tempi = Bernstein(L-1, i, objPoint.x());
                    float tempj = Bernstein(M-1, j, objPoint.y());
                    float tempk = Bernstein(N-1, k, objPoint.z());
                    newPoint = newPoint + tempi*tempj*tempk*control_cvtP;
                }
        mobjLoader.vSets[num][0] = revert(newPoint).x();
        mobjLoader.vSets[num][1] = revert(newPoint).y();
        mobjLoader.vSets[num][2] = revert(newPoint).z();
    }
}

//递归
void Canvas::updatepoints(QVector3D mcurPoint, QVector3D p) {
    QVector3D tempCurPoint = mcurPoint;
    for(int i=0;i<mcontrolPoint->get_x();i++)
        for(int j=0;j<mcontrolPoint->get_y();j++)
            for(int k=0;k<mcontrolPoint->get_z();k++) {
                QVector3D tempPoint(i, j, k);
                if(tempPoint != tempCurPoint) {
                    if(i == tempCurPoint.x() && k == tempCurPoint.z() && j != 0 && j != mcontrolPoint->get_y()-1) {
                        mcontrolPoint->updateControlPointPos(tempPoint,
                                                             QVector3D(p.x()*j/(mcontrolPoint->get_x()-1),
                                                                       p.y()*j/(mcontrolPoint->get_y()-1),
                                                                       p.z()*j/(mcontrolPoint->get_z()-1)));
                        updatepoints(tempPoint, QVector3D(p.x()*j/(mcontrolPoint->get_x()-1),
                                                             p.y()*j/(mcontrolPoint->get_y()-1),
                                                             p.z()*j/(mcontrolPoint->get_z()-1)));
                    }
                    if(j == tempCurPoint.y() && k == tempCurPoint.z() && i != 0 && i != mcontrolPoint->get_x()-1) {
                        mcontrolPoint->updateControlPointPos(tempPoint,
                                                             QVector3D(p.x()*i/(mcontrolPoint->get_x()-1),
                                                                       p.y()*i/(mcontrolPoint->get_y()-1),
                                                                       p.z()*i/(mcontrolPoint->get_z()-1)));
                        updatepoints(tempPoint, QVector3D(p.x()*i/(mcontrolPoint->get_x()-1),
                                                             p.y()*i/(mcontrolPoint->get_y()-1),
                                                             p.z()*i/(mcontrolPoint->get_z()-1)));
                    }
                    if(i == tempCurPoint.x() && j == tempCurPoint.y() && k != 0  && k != mcontrolPoint->get_z()-1) {
                        mcontrolPoint->updateControlPointPos(tempPoint,
                                                             QVector3D(p.x()*k/(mcontrolPoint->get_x()-1),
                                                                       p.y()*k/(mcontrolPoint->get_y()-1),
                                                                       p.z()*k/(mcontrolPoint->get_z()-1)));
                        updatepoints(tempPoint, QVector3D(p.x()*k/(mcontrolPoint->get_x()-1),
                                                             p.y()*k/(mcontrolPoint->get_y()-1),
                                                             p.z()*k/(mcontrolPoint->get_z()-1)));
                    }
                }
            }
    updateGL();
}

QVector3D Canvas::convert(QVector3D p) {
    beginPoint = QVector3D(-mcontrolPoint->getSize(),
                           -mcontrolPoint->getSize(),
                           -mcontrolPoint->getSize());
    QVector3D res = (p - beginPoint) / (2 * mcontrolPoint->getSize());
    return res;
}

QVector3D Canvas::revert(QVector3D p) {
    beginPoint = QVector3D(-mcontrolPoint->getSize(),
                           -mcontrolPoint->getSize(),
                           -mcontrolPoint->getSize());
    QVector3D res = beginPoint + 2 * mcontrolPoint->getSize() * p;
    return res;
}

void Canvas::updateControlPoint(int x, int y, int z) {
    mcontrolPoint->updateControlPoint(x, y, z);
    updateGL();
}

void Canvas::updateCurPoint(int x, int y, int z) {
    mcontrolPoint->setColor(curPoint.x(), curPoint.y(), curPoint.z(), QVector3D(0, 1, 0));
    curPoint = QVector3D(x, y, z);
    mcontrolPoint->setColor(curPoint.x(), curPoint.y(), curPoint.z(), QVector3D(1, 0, 0));
    updateGL();
}

void Canvas::updateCurPointPos(int x, int y, int z) {
    mcontrolPoint->updateControlPointPos(curPoint,
                                         QVector3D((x-50)/100.0, (y-50)/100.0, (z-50)/100.0));
    updatepoints(curPoint, QVector3D((x-50)/100.0, (y-50)/100.0, (z-50)/100.0));
    updateobj();
    updateGL();
}

void Canvas::setScale(float s) {
    scale = s;
    updateGL();
}

void Canvas::setTranslate(QVector3D t) {
    translate = t;
    updateGL();
}

void Canvas::mouseMoveEvent(QMouseEvent *event) {
    if(mouse_down == true) {
        float x = event->pos().x() - originPoint.x();
        float y = event->pos().y() - originPoint.y();
        //比例无所谓，只要旋转就行了
        rotateX += y/100;
        rotateY += x/100;
    }
    updateGL();
}

void Canvas::mousePressEvent(QMouseEvent *event) {
    mouse_down = true;
    originPoint = event->pos();
}

void Canvas::mouseReleaseEvent(QMouseEvent *event) {
    mouse_down = false;
}

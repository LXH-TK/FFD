#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <GLUT/GLUT.h>

using namespace std;
typedef vector<GLint> vInfo;

class objLoader {
public:
    objLoader();                        //声明默认构造函数
    objLoader(string filename);
    void Draw_obj();                    //绘制函数
    ~objLoader();
    vector< vector<GLfloat> > vSets;    //存放顶点(x, y, z)坐标
    vector<vector<GLfloat> > tempvSets; //变化后的点，便于恢复
    vector< vector<GLfloat> > vnSets;   //存放顶点法向量坐标
    vector< vector<GLfloat> > vtSets;   //存放纹理坐标
    vector< vector<vInfo> > fSets;      //存放面的顶点索引，GLint[3]中分别是顶点坐标/纹理坐标/法向量坐标
};

#endif // OBJLOADER_H

#include "objloader.h"

objLoader::objLoader() {
}

objLoader::objLoader(string filename) {
    string line;
    fstream f;
    f.open(filename.c_str(), ios::in);
    if(!f.is_open())
        cout << "Something Went Wrong When Opening Objfiles" << endl;

    while(!f.eof()) {
        getline(f, line);                  //拿到obj文件中一行，作为一个字符串
        vector<string>parameters;
        string tailMark = " ";
        string ans = "";                   //申请内存资源但资源空间值为0

        line = line.append(tailMark);
        for(int i=0;i<(int)line.length();i++) {
            char ch = line[i];
            if(ch != ' ')
                ans += ch;
            else {
                parameters.push_back(ans); //取出字符串中的元素，以空格切分
                ans = "";
            }
        }
        if(parameters[0] == "v") {         //顶点
            vector<GLfloat>Point;
            for(int i=1;i<4;i++) {
                //从1开始，将顶点的xyz三个坐标放入顶点vector
                GLfloat xyz = atof(parameters[i].c_str());
                Point.push_back(xyz);
            }
            vSets.push_back(Point);
            tempvSets.push_back(Point);
        }
        else if(parameters[0] == "f") {    //面
            //如果是面的话，存放三/四个顶点的索引
            vector<vInfo>vIndexSets;
            for(int i=1;i<(int)parameters.size();i++) {
                vInfo tmpVInfo;
                string x = parameters[i];
                string ans = "";
                x.append("/");
                for(int j=0;j<(int)x.length();j++) {
                    //跳过‘/’
                    char ch = x[j];
                    if(ch != '/')
                        ans += ch;
                    else {
                        GLint index = atof(ans.c_str());
                        index = (int)index;
                        index--;           //顶点索引在obj文件中是从1开始的，而我们存放的顶点vector是从0开始的，因此要减1
                        tmpVInfo.push_back(index);
                        ans = "";
                    }
                }
                vIndexSets.push_back(tmpVInfo);
            }
            fSets.push_back(vIndexSets);
        }
        else if(parameters[0] == "vn") {
            //法向量坐标，存放在vnSets中
            vector<GLfloat>Normal;
            for(int i=1;i<4;i++) {
                //从1开始，将顶点的xyz三个坐标放入顶点vector
                GLfloat xyz = atof(parameters[i].c_str());
                Normal.push_back(xyz);
            }
            vnSets.push_back(Normal);
        }
        else if(parameters[0] == "vt") {
            //纹理坐标，存放在vtSets中
            vector<GLfloat>Texture;
            for(int i=1;i<3;i++) {
                GLfloat texCord = atof(parameters[i].c_str());
                Texture.push_back(texCord);
            }
            vtSets.push_back(Texture);
        }
    }
    f.close();
}

void objLoader::Draw_obj() {
    for(int i=0;i<(int)fSets.size();i++) {
        vector<vInfo> currentFace = fSets[i];       //当前面
        glBegin(GL_POLYGON);                        //开始绘制
        for(int j=0;j<(int)currentFace.size();j++) {
            //当前面共有currentFace.size()个顶点
            vInfo currentVertex = currentFace[j];
            GLint vIndex = currentVertex[0];        //顶点坐标索引
            GLint vtIndex = currentVertex[1];       //纹理坐标索引
            GLint vnIndex = currentVertex[2];       //法向量坐标索引
            glNormal3f(vnSets[vnIndex][0], vnSets[vnIndex][1], vnSets[vnIndex][2]);
            glTexCoord2f(vtSets[vtIndex][0], vtSets[vtIndex][1]);
            glVertex3f(vSets[vIndex][0], vSets[vIndex][1], vSets[vIndex][2]);
        }
        glEnd();
    }
}

objLoader::~objLoader() {
}

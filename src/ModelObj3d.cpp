#include "ModelObj3d.h"


ModelObj3d::ModelObj3d()
{
    //ctor
}

ModelObj3d::~ModelObj3d()
{
    //dtor
}

void ModelObj3d::loadFile(const char * filename){
    std::string sLine = "";
    std::ifstream infile;

    infile.open(filename);

    while (!infile.eof())
    {
        getline(infile, sLine);
        //std::cout << sLine << std::endl;

        std::size_t found = sLine.find("# ");
        if(found!=std::string::npos){
            continue;
        }

        found = sLine.find("v ");
        if(found!=std::string::npos){
            //std::cout << "v" << std::endl;
            decodeVertice(sLine);
        }

        found = sLine.find("vn ");
        if(found!=std::string::npos){
            decodeNormais(sLine);
        }
        found = sLine.find("vt ");
        if(found!=std::string::npos){
           decodeTexturas(sLine);
        }

        found = sLine.find("f ");
        if(found!=std::string::npos){
            decodeFace(sLine);
        }

        found = sLine.find("g ");
        if(found!=std::string::npos){
            //std::cout << "g" << std::endl;
        }

    }
}

void ModelObj3d::decodeVertice(std::string str){
    int rsize = 0;
    std::string *s = splitchar(str,' ',&rsize);

    if(rsize==4){
        Vector3f vec;
        vec.v[0] = std::atof(s[1].c_str());
        vec.v[1] = std::atof(s[2].c_str());
        vec.v[2] = std::atof(s[3].c_str());

        v.push_back(vec);

        //std::cout << " Vertices " << vec.v[0] << " " << vec.v[1] << " " << vec.v[2] << std::endl;
    }
}

void ModelObj3d::decodeNormais(std::string str){
    int rsize = 0;
    std::string *s = splitchar(str,' ',&rsize);

    if(rsize==4){
        Vector3f vec;
        vec.v[0] = std::atof(s[1].c_str());
        vec.v[1] = std::atof(s[2].c_str());
        vec.v[2] = std::atof(s[3].c_str());

        vn.push_back(vec);

        //std::cout << " Normais "<<vec.v[0] << " " << vec.v[1] << " " << vec.v[2] << std::endl;
    }
}

void ModelObj3d::decodeTexturas(std::string str){
    int rsize = 0;
    std::string *s = splitchar(str,' ',&rsize);

    if(rsize==4){
        Vector3f vec;
        vec.v[0] = std::atof(s[1].c_str());
        vec.v[1] = std::atof(s[2].c_str());
        vec.v[2] = std::atof(s[3].c_str());

        vt.push_back(vec);

        //std::cout << " Texturas "<< vec.v[0] << " " << vec.v[1] << " " << vec.v[2] << std::endl;
    }
}

void ModelObj3d::decodeFace(std::string str){
    int rsize = 0;
    std::string *s = splitchar(str,' ',&rsize);

    //std::cout << "FACE" << rsize <<std::endl;
    if(rsize==5){
        std::cout << "FACE 3" << std::endl;
        Face3D ff;
        ff.nvertices = 3;

        Vector3f vec;
        for(int i = 0; i < 3;i++){
            int rsize2 = 0;
            std::string *s2 = splitchar(s[i+1],'//',&rsize2);

            ff.v[i] = std::atof(s2[0].c_str());
            ff.t[i] = std::atof(s2[1].c_str());
            ff.n[i] = std::atof(s2[2].c_str());

            std::cout << ff.v[i] << " " << ff.n[i] << " " << ff.t[i] << std::endl;
        }

        f.push_back(ff);

        //std::cout << " Texturas "<< vec.v[0] << " " << vec.v[1] << " " << vec.v[2] << std::endl;
    }else if(rsize==6){
        std::cout << "FACE 4" << std::endl;
        Face3D ff;
        ff.nvertices = 4;

        Vector3f vec;
        for(int i = 0; i < 4;i++){
            int rsize2 = 0;
            std::string *s2 = splitchar(s[i+1],'//',&rsize2);

            ff.v[i] = std::atof(s2[0].c_str());
            ff.t[i] = std::atof(s2[1].c_str());
            ff.n[i] = std::atof(s2[2].c_str());

            //std::cout << ff.v[i] << " " << ff.n[i] << " " << ff.t[i] << std::endl;
        }

        f.push_back(ff);
    }
}

void ModelObj3d::draw(){

    for(std::vector<Face3D>::iterator it = f.begin(); it != f.end(); ++it) {
        Face3D ff = (*it);


        glBegin(GL_POLYGON);
            for(int i = 0; i < ff.nvertices; i++){
                Vector3f vv = v.at(ff.v[i]-1);
                Vector3f nn = vn.at(ff.n[i]-1);
                Vector3f tt = vt.at(ff.t[i]-1);

                glNormal3f(nn.v[0], nn.v[1], nn.v[2]);
                //std::cout << "t " << tt.v[0] << " " << tt.v[1] << " " << (ff.t[i]-1) << std::endl;
                glTexCoord2f(tt.v[0], tt.v[1]);
                glVertex3f(vv.v[0], vv.v[1], vv.v[2]);
            }
        /*
            glColor3f(1,0,0);
            glVertex3f(-0.5, -0.5, 1.5);
            glColor3f(1,0,0);
            glVertex3f(-0.5,  0.5, 0.6);
            glColor3f(1,0,0);
            glVertex3f(0.5,  0.5, 1.5);
            glColor3f(1,0,0);
            glVertex3f(0.5, -0.5, 0.6);
            */
        glEnd();
    }
}

std::string *ModelObj3d::splitchar(std::string input,char spchar, int *rsize){
    int coutchar = 0;
    int lastchar = -1;
    for(int i = 0; i < input.size(); i++){
        if(lastchar<(i-1) && input[i]==spchar){
            coutchar++;
            lastchar = i;
        }else if(input[i]==spchar){
            lastchar = i;
        }
    }
    //std::cout << coutchar << std::endl;

    std::string *streturn = new std::string[lastchar+1];

    coutchar = 0;
    lastchar = -1;

    for(int i = 0; i < input.size(); i++){

        if(lastchar<(i-1) && input[i]==spchar){
            streturn[coutchar] = input.substr (lastchar+1,i-(lastchar+1));
            //std::cout << streturn[coutchar] << std::endl;

            coutchar++;
            lastchar = i;

        }else if(input[i]==spchar){
            lastchar = i;
        }

    }
    streturn[coutchar] = input.substr (lastchar+1,(input.size())-(lastchar+1));
    //std::cout << streturn[coutchar] << std::endl;
    *rsize = (coutchar+1);

    return streturn;
}

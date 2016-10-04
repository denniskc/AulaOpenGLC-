#ifndef MODELOBJ3D_H
#define MODELOBJ3D_H

#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "3dObject.h"
#include "GL/gl.h"

typedef struct{
	unsigned char nvertices = 0;
	int v[4];
	int n[4];
	int t[4];
} Face3D;

typedef struct{
	char *nome;
	int finicial;
	int ffinal;
	float size_group[3];
	float menor[3];
	float maior[3];
} GrupoFaces;

typedef struct{
    float v[3];
} Vector3f;

typedef struct{
    float v[2];
} Vector2f;


class ModelObj3d
{
    public:

        std::vector<Vector3f> v;
        std::vector<Vector3f> vn;
        std::vector<Vector3f> vt;
        std::vector<Face3D> f;

        ModelObj3d();
        virtual ~ModelObj3d();
        void loadFile(const char * filename);
        std::string *splitchar(std::string input,char spchar, int *rsize);

        void decodeVertice(std::string str);
        void decodeNormais(std::string str);
        void decodeTexturas(std::string str);
        void decodeFace(std::string str);

        void draw();
        void draw2();

    protected:

    private:
};

#endif // MODELOBJ3D_H

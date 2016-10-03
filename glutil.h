#ifndef GLUTIL_H_INCLUDED
#define GLUTIL_H_INCLUDED

#include<stdio.h>


unsigned char *loadBitmap(const char* filename,int *w,int *h){
    FILE *f;
    f = fopen(filename,"rb");
    if(f!=NULL){
        unsigned char b;
       //while(b!=EOF){
       /*for(int i = 0; i < 100;i++){
            fread(&b,1,1,f);
            printf("%i - %i \n",i,b);
        }*/

        //W 18 int
        //H 22 int
        //DATA byte 54

        unsigned int ww = 0;
        unsigned int hh = 0;

        fseek(f,18,SEEK_SET);

        fread(&ww,4,1,f);
        fread(&hh,4,1,f);
        printf("W %d H %d \n",ww,hh);

        *w = ww;
        *h = hh;

        int datasize = ww*hh*3;
        unsigned char *data = (unsigned char *)malloc(datasize);

        fseek(f,54,SEEK_SET);
        fread(data,datasize,1,f);



        fclose(f);
        return data;
    }else{
        printf("Nao existe o arquivo %s \n",filename);
    }
}

GLuint loadTexture(const char* filename){
    int w = 0;
    int h = 0;

    unsigned char* data = loadBitmap(filename,&w,&h);

    GLuint textureID;
    glGenTextures(1, &textureID);

    glBindTexture(GL_TEXTURE_2D, textureID);

    // Give the image to OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, w, h, 0, 32992, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    return textureID;
}

#endif // GLUTIL_H_INCLUDED

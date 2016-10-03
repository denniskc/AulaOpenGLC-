#include <windows.h>
#include "GL/glut.h"
#include "3DObject.h"
#include <vector>
#include <stdlib.h>
#include "glutil.h"
#include "ModelObj3d.h"

GLuint tex = 0;
GLuint tex2 = 0;
GLuint tex_tanque = 0;
float camerapos = 3;

float ang = 0;
std::vector<gl3dObject *> listaDeObjetos;
ModelObj3d *objfile;

void display()
{
    glLoadIdentity();
    gluLookAt(0, 0, -camerapos, 0, 0, -camerapos+1, 0, 1, 0);

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glDisable(GL_COLOR);
    glEnable(GL_DEPTH_TEST);
    //glDisable(GL_DEPTH_TEST);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex);

    glPushMatrix();

    glRotated(ang,0,1,0);

    glColor3f(1,1,1);

    glBegin(GL_POLYGON);
    glTexCoord2f(0,0);
    glVertex3f(-1.5, -1.5, 1);
    glTexCoord2f(0,1);
    glVertex3f(-1.5,  1.5, 1);
    glTexCoord2f(1,1);
    glVertex3f(1.5,  1.5, 1);
    glTexCoord2f(1,0);
    glVertex3f(1.5, -1.5, 1);

    glEnd();

    glDisable(GL_TEXTURE_2D);
    glEnable(GL_COLOR);

    glBegin(GL_POLYGON);
        glColor3f(1,0,0);
        glVertex3f(-0.5, -0.5, 1.5);
        glColor3f(1,0,0);
        glVertex3f(-0.5,  0.5, 0.6);
        glColor3f(1,0,0);
        glVertex3f(0.5,  0.5, 1.5);
        glColor3f(1,0,0);
        glVertex3f(0.5, -0.5, 0.6);
    glEnd();

    for(std::vector<gl3dObject *>::iterator it = listaDeObjetos.begin(); it != listaDeObjetos.end(); ++it) {
        (*it)->draw();
    }

    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, tex_tanque);
        glScalef(0.01f,0.01f,0.01f);
        objfile->draw();
    glPopMatrix();
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, tex_tanque);
        glTranslatef(2,0,0);
        glScalef(0.01f,0.01f,0.01f);
        objfile->draw();
    glPopMatrix();
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, tex_tanque);
        glTranslatef(0,1.5f,0);
        glScalef(0.01f,0.01f,0.01f);
        objfile->draw();
    glPopMatrix();

    glPopMatrix();


    glFlush();
}

void init()
{
    tex = loadTexture("l2.bmp");
    tex2 = loadTexture("s.bmp");
    tex_tanque = loadTexture("textura-tanque.bmp");

    objfile = new ModelObj3d();
    objfile->loadFile("tank.obj");

    for(int i = 0; i < 1000;i++){
        gl3dObject *objtmp = new gl3dObject((rand()%100)/10.0f-5.0f,(rand()%100)/10.0f-5.0f,(rand()%100)/10.0f-5.0f);
        objtmp->mysize = (rand()%10)/100.0+0.01;
        objtmp->angvel = (rand()%40)/10.0;
        objtmp->tex = tex2;
        listaDeObjetos.push_back(objtmp);
    }

    glClearColor(0.000, 0.0, 0.0, 0.0);

    glColor3f(0.314, 0.314, 0.000);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45, (float)800/ 600, 1, 100);

    glMatrixMode(GL_MODELVIEW);

}

void update(int calbac){
    for(std::vector<gl3dObject *>::iterator it = listaDeObjetos.begin(); it != listaDeObjetos.end(); ++it) {
        (*it)->update();
    }

    glutPostRedisplay();
    glutTimerFunc(5,update,1);
}

void keyboard(unsigned char key, int x, int y)
{
    switch(key) {
        case 'b':
        // call a function
        break;
        case 'w':
            camerapos-=0.2;
        break;
        case 's':
            camerapos+=0.2;
        break;
        case 'a':
            ang-=2;
        break;
        case 'd':
            ang+=2;
        break;
        default:
        break;
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Test");
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    glutTimerFunc(5,update,1);

    init();
    glutMainLoop();
    return 0;
}



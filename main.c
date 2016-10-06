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

void setMaterial(){
    float f[4];
    f[0] = 0.2; f[1] = 0.2; f[2] = 0.2; f[3] = 1;
    glMaterialfv (GL_FRONT, GL_AMBIENT, f);
    f[0] = 0.8; f[1] = 0.8; f[2] = 0.8; f[3] = 1;
    glMaterialfv (GL_FRONT, GL_DIFFUSE, f);
    f[0] = 0.2;     f[1] = 0.2; f[2] = 0.2; f[3] = 1;
    glMaterialfv (GL_FRONT, GL_SPECULAR, f);
    f[0] = 10;     f[1] = 0.2; f[2] = 0.2; f[3] = 1;
    glMaterialfv (GL_FRONT, GL_SHININESS, f);
}

void setaLuz(){
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat light_position[] = { 0.0, 0.0, -4.0, 1.0 };
    GLfloat spot_light_position[] = { 0.0, 0.0, 1.0, 1.0 };

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_ambient);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    //glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    //glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER)

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 45.0);
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 2.0);
    glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,spot_light_position);

    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.0);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.0);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.1);


    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);

    setMaterial();

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

}

void display()
{

    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    gluLookAt(0, 0, -camerapos, 0, 0, -camerapos+1, 0, 1, 0);
    glDisable(GL_COLOR);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex);

    glPushMatrix();

    glRotated(ang,0,1,0);
    setaLuz();



    glColor3f(1,1,1);

    glBegin(GL_POLYGON);
    glTexCoord2f(0,0);
    glNormal3f(0,0,-1);
    glVertex3f(-1.5, -1.5, 0);
    glNormal3f(0,0,-1);
    glTexCoord2f(0,1);
    glVertex3f(-1.5,  1.5, 0);
    glNormal3f(0,0,-1);
    glTexCoord2f(1,1);
    glVertex3f(1.5,  1.5, 0);
    glNormal3f(0,0,-1);
    glTexCoord2f(1,0);
    glVertex3f(1.5, -1.5, 0);

    glEnd();

    setMaterial();

    for(std::vector<gl3dObject *>::iterator it = listaDeObjetos.begin(); it != listaDeObjetos.end(); ++it) {
        (*it)->draw();
    }

    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, tex_tanque);
        setMaterial();
        glScalef(0.01f,0.01f,0.01f);
        objfile->draw();
    glPopMatrix();
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, tex_tanque);
        setMaterial();
        glTranslatef(2,0,0);
        glScalef(0.01f,0.01f,0.01f);
        objfile->draw2();
    glPopMatrix();
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, tex_tanque);
        setMaterial();
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

    glColor3f(0.300, 0.314, 0.000);

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



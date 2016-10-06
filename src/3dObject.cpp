#include "3dObject.h"
#include "GL/gl.h"

gl3dObject::gl3dObject()
{
    x = 0;
    y = 0;
    z = 0;
    ang = 0;
    mysize = 1.2;
    angvel = 1;
}

gl3dObject::gl3dObject(float x,float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
    mysize = 1;
    ang = 0;
    angvel = 1;
}

gl3dObject::~gl3dObject()
{
    //dtor
}

void gl3dObject::update()
{
    ang+=angvel;
}
void gl3dObject::draw()
{

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex);

    glPushMatrix();

    glTranslatef(x,y,z);
    glScaled(mysize,mysize,mysize);
    glRotated(ang,0,1,0);

    glColor3f(1,1,1);
    glBegin(GL_POLYGON);
        glNormal3f(0,0,1);
        glTexCoord2f(0,0);
        glVertex3f(-1.0,-1.0,0);
        glNormal3f(0,0,1);
        glTexCoord2f(0,1);
        glVertex3f(-1.0,+1.0,0);
        glNormal3f(0,0,1);
        glTexCoord2f(1,1);
        glVertex3f(+1.0,+1.0,0);
        glNormal3f(0,0,1);
        glTexCoord2f(1,0);
        glVertex3f(+1.0,-1.0,0);
    glEnd();
    glPopMatrix();
}



#ifndef GL3DOBJECT_H
#define GL3DOBJECT_H


class gl3dObject
{
    public:
        float x,y,z;
        float ang;
        float mysize;
        float angvel;
        int tex;

        gl3dObject();
        gl3dObject(float x,float y, float z);
        virtual ~gl3dObject();

        void update();
        void draw();

    protected:

    private:
};

#endif // 3DOBJECT_H

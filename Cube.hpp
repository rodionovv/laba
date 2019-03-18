#include <GL/gl.h>

class Cube {
public:
    static void setMode(GLenum Mode);
    void draw();
    Cube(GLfloat x, GLfloat y, GLfloat z, int len, GLenum mode);
    Cube() = default;
private:
    static GLenum mode;
    GLfloat x, y, z;
    int EDGE_LENGTH;
};
//
// Created by wasya on 16.03.2019.
//

#include <GL/gl.h>
#include "Cube.hpp"

void Cube::draw() {

    GLfloat left = this->x - EDGE_LENGTH / 2;
    GLfloat  right = left + EDGE_LENGTH;
    GLfloat bottom = this->y - EDGE_LENGTH / 2;
    GLfloat top = bottom + EDGE_LENGTH;
    GLfloat back = this->z - EDGE_LENGTH / 2;
    GLfloat front  = back + EDGE_LENGTH;


    GLfloat vertices[] = {
            //face
            left, top, front,
            right, top, front,
            right, bottom ,front,
            left, bottom, front,

            // back
            left, top, back,
            right, top, back,
            right, bottom, back,
            left, bottom, back,


            //left
            left, top, front,
            left, top, back,
            left, bottom, back,
            left, bottom, front,

            //right
            right, top, front,
            right, top, back,
            right, bottom, back,
            right, bottom, front,

            //top
            left, top, front,
            left, top, back,
            right, top, back,
            right, top, front,

            //bottom
            left, bottom, front,
            left, bottom, back,
            right, bottom, back,
            right, bottom, front,

    };

    GLfloat color[] = {
//red
            1, 0, 0,
            1, 0, 0,
            1, 0 ,0,
            1, 0, 0,
//green
            0.5, 0.5, 0.5,
            0.5, 0.5, 0.5,
            0.5, 0.5, 0.5,
            0.5, 0.5, 0.5,
//blue
            0, 0, 1,
            0, 0, 1,
            0, 0 ,1,
            0, 0, 1,
//yellow
            1, 1, 0,
            1, 1, 0,
            1, 1 ,0,
            1, 1, 0,
//pink
            1, 0, 1,
            1, 0, 1,
            1, 0 ,1,
            1, 0, 1,
//blue!
            0, 1, 1,
            0, 1, 1,
            0, 1 ,1,
            0, 1, 1,


    };

    glPolygonMode(GL_FRONT_AND_BACK,mode);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glDrawArrays(GL_QUADS, 0, 24);
    glColorPointer(3, GL_FLOAT, 0, color);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

}

Cube::Cube(GLfloat x, GLfloat y, GLfloat z, int len, GLenum mode) {
    this->y = y;
    this->z = z;
    this->x = x;
    this->EDGE_LENGTH = len;
    this->mode = mode;

}

void Cube::setMode(GLenum Mode) {
    mode = Mode;
}
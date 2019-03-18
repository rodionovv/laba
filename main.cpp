#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <iostream>
#include "Cube.hpp"

using namespace std;

GLint WIDTH = 640, HEIGHT  = 480;
GLfloat Xratio = 0.5, Yratio = 0.5, x, y, curX, curY;
int type = -1;
GLfloat rotationX = 0.0f;
GLfloat rotationY = 0.0f;


void cursor_callback(GLFWwindow* window, double xpos, double ypos){

    if(xpos -  curX != 0) rotationY -= 0.5;
    else rotationY += 0.5;
    if(ypos > curY) rotationX -= 0.5;
    else  rotationX += 0.5;

    if (rotationX == 360) rotationX = 0;
    if (rotationX == -360) rotationX = 0;

    if (rotationY == 360) rotationX = 0;
    if (rotationY == -360) rotationX = 0;


    curX = xpos;
    curY = ypos;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    switch (button) {
        case (GLFW_MOUSE_BUTTON_LEFT):
            if (action == GLFW_PRESS) {
                glfwSetCursorPosCallback(window, cursor_callback);
                curY = y;
                curX = x;
            }
            if (action == GLFW_RELEASE) {
                type = -1;
                glfwSetCursorPosCallback(window, NULL);
                Yratio = (GLfloat) y / HEIGHT;
                Xratio = (GLfloat) x / WIDTH;
            }
    }
}


static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    else if ((key == GLFW_KEY_UP || key == GLFW_KEY_W)){
        switch (action) {
            case GLFW_PRESS:
                rotationX -= 10;
                break;
            case GLFW_REPEAT:
                rotationX -= 10;
                break;
        }
    } else if (key == GLFW_KEY_DOWN || key == GLFW_KEY_S){
        switch (action) {
            case GLFW_PRESS:
                rotationX += 10;
                break;
            case GLFW_REPEAT:
                rotationX += 10;
                break;
        }
    } else if (key == GLFW_KEY_LEFT || key == GLFW_KEY_A) {
        switch (action) {
            case GLFW_PRESS:
                rotationY -= 10;
                break;
            case GLFW_REPEAT:
                rotationY -= 10;
                break;
        }
    } else if (key == GLFW_KEY_RIGHT || key == GLFW_KEY_D){
        switch (action) {
            case GLFW_PRESS:
                rotationY += 10;
                break;
            case GLFW_REPEAT:
                rotationY += 10;
                break;
        }
    } else if (key == GLFW_KEY_Q && action == GLFW_PRESS){
        Cube::setMode(GL_FILL);

    }
}


void window_size_callback(GLFWwindow* window, GLint width, GLint height) {
    WIDTH = width;
    HEIGHT = height;
    glViewport(0.0, 0.0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, 0, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    x = width * Xratio;
    y = height * Yratio;
    glfwSwapBuffers(window);
}


int main() {

    if (!glfwInit()){
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "window", NULL, NULL);
    if (!window){
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetKeyCallback(window, key_callback);
    glfwSetWindowSizeCallback(window, window_size_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwMakeContextCurrent(window);


    glViewport(0.0, 0.0, WIDTH, HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, WIDTH, 0, HEIGHT, 0, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    x = WIDTH  * Xratio;
    y = HEIGHT * Yratio;
    GLenum mode = GL_FILL;

    while(!glfwWindowShouldClose(window)){

        glPushMatrix();
        glTranslatef(WIDTH / 2, HEIGHT / 2, -500);
        glRotatef(rotationX, 1, 0, 0);
        glRotatef(rotationY, 0, 1, 0);
        glTranslatef(- WIDTH / 2, - HEIGHT / 2, 500);
        glScalef(1, 1, 1);


        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Cube cube(x, y, -500, 200, mode);
        cube.draw();

        glPopMatrix();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

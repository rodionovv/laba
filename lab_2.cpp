#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <imgui.h>

#include "imgui_impl_glfw.h"

#define PI 3.14
using namespace std;


GLint WIDTH = 640, HEIGHT  = 480, EDGE_LENGTH = 100, x, y;
GLfloat Xratio = 0.5, Yratio = 0.5;
int type = -1;
float color[36][3];


void make_color(){
    for (int i = 0; i < 36; i++){
        for (int j = 0; j < 36; j++){
            float c = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            color[i][j] = c;
        }
    }
}

void color_rotate(){
    float r = color[35][0], g = color[35][1], b = color[35][2];
    for (int i = 35; i > 0; i--){
        for (int j = 0; j < 3; j++){
            color[i][j] = color[i - 1][j];
        }
    }
    color[0][0] = r;
    color[0][1] = g;
    color[0][2] = b;
}

void draw(GLfloat w,GLfloat h, int type){

    glClear(GL_COLOR_BUFFER_BIT);

    GLfloat left = w - EDGE_LENGTH / 2;
    GLfloat  right = left + EDGE_LENGTH;
    GLfloat bottom = h - EDGE_LENGTH / 2;
    GLfloat top = bottom + EDGE_LENGTH;

    GLfloat vertices[] = {
            right, top,
            left , top,
            left, bottom,
            right, bottom
    };

    switch(type) {
        case 0: {
            glBegin(GL_LINE_LOOP);
            int j = 0;
            for (GLfloat i = 0.0; i < 2 * PI; i += PI / 18) {
                glColor3f(color[j][0], color[j][1],color[j][2]);
                j++;
                glVertex2f(w + (50 * sqrt(2)) * sin(i), h + (50 * sqrt(2)) * cos(i));
            }
            glEnd();
            glEnableClientState(GL_VERTEX_ARRAY);
            glColor3f(1, 1, 1);
            glVertexPointer(2, GL_FLOAT, 0, vertices);
            glDrawArrays(GL_QUADS, 0, 4);
            glDisableClientState(GL_VERTEX_ARRAY);
            break;
        }
        case 1: {
            glEnableClientState(GL_VERTEX_ARRAY);
            glColor3f(1, 0, 0);
            glVertexPointer(2, GL_FLOAT, 0, vertices);
            glDrawArrays(GL_QUADS, 0, 4);
            glDisableClientState(GL_VERTEX_ARRAY);
            break;
        }
        case 2: {
            color_rotate();
            glBegin(GL_LINE_LOOP);
            int j = 0;
            for (GLfloat i = 0.0; i < 2 * PI; i += PI / 18) {
                glColor3f(color[j][0], color[j][1], color[j][2]);
                j++;
                glVertex2f(w + (50 * sqrt(2)) * sin(i), h + (50 * sqrt(2)) * cos(i));
            }
            glEnd();
            glEnableClientState(GL_VERTEX_ARRAY);
            glColor3f(1, 1, 1);
            glVertexPointer(2, GL_FLOAT, 0, vertices);
            glDrawArrays(GL_QUADS, 0, 4);
            glDisableClientState(GL_VERTEX_ARRAY);
            break;

        }
        default: {
            glEnableClientState(GL_VERTEX_ARRAY);
            glColor3f(1, 1, 1);
            glVertexPointer(2, GL_FLOAT, 0, vertices);
            glDrawArrays(GL_QUADS, 0, 4);
            glDisableClientState(GL_VERTEX_ARRAY);
            break;
        }
    }
}


void cursor_callback(GLFWwindow* window, double xpos, double ypos){
    if (xpos + EDGE_LENGTH / 2 > WIDTH ||
        xpos - EDGE_LENGTH / 2 < 0 ||
        ypos + EDGE_LENGTH / 2 > HEIGHT ||
        ypos - EDGE_LENGTH / 2 < 0) type = 1;
    else {
        x = xpos;
        y = HEIGHT - ypos;
        type = -1;
    }
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    switch (button) {
        case (GLFW_MOUSE_BUTTON_LEFT):
            if (action == GLFW_PRESS) glfwSetCursorPosCallback(window, cursor_callback);
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
    else if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
        make_color();
        type = 0;
    } else if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
        type = -1;
    }else if (key == GLFW_KEY_3 && action == GLFW_PRESS){
        if (type == 2) {
            type = 0;
            glfwSwapInterval(1);
        } else {
            type = 2;
            glfwSwapInterval(25);
        }
    } else if ((key == GLFW_KEY_UP || key == GLFW_KEY_W)){
        type = -1;
        switch (action) {
            case GLFW_PRESS:
                if (y + 10 + EDGE_LENGTH / 2 > HEIGHT) {
                    type = 1;
                }
                else y += 10;
                break;
            case GLFW_REPEAT:
                if (y + 10 + EDGE_LENGTH / 2 > HEIGHT) type = 1;
                else y += 10;
                break;
            case GLFW_RELEASE:
                Yratio = (GLfloat) y / HEIGHT;
        }
    } else if (key == GLFW_KEY_DOWN || key == GLFW_KEY_S){
        type = -1;
        switch (action) {
            case GLFW_PRESS:
                if (y - 10 - EDGE_LENGTH / 2 < 0) type = 1;
                else y -= 10;
                break;
            case GLFW_REPEAT:
                if (y - 10 - EDGE_LENGTH / 2 < 0) type = 1;
                else y -= 10;
                break;
            case GLFW_RELEASE:
                Yratio = (GLfloat) y / HEIGHT;
        }
    } else if (key == GLFW_KEY_LEFT || key == GLFW_KEY_A) {
        type = -1;
        switch (action) {
            case GLFW_PRESS:
                if (x - 10 - EDGE_LENGTH / 2 < 0) type = 1;
                else x -= 10;
                break;
            case GLFW_REPEAT:
                if (x - 10 - EDGE_LENGTH / 2 < 0) type = 1;
                else x -= 10;
                break;
            case GLFW_RELEASE:
                Xratio = (GLfloat) x / WIDTH;
        }
    } else if (key == GLFW_KEY_RIGHT || key == GLFW_KEY_D){
        type = -1;
        switch (action) {
            case GLFW_PRESS:
                if (x + 10 + EDGE_LENGTH / 2 > WIDTH) type = 1;
                else x += 10;
                break;
            case GLFW_REPEAT:
                if (x + 10 + EDGE_LENGTH / 2 > WIDTH) type = 1;
                else x += 10;
                break;
            case GLFW_RELEASE:
                Xratio = (float) x / WIDTH;
        }
    }
}


void window_size_callback(GLFWwindow* window, GLint width, GLint height) {
    WIDTH = width;
    HEIGHT = height;
    glViewport(0.0, 0.0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, 0, 1);
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
    glOrtho(0, WIDTH, 0, HEIGHT, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    x = WIDTH  * Xratio;
    y = HEIGHT * Yratio;

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;



    while(!glfwWindowShouldClose(window)){

        glClear(GL_COLOR_BUFFER_BIT);

        draw(x, y, type);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

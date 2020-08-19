#include <stdlib.h>
#include <stdio.h>
#include "Display.h"

Display::Display(const char* title, int width, int height, int fps_cap) {
    this->title = title;
    this->width = width;
    this->height = height;
    this->fps_cap = fps_cap;
}

void Display::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void Display::errorCallback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

double Display::getTime()
{
    return glfwGetTime();
}

void Display::createWindow() 
{
    glfwSetErrorCallback(errorCallback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 1 );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE ); 

    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetKeyCallback(window, keyCallback);

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glfwSwapInterval(1);

    printf("OpenGL version: %s\n", glGetString(GL_VERSION));

    // TODO(shaw): OpenGL error checks have been omitted 
}

int Display::getWidth() {
    return width;
}

int Display::getHeight() {
    return height;
}

GLFWwindow* Display::getWindow() {
    return window;
}

void Display::update() 
{
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Display::close() 
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

bool Display::windowShouldClose()
{
    return glfwWindowShouldClose(window);
}

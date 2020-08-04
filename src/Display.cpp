#include <stdlib.h>
#include <stdio.h>
#include "Display.h"

Display::Display(const char* title, int width, int height, int fps_cap) {
    m_title = title;
    m_width = width;
    m_height = height;
    m_fpsCap = fps_cap;
}

void Display::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void Display::errorCallback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
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

    m_window = glfwCreateWindow(m_width, m_height, m_title, NULL, NULL);
    if (!m_window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetKeyCallback(m_window, keyCallback);

    glfwMakeContextCurrent(m_window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glfwSwapInterval(1);

    printf("OpenGL version: %s\n", glGetString(GL_VERSION));

    // TODO(shaw): OpenGL error checks have been omitted 
}

void Display::update() 
{
    glfwSwapBuffers(m_window);
}

void Display::close() 
{
    glfwDestroyWindow(m_window);
}

bool Display::windowShouldClose()
{
    return glfwWindowShouldClose(m_window);
}

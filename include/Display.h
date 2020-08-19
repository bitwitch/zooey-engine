#pragma once 
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Display {

private:
    int width;
    int height;
    int fps_cap;
    const char* title;
    GLFWwindow* window;

public:
    Display(const char* title, int width=1280, int height=720, int fps_cap=60);
    bool windowShouldClose();
    void createWindow();
    void update();
    void close();
    double getTime();
    int getWidth();
    int getHeight();
    GLFWwindow* getWindow();

private:
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void errorCallback(int error, const char* description);

};

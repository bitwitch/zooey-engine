#pragma once 
#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct Display {

    int width;
    int height;
    int fps_cap;
    const char* title;
    GLFWwindow* window;

    Display(const char* title, int width=1280, int height=720, int fps_cap=60);
    bool window_should_close();
    void create_window();
    void update();
    void close();
    double get_time();

    // glfw callbacks
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void error_callback(int error, const char* description);

};


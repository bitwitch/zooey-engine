#pragma once 

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Display {

    extern int width;
    extern int height;
    extern int fps_cap;
    extern double last_frame_time;
    extern double current_frame_time;
    extern float frame_dt;
    extern GLFWwindow* window;

    //Display(const char* title, int width=1280, int height=720, int fps_cap=60);
    bool window_should_close();
    void create_window(const char* title);
    void update();
    void update_time();
    void close();
    double get_time();

}

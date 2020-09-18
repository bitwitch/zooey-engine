#include <stdlib.h>
#include <stdio.h>
#include "Display.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

namespace Display {

    int width = 1280;
    int height = 720;
    int fps_cap = 60;
    double last_frame_time = 0;
    double current_frame_time = 0;
    float frame_dt = 0;
    GLFWwindow* window;

    double get_time()
    {
        return glfwGetTime();
    }

    void create_window(const char* title) 
    {
        glfwSetErrorCallback(error_callback);

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

        glfwSetKeyCallback(window, key_callback);

        glfwMakeContextCurrent(window);
        gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        glfwSwapInterval(1);

        printf("OpenGL version: %s\n", glGetString(GL_VERSION));

        // TODO(shaw): OpenGL error checks have been omitted 
    }

    void update_time() {
        current_frame_time = get_time();
        frame_dt = (float)(current_frame_time - last_frame_time);
        last_frame_time = current_frame_time;
    }

    void update() 
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    void close() 
    {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    bool window_should_close()
    {
        return glfwWindowShouldClose(window);
    }

}

#include <stdio.h>
#include <stdlib.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Display.h"

int main(int argc, char** argv) 
{
    Display display = Display("Game Title");
    display.createWindow();
    //Loader loader = Loader();
    //Renderer renderer = Renderer();

    //double lastTime = glfwGetTime();
    //int nbFrames = 0;

    while (!display.windowShouldClose())
    {
        //logSecondsPerFrame(lastTime, nbFrames);

        display.update();

        glfwPollEvents();
    }

    display.close();

    glfwTerminate();
    exit(EXIT_SUCCESS);
}   

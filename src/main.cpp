#include <stdio.h>
#include <stdlib.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Display.h"
#include "Loader.h"
#include "Renderer.h"

int main(int argc, char** argv) 
{
    Display display = Display("Game Title");
    display.createWindow();
    Loader loader = Loader();
    Renderer renderer = Renderer();

    //double lastTime = display.getTime();
    //int nbFrames = 0;

    std::vector<float> vertices = {
        // Left bottom triangle
        -0.5f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        // Right top triangle
        0.5f, -0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f
    };
    
    RawModel model = loader.loadToVAO(vertices);

    while (!display.windowShouldClose())
    {
        //logSecondsPerFrame(lastTime, nbFrames);
        renderer.prepare();
        renderer.render(model);

        display.update();

        glfwPollEvents();
    }

    loader.cleanUp();
    display.close();

    exit(EXIT_SUCCESS);
}   

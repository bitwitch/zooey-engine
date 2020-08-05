#include <stdio.h>
#include <stdlib.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Display.h"
#include "Loader.h"
#include "Renderer.h"
#include "StaticShader.h"

int main(int argc, char** argv) 
{
    Display display = Display("Game Title");
    display.createWindow();
    Loader loader = Loader();
    Renderer renderer = Renderer();
    StaticShader shader = StaticShader();

    //double lastTime = display.getTime();
    //int nbFrames = 0;

    std::vector<float> vertices = {
        -0.5f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.5f, 0.5f, 0.0f
    };

    std::vector<int> indices = {
        0, 1, 3,
        3, 1, 2
    };
    
    RawModel model = loader.loadToVAO(vertices, indices);

    while (!display.windowShouldClose())
    {
        //logSecondsPerFrame(lastTime, nbFrames);
        renderer.prepare();
        shader.start();
        renderer.render(model);
        shader.stop();
        display.update();
    }

    shader.cleanUp();
    loader.cleanUp();
    display.close();

    exit(EXIT_SUCCESS);
}   

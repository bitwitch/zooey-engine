#include <stdio.h>
#include <stdlib.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Display.h"
#include "Loader.h"
#include "ModelTexture.h"
#include "TexturedModel.h"
#include "Renderer.h"
#include "StaticShader.h"

int main(int argc, char** argv) 
{
    Display display = Display("Game Title");
    display.createWindow();
    Loader loader = Loader();
    StaticShader shader = StaticShader();
    Renderer renderer = Renderer(display, shader);

    //double lastTime = display.getTime();
    //int nbFrames = 0;

    std::vector<float> vertices = {
        -0.5f,0.5f,-0.5f,	
        -0.5f,-0.5f,-0.5f,	
        0.5f,-0.5f,-0.5f,	
        0.5f,0.5f,-0.5f,		
        
        -0.5f,0.5f,0.5f,	
        -0.5f,-0.5f,0.5f,	
        0.5f,-0.5f,0.5f,	
        0.5f,0.5f,0.5f,
        
        0.5f,0.5f,-0.5f,	
        0.5f,-0.5f,-0.5f,	
        0.5f,-0.5f,0.5f,	
        0.5f,0.5f,0.5f,
        
        -0.5f,0.5f,-0.5f,	
        -0.5f,-0.5f,-0.5f,	
        -0.5f,-0.5f,0.5f,	
        -0.5f,0.5f,0.5f,
        
        -0.5f,0.5f,0.5f,
        -0.5f,0.5f,-0.5f,
        0.5f,0.5f,-0.5f,
        0.5f,0.5f,0.5f,
        
        -0.5f,-0.5f,0.5f,
        -0.5f,-0.5f,-0.5f,
        0.5f,-0.5f,-0.5f,
        0.5f,-0.5f,0.5f
    };

    std::vector<int> indices = {
        0,1,3,
        3,1,2,
        4,5,7,
        7,5,6,
        8,9,11,
        11,9,10,
        12,13,15,
        15,13,14,
        16,17,19,
        19,17,18,
        20,21,23,
        23,21,22
    };
    
    std::vector<float> tex_coords = {
        0,0,
        0,1,
        1,1,
        1,0,
        0,0,
        0,1,
        1,1,
        1,0,
        0,0,
        0,1,
        1,1,
        1,0,
        0,0,
        0,1,
        1,1,
        1,0,
        0,0,
        0,1,
        1,1,
        1,0,
        0,0,
        0,1,
        1,1,
        1,0
    };

    RawModel model = loader.loadToVAO(vertices, tex_coords, indices);
    ModelTexture texture = ModelTexture(loader.loadTexture("data/boob.jpg"));
    TexturedModel textured_model = TexturedModel(model, texture);

    Entity entity = Entity(textured_model, glm::vec3(0,0,-3));

    Camera camera = Camera();

    while (!display.windowShouldClose())
    {
        //logSecondsPerFrame(lastTime, nbFrames);
        //entity.move(0, 0, -0.01);
        entity.rotate(1, 2, -3);

        camera.move();

        shader.start();
        shader.loadViewMatrix(camera);
        renderer.clear();
        renderer.render(entity, shader);
        shader.stop();
        display.update();
    }

    loader.cleanUp();
    display.close();

    exit(EXIT_SUCCESS);
}   

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
#include "OBJLoader.h"

int main(int argc, char** argv) 
{
    Display display = Display("Game Title");
    display.createWindow();
    Loader loader = Loader();
    StaticShader shader = StaticShader();
    Renderer renderer = Renderer(display, shader);

    //double lastTime = display.getTime();
    //int nbFrames = 0;

    RawModel obj_model = OBJLoader::loadObjModel("stall", loader);
    ModelTexture obj_texture = ModelTexture(loader.loadTexture("data/stall_texture.png"));
    TexturedModel obj_textured_model = TexturedModel(obj_model, obj_texture);
    Entity obj_entity = Entity(obj_textured_model, glm::vec3(0,0,-30));

    Camera camera = Camera();

    while (!display.windowShouldClose())
    {
        //logSecondsPerFrame(lastTime, nbFrames);
        //entity.move(0, 0, -0.01);
        //
        obj_entity.rotate(0, 1, 0);

        camera.move();

        shader.start();
        shader.loadViewMatrix(camera);
        renderer.clear();
        renderer.render(obj_entity, shader);
        shader.stop();
        display.update();
    }

    loader.cleanUp();
    display.close();

    exit(EXIT_SUCCESS);
}   

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
#include "Light.h"

int main(int argc, char** argv) 
{
    Display display = Display("Game Title");
    display.createWindow();
    Loader loader = Loader();
    StaticShader shader = StaticShader();
    Renderer renderer = Renderer(display, shader);

    //double lastTime = display.getTime();
    //int nbFrames = 0;

    RawModel model = OBJLoader::loadObjModel("dragon", loader);
    ModelTexture texture = ModelTexture(loader.loadTexture("data/cream.png"));
    TexturedModel textured_model = TexturedModel(model, texture);
    texture.setShineDamper(10);
    texture.setReflectivity(1);

    Entity entity = Entity(textured_model, glm::vec3(0,-5,-30));

    Light light = Light(glm::vec3(200,200,100), glm::vec3(1,1,1));

    Camera camera = Camera(display.getWindow());

    while (!display.windowShouldClose())
    {
        //logSecondsPerFrame(lastTime, nbFrames);
        //entity.move(0, 0, -0.01);
        //
        entity.rotate(0, 1, 0);

        camera.move();

        shader.start();
        shader.loadViewMatrix(camera);
        shader.loadLight(light);
        renderer.clear();
        renderer.render(entity, shader);
        shader.stop();
        display.update();
    }

    loader.cleanUp();
    display.close();

    exit(EXIT_SUCCESS);
}   

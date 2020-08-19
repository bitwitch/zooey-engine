#include <stdio.h>
#include <stdlib.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Display.h"
#include "Loader.h"
#include "ModelTexture.h"
#include "TexturedModel.h"
#include "MasterRenderer.h"
#include "StaticShader.h"
#include "OBJLoader.h"
#include "Light.h"
#include "Random.h"

int main(int argc, char** argv) 
{
    Display display = Display("Game Title");
    display.createWindow();
    Loader loader = Loader();

    //double lastTime = display.getTime();
    //int nbFrames = 0;

    //RawModel model = OBJLoader::loadObjModel("dragon", loader);
    //ModelTexture texture = ModelTexture(loader.loadTexture("cream.png"));
    //TexturedModel textured_model = TexturedModel(model, texture);
    //texture.setShineDamper(10);
    //texture.setReflectivity(1);

    //Entity entity = Entity(textured_model, glm::vec3(0,-5,-30));

    Light light = Light(glm::vec3(3000,2000,3000), glm::vec3(1,1,1));

    Camera camera = Camera(display.getWindow());

    RawModel cube_raw = OBJLoader::loadObjModel("cube", loader);
    ModelTexture cube_texture = ModelTexture(loader.loadTexture("grass_block.png"));
    cube_texture.setShineDamper(10);
    cube_texture.setReflectivity(0.2);
    TexturedModel cube_model = TexturedModel(cube_raw, cube_texture);

    Entity entity = Entity(cube_model, glm::vec3(0,0,-5));

    std::vector<Entity> cubes;
    for (int i=0; i<3000; i++) {
        Entity cube = Entity(cube_model, 
                glm::vec3(Random::integer(-100,100), 
                          Random::integer(-100,100), 
                          Random::integer(-200,200)),
                glm::vec3(Random::integer(0,360),
                          Random::integer(0,360),
                          Random::integer(0,360)));
        cubes.push_back(cube);
    }

    MasterRenderer renderer = MasterRenderer(display);

    while (!display.windowShouldClose())
    {
        //logSecondsPerFrame(lastTime, nbFrames);

        camera.move();

        //for (auto& cube: cubes) {
            //cube.rotate(1,2,3);
            //renderer.processEntity(cube);
        //}
        
        entity.rotate(0, -0.5, 0);
        renderer.processEntity(entity);

        renderer.render(light, camera);

        display.update();
    }

    loader.cleanUp();
    display.close();

    exit(EXIT_SUCCESS);
}   

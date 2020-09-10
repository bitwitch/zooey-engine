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
    Display display = Display("Demo");
    display.createWindow();
    Loader loader = Loader();

    //double lastTime = display.getTime();
    //int nbFrames = 0;

    //Light light = Light(glm::vec3(0,50000,100), glm::vec3(1,1,1));
    Light light = Light(glm::vec3(20000,20000,2000), glm::vec3(1,1,1));

    Camera camera = Camera(display.getWindow());

    // Cubes
    RawModel cube_raw = OBJLoader::loadObjModel("cube", loader);
    ModelTexture cube_texture = ModelTexture(loader.loadTexture("grass_block.png"));
    cube_texture.setShineDamper(35);
    cube_texture.setReflectivity(0.2);
    TexturedModel cube_model = TexturedModel(cube_raw, cube_texture);

    std::vector<Entity> cubes;
    for (int i=0; i<1000; i++) {
        Entity cube = Entity(cube_model, 
                glm::vec3(Random::integer(-100,100), 
                          Random::integer(0,100), 
                          Random::integer(-200,200)),
                glm::vec3(Random::integer(0,360),
                          Random::integer(0,360),
                          Random::integer(0,360)));
        cubes.push_back(cube);
    }

    // Dragons
    RawModel dragon_raw = OBJLoader::loadObjModel("dragon", loader);
    ModelTexture dragon_texture = ModelTexture(loader.loadTexture("bronze.png"));
    dragon_texture.setShineDamper(10);
    dragon_texture.setReflectivity(0.85);
    TexturedModel dragon_model = TexturedModel(dragon_raw, dragon_texture);
    Entity dragon = Entity(dragon_model, glm::vec3(-30, 0, -50), glm::vec3(0, 0, 0));


    // Terrain
    ModelTexture terrain_texture = ModelTexture(loader.loadTexture("grass.png"));
    //ModelTexture terrain_texture2 = ModelTexture(loader.loadTexture("ground_grass_gen_10.png"));
    Terrain terrain1 = Terrain(0, 0, loader, terrain_texture);
    Terrain terrain2 = Terrain(0, 1, loader, terrain_texture);
    Terrain terrain3 = Terrain(1, 0, loader, terrain_texture);
    Terrain terrain4 = Terrain(1, 1, loader, terrain_texture);

    MasterRenderer renderer = MasterRenderer(display);

    while (!display.windowShouldClose())
    {
        //logSecondsPerFrame(lastTime, nbFrames);

        camera.move();

        renderer.processTerrain(terrain1);
        renderer.processTerrain(terrain2);
        renderer.processTerrain(terrain3);
        renderer.processTerrain(terrain4);

        //for (auto& cube: cubes) {
            //cube.rotate(1,2,3);
            //renderer.processEntity(cube);
        //}

        dragon.rotate(0,1,0);
        renderer.processEntity(dragon);
       
        renderer.render(light, camera);

        display.update();
    }

    loader.cleanUp();
    display.close();

    exit(EXIT_SUCCESS);
}   

#include <stdio.h>
#include <stdlib.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Display.h"
#include "Entity.h"
#include "Player.h"
#include "Terrain.h"
#include "Loader.h"
#include "ModelTexture.h"
#include "TexturedModel.h"
#include "MasterRenderer.h"
#include "StaticShader.h"
#include "OBJLoader.h"
#include "Light.h"
#include "Random.h"
#include "Maths.h"

int main(int argc, char** argv) 
{
    //Display display = Display("Demo");
    Display::create_window("Zooey");

    Loader loader = Loader();

    Light light = Light(glm::vec3(20000,20000,2000), glm::vec3(1,1,1));

    Camera camera = Camera(Display::window);

    // Cubes
    RawModel cube_raw = OBJLoader::loadObjModel("cube", loader);
    //ModelTexture cube_texture = ModelTexture(loader.loadTexture("grass_block.png"));
    ModelTexture cube_texture = ModelTexture(loader.loadTexture("error_texture.png"));
    cube_texture.setShineDamper(20);
    cube_texture.setReflectivity(0.4);
    TexturedModel cube_model = TexturedModel(cube_raw, cube_texture);

    std::vector<Entity> cubes;
    std::vector<glm::vec3> cube_starts;
    std::vector<glm::vec3> cube_targets;
    std::vector<glm::vec3> cube_rotations;

    for (int i=0; i<13; i++) {
        for (int j=0; j<13; j++) {
            for (int k=0; k<13; k++) {
                Entity cube = Entity(cube_model, glm::vec3(-3*i, 3*j+2, -3*k));
                cubes.push_back(cube);
                cube_starts.push_back(cube.getPosition());
                cube_targets.push_back(glm::vec3(Random::integer(-200, 200), 
                                                  Random::integer(2, 200), 
                                                  Random::integer(0, -200)));
                cube_rotations.push_back(glm::vec3(Random::integer(0, 360), 
                                                   Random::integer(0, 360), 
                                                   Random::integer(0, 360)));
            }
        }
    }

    // Dragon
    RawModel dragon_raw = OBJLoader::loadObjModel("dragon", loader);
    ModelTexture dragon_texture = ModelTexture(loader.loadTexture("bronze.png"));
    dragon_texture.setShineDamper(10);
    dragon_texture.setReflectivity(0.85);
    TexturedModel dragon_model = TexturedModel(dragon_raw, dragon_texture);
    Player dragon = Player(Display::window, dragon_model, 
                           glm::vec3(-30, 0, -50), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));


    // Terrain
    ModelTexture terrain_texture = ModelTexture(loader.loadTexture("grass.png"));
    //ModelTexture terrain_texture2 = ModelTexture(loader.loadTexture("ground_grass_gen_10.png"));
    Terrain terrain1 = Terrain(0, 0, loader, terrain_texture);
    Terrain terrain2 = Terrain(0, 1, loader, terrain_texture);
    Terrain terrain3 = Terrain(1, 0, loader, terrain_texture);
    Terrain terrain4 = Terrain(1, 1, loader, terrain_texture);

    MasterRenderer renderer = MasterRenderer(Display::width, Display::height);

    // random demo variables
    bool reset = false;
    bool explode = false;
    bool rotated = false;
    float explosion_speed = 0.05f;
    bool cube_mode = true; // false == dragon_mode
    bool dragon_rotate = false;
    GLFWwindow* window = Display::window;


    bool was_key_7 = false;
    bool was_key_6 = false;
    while (!Display::window_should_close())
    {
        //logSecondsPerFrame(lastTime, nbFrames);
        Display::update_time();

        if (glfwGetKey(window, GLFW_KEY_7)) {
            if (!was_key_7) {
                cube_mode = !cube_mode;
                reset = true;
            }
            was_key_7 = true;
        } else {
            was_key_7 = false;
        }

        if (glfwGetKey(window, GLFW_KEY_0))
            reset = true;

        if (reset) {
            explode = false;
            rotated = false;
            reset = false;
            dragon_rotate = false;
            for (int i=0; i<cubes.size(); i++) { 
                auto& cube = cubes[i];
                auto start = cube_starts[i];
                cube.position = start;
                cube.rotation = glm::vec3(0,0,0);
            }
        }

        if (glfwGetKey(window, GLFW_KEY_8))
            explode = true;

        if (glfwGetKey(window, GLFW_KEY_6)) {
            if (!was_key_6)
                dragon_rotate = !dragon_rotate;
            was_key_6 = true;
        } else {
            was_key_6 = false;
        }

        camera.move(Display::frame_dt);

        renderer.processTerrain(terrain1);
        renderer.processTerrain(terrain2);
        renderer.processTerrain(terrain3);
        renderer.processTerrain(terrain4);

        if (explode && !rotated) {
            for (int i=0; i<cubes.size(); i++) { 
                auto& cube = cubes[i];
                cube.rotation = cube_rotations[i];
            }
            rotated = true;
        }

        if (cube_mode) {
            for (int i=0; i<cubes.size(); i++) { 
                auto& cube = cubes[i];
                if (explode) {
                    auto target = cube_targets[i];
                    glm::vec3 movement = (target - cube.getPosition()) * explosion_speed;
                    cube.move(movement);
                    cube.rotate(1, 2, 3);
                }
                renderer.processEntity(cube);
            }
        } else {
            dragon.move(Display::frame_dt);
            if (dragon_rotate) 
                dragon.rotate(0,1,0);
            renderer.processEntity(dragon);
        }

        renderer.render(light, camera);

        Display::update();
    }

    loader.cleanUp();

    Display::close();

    exit(EXIT_SUCCESS);
}   

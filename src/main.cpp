#include <stdio.h>
#include <stdlib.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "display.h"
#include "entity.h"
#include "terrain.h"
#include "loader.h"
#include "model_texture.h"
#include "textured_model.h"
#include "master_renderer.h"
#include "static_shader.h"
#include "obj_loader.h"
#include "light.h"
#include "random.h"
#include "maths.h"

int main(int argc, char** argv) 
{
    Display display = Display("Demo");
    display.create_window();
    Loader loader = Loader();

    //double lastTime = display.getTime();
    //int nbFrames = 0;

    Light light = Light(glm::vec3(20000,20000,2000), glm::vec3(1,1,1));

    Camera camera = Camera(display.window);

    // Cubes
    Raw_Model cube_raw = load_obj_model("cube", &loader);
    //Model_Texture cube_texture = Model_Texture(loader.load_texture("grass_block.png"));
    Model_Texture cube_texture = Model_Texture(loader.load_texture("error_texture.png"));
    cube_texture.shine_damper = 20;
    cube_texture.reflectivity = 0.4;
    Textured_Model cube_model = Textured_Model(&cube_raw, &cube_texture);

    std::vector<Entity> cubes;
    std::vector<glm::vec3> cube_starts;
    std::vector<glm::vec3> cube_targets;
    std::vector<glm::vec3> cube_rotations;

    for (int i=0; i<13; i++) {
        for (int j=0; j<13; j++) {
            for (int k=0; k<13; k++) {
                Entity cube = Entity(&cube_model, glm::vec3(-3*i, 3*j+2, -3*k));
                cubes.push_back(cube);
                cube_starts.push_back(cube.position);
                cube_targets.push_back(glm::vec3(Random::integer(-200, 200), 
                                                  Random::integer(2, 200), 
                                                  Random::integer(0, -200)));
                cube_rotations.push_back(glm::vec3(Random::integer(0, 360), 
                                                   Random::integer(0, 360), 
                                                   Random::integer(0, 360)));
            }
        }
    }

    // Dragons
    Raw_Model dragon_raw = load_obj_model("dragon", &loader);
    Model_Texture dragon_texture = Model_Texture(loader.load_texture("bronze.png"));
    dragon_texture.shine_damper = 10;
    dragon_texture.reflectivity = 0.85;
    Textured_Model dragon_model = Textured_Model(&dragon_raw, &dragon_texture);
    Entity dragon = Entity(&dragon_model, glm::vec3(-30, 0, -50), glm::vec3(0, 0, 0));


    // Terrain
    Model_Texture terrain_texture = Model_Texture(loader.load_texture("grass.png"));
    //Model_Texture terrain_texture2 = Model_Texture(loader.loadTexture("ground_grass_gen_10.png"));
    Terrain terrain1 = Terrain(0, 0, &loader, &terrain_texture);
    Terrain terrain2 = Terrain(0, 1, &loader, &terrain_texture);
    Terrain terrain3 = Terrain(1, 0, &loader, &terrain_texture);
    Terrain terrain4 = Terrain(1, 1, &loader, &terrain_texture);

    Master_Renderer renderer = Master_Renderer(&display);


    // random demo variables
    bool reset = false;
    bool explode = false;
    bool rotated = false;
    float explosion_speed = 0.05f;
    bool cube_mode = true; // false == dragon_mode
    bool dragon_rotate = false;
    GLFWwindow* window = display.window;



    while (!display.window_should_close())
    {
        //logSecondsPerFrame(lastTime, nbFrames);

        if (glfwGetKey(window, GLFW_KEY_7)) {
            cube_mode = !cube_mode;
            reset = true;
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

        if (glfwGetKey(window, GLFW_KEY_6))
            dragon_rotate = !dragon_rotate;

        camera.move();

        renderer.process_terrain(&terrain1);
        renderer.process_terrain(&terrain2);
        renderer.process_terrain(&terrain3);
        renderer.process_terrain(&terrain4);

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
                    glm::vec3 movement = (target - cube.position) * explosion_speed;
                    cube.move(movement);
                    cube.rotate(glm::vec3(1, 2, 3));
                }
                renderer.process_entity(&cube);
            }
        } else {
            if (dragon_rotate) 
                dragon.rotate(glm::vec3(0,1,0));
            renderer.process_entity(&dragon);
        }

        renderer.render(&light, &camera);

        display.update();
    }

    loader.clean_up();
    display.close();

    exit(EXIT_SUCCESS);
}   

#include <stdio.h>
#include <stdlib.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "display.h"
#include "entity.h"
#include "terrain.h"
#include "loader.h"
#include "input.h"
#include "model_texture.h"
#include "textured_model.h"
#include "master_renderer.h"
#include "static_shader.h"
#include "obj_loader.h"
#include "light.h"
#include "random.h"
#include "maths.h"
#include "player.h"

int main(int argc, char** argv) 
{
    Display display = Display("Messenger");
    display.create_window();

    Loader loader = Loader();

    Input::init(display.window);
    Input input = Input();


    //double lastTime = display.getTime();
    //int nbFrames = 0;

    Light light = Light(glm::vec3(0,20000,20000), glm::vec3(1,1,1));

    Camera camera = Camera(display.window);

    // Player
    Raw_Model player_raw = load_obj_model("cube", &loader);
    Model_Texture player_texture = Model_Texture(loader.load_texture("bronze.png"));
    player_texture.shine_damper = 10;
    player_texture.reflectivity = 0.1;
    Textured_Model player_model = Textured_Model(&player_raw, &player_texture);
    Entity player = Entity(&player_model, glm::vec3(0, 0.5, -20), glm::vec3(0, 0, 0));

    // Terrain
    Model_Texture terrain_texture = Model_Texture(loader.load_texture("grass.png"));
    //Model_Texture terrain_texture2 = Model_Texture(loader.loadTexture("ground_grass_gen_10.png"));
    Terrain terrain1 = Terrain(0, 0, &loader, &terrain_texture);
    Terrain terrain2 = Terrain(0, 1, &loader, &terrain_texture);
    Terrain terrain3 = Terrain(1, 0, &loader, &terrain_texture);
    Terrain terrain4 = Terrain(1, 1, &loader, &terrain_texture);

    Master_Renderer renderer = Master_Renderer(&display);

    while (!display.window_should_close())
    {
        input.update_keyboard(); // needs to happen before Display::update() which polls events

        display.update();

        camera.move();
        update_player(&player, &input, display.frame_dt);

        renderer.process_terrain(&terrain1);
        renderer.process_terrain(&terrain2);
        renderer.process_terrain(&terrain3);
        renderer.process_terrain(&terrain4);

        renderer.process_entity(&player);

        renderer.render(&light, &camera);

        display.swap_buffers();
    }

    loader.clean_up();
    display.close();

    exit(EXIT_SUCCESS);
}   

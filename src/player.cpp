#include "player.h"
#include "entity.h"
#include "input.h"
#include "glm_subset.h"

void update_player(Entity *player, Input *input, float dt) {

    if (input->key_down(KEY_W)) {
        player->move(glm::vec3(0,0,-0.2));
    }
    if (input->key_down(KEY_A)) {
        player->move(glm::vec3(-0.2,0,0));
    }
    if (input->key_down(KEY_S)) {
        player->move(glm::vec3(0,0,0.2));
    }
    if (input->key_down(KEY_D)) {
        player->move(glm::vec3(0.2,0,0));
    }

}

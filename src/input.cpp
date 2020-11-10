#include "input.h"
#include <map>

// scope file
std::map<int, Key> key_glfw_to_native = {
    {GLFW_KEY_ESCAPE, KEY_ESCAPE},
    {GLFW_KEY_SPACE, KEY_SPACE},
    {GLFW_KEY_W, KEY_W},
    {GLFW_KEY_A, KEY_A},
    {GLFW_KEY_S, KEY_S},
    {GLFW_KEY_D, KEY_D},
    {GLFW_KEY_P, KEY_P}
};

// scope export
std::vector<Input*> Input::instances;

Input::Input() {
    for (int i=0; i<KEY_COUNT; i++) {
        keyboard_state[i]      = KEY_STATE_STILL_RELEASED;
        last_keyboard_state[i] = KEY_STATE_STILL_RELEASED;
    }
    instances.push_back(this);
}

void Input::init(GLFWwindow* window) {
    glfwSetKeyCallback(window, key_callback);
}

void Input::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    std::map<int, Key>::iterator it = key_glfw_to_native.find(key);
    if (it == key_glfw_to_native.end())
        return;
        
    Key input_key = it->second;

    for (Input* input: instances) {
        if (action == GLFW_PRESS) {
            input->keyboard_state[input_key] = KEY_STATE_JUST_PRESSED;

        } else if (action == GLFW_REPEAT) {
            input->keyboard_state[input_key] = KEY_STATE_STILL_PRESSED;

        } else if (action == GLFW_RELEASE) {
            input->keyboard_state[input_key] = KEY_STATE_JUST_RELEASED;

        }
    }
}

void Input::update_keyboard() {
    for (int i=0; i<KEY_COUNT; i++) {
        switch(keyboard_state[i]) {
        case KEY_STATE_JUST_PRESSED:
            keyboard_state[i] = KEY_STATE_STILL_PRESSED;
            break;
        case KEY_STATE_JUST_RELEASED:
            keyboard_state[i] = KEY_STATE_STILL_RELEASED;
            break;
        default: 
            break;
        }
    }
}

bool Input::key_down(Key key) {
    return keyboard_state[key] == KEY_STATE_JUST_PRESSED ||
           keyboard_state[key] == KEY_STATE_STILL_PRESSED;
}

bool Input::key_pressed(Key key) {
    return keyboard_state[key] == KEY_STATE_JUST_PRESSED;
}



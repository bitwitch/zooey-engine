#pragma once

#include <GLFW/glfw3.h>
#include <vector>

enum Key {
    KEY_W,
    KEY_A,
    KEY_S,
    KEY_D,
    KEY_P,
    KEY_ESCAPE,
    KEY_SPACE,
    KEY_COUNT
};

enum Key_State { 
    KEY_STATE_JUST_PRESSED,
    KEY_STATE_STILL_PRESSED,
    KEY_STATE_JUST_RELEASED,
    KEY_STATE_STILL_RELEASED,
    KEY_STATE_COUNT
};

struct Input {
    Key_State keyboard_state[KEY_COUNT];
    Key_State last_keyboard_state[KEY_COUNT];
    void update_keyboard();
    bool key_down(Key key);
    bool key_pressed(Key key);

    Input();
    static void init(GLFWwindow* window); // registers glfw key callback
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static std::vector<Input*> instances;
};


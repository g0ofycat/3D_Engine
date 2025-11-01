#pragma once

#include <GLFW/glfw3.h>

#include "./keybind_handler.hpp"
#include "../camera/player_camera_controller.hpp"

// ======= movement_listener =======

class movement_listener
{
private:
    float lastTime;

    keybind_handler &keys;
    player_camera_controller &camera;

public:
    // ======= CONSTRUCTOR =======

    /// @brief Constructor for movement_listener
    /// @param key_handler: The keybind_handler object
    /// @param camera_object: The player_camera_controller object
    movement_listener(keybind_handler &key_handler, player_camera_controller &camera_object)
        : keys(key_handler), camera(camera_object), lastTime(glfwGetTime()) {}

    /// @brief Update the camera based on movement
    void update()
    {
        float now = glfwGetTime();
        float deltaTime = now - lastTime;
        lastTime = now;

        std::vector<int> pressed;

        for (int key : keys.get_valid_keys())
            if (keys.is_key_down(key))
                pressed.push_back(key);

        camera.processKeyboard(pressed, deltaTime);
    }
};
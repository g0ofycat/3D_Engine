#pragma once

#include "./keybind_handler.hpp"
#include "../camera/camera_handler.hpp"

// ======= movement_handler =======

class movement_handler
{
private:
    float lastTime;

    keybind_handler &keys;
    camera_handler &camera;

public:
    // ======= CONSTRUCTOR =======

    /// @brief Constructor for movement_handler
    /// @param key_handler: The keybind_handler object
    /// @param camera_object: The camera_handler object
    movement_handler(keybind_handler &key_handler, camera_handler &camera_object)
        : keys(key_handler), camera(camera_object), lastTime(glfwGetTime()) {}

    /// @brief Update the shader based on movement
    void update()
    {
        float now = glfwGetTime();

        float deltaTime = now - lastTime;

        lastTime = now;

        camera.processKeyboard(
            keys.is_key_down(GLFW_KEY_W),
            keys.is_key_down(GLFW_KEY_A),
            keys.is_key_down(GLFW_KEY_S),
            keys.is_key_down(GLFW_KEY_D),
            deltaTime);
    }
};
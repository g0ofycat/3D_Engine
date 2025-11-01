#pragma once

#include <iostream>
#include <unordered_set>
#include <functional>
#include <vector>

#include <GLFW/glfw3.h>

#include "../screen_class.hpp"

// ======= TYPEDEF =======

typedef std::function<void(int)> callback_func;

// ======= keybind_handler =======

class keybind_handler
{
private:
    std::unordered_set<int> keys_to_track;
    GLFWwindow *current_window;

private:
    /// @brief Key callback
    /// @param window
    /// @param key
    /// @param scancode
    /// @param action
    /// @param mods
    static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
    {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
    }

public:
    // ======= CONSTRUCTOR =======

    /// @brief Constructor for keybind_handler
    /// @param screen: The screen to track
    /// @param tracked_keys: The keys that will be tracked
    keybind_handler(screen_class &screen, const std::vector<int> &tracked_keys)
    {
        current_window = screen.get_window();
        keys_to_track = std::unordered_set<int>(tracked_keys.begin(), tracked_keys.end());

        glfwSetKeyCallback(current_window, key_callback);
    }

    // ======= MAIN API =======

    /// @brief Check if a specific valid key is held down
    /// @param key
    /// @return bool
    bool is_key_down(int key)
    {
        if (keys_to_track.find(key) == keys_to_track.end())
            return false;

        return glfwGetKey(current_window, key) == GLFW_PRESS;
    }
};
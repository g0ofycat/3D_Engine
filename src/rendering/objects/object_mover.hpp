#pragma once

#include <unordered_map>

#include "../graphics/shaders/shader_class.hpp"

// ======= object_mover =======

class object_mover
{
public:
    static float x_offset;
    static float y_offset;

public:
    // ======= MAIN API =======

    /// @brief Move a certain direction
    /// @param dx: X Offset
    /// @param dy: Y Offset
    static void move(float dx, float dy)
    {
        x_offset += dx;
        y_offset += dy;
    }

    /// @brief: Apply the offset to a shader
    /// @param name: Name of the vec3
    /// @param shader
    static void apply(std::string name, shader_class &shader)
    {
        shader.set_uniform3f(name, x_offset, y_offset, 0.0f);
    }

    /// @brief Returns a map of the X and Y coordinates
    /// @return {{"x", x_offset}, {"y", y_offset}}
    static std::unordered_map<std::string, float> get_offset()
    {
        return {{"x", x_offset}, {"y", y_offset}};
    }
};

float object_mover::x_offset = 0.0f;
float object_mover::y_offset = 0.0f;
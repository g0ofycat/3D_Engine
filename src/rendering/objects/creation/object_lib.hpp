#pragma once

#include <vector>
#include <unordered_map>
#include <variant>

// ======= object_lib =======

class object_lib
{
public:
    // ======= 2D SHAPES =======

    /// @brief Triangle object
    /// @return {{"vertices", vertices}, {"colors", colors}, {"texture_coords", texture_coords}, {"count", 3}};
    static std::unordered_map<std::string, std::variant<int, std::vector<float>>> triangle()
    {
        std::vector<float> vertices = {
            0.0f, 0.5f, 0.0f,
            -0.5f, 0.0f, 0.0f,
            0.5f, 0.0f, 0.0f};

        std::vector<float> colors = {
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f};

        std::vector<float> texture_coords = {
            0.5f, 1.0f,
            0.0f, 0.0f,
            1.0f, 0.0f};

        return {{"vertices", vertices}, {"colors", colors}, {"texture_coords", texture_coords}, {"count", 3}};
    }

    /// @brief Square object
    /// @return {{"vertices", vertices}, {"colors", colors}, {"texture_coords", texture_coords}, {"count", 6}};
    static std::unordered_map<std::string, std::variant<int, std::vector<float>>> square()
    {
        std::vector<float> vertices = {
            // first triangle
            -0.5f, 0.5f, 0.0f,  // top-left
            0.5f, 0.5f, 0.0f,   // top-right
            -0.5f, -0.5f, 0.0f, // bottom-left

            // second triangle
            -0.5f, -0.5f, 0.0f, // bottom-left
            0.5f, 0.5f, 0.0f,   // top-right
            0.5f, -0.5f, 0.0f   // bottom-right
        };

        std::vector<float> colors = {
            1.0f, 0.0f, 0.0f, // top-left
            0.0f, 1.0f, 0.0f, // top-right
            0.0f, 0.0f, 1.0f, // bottom-left

            0.0f, 0.0f, 1.0f, // bottom-left
            0.0f, 1.0f, 0.0f, // top-right
            1.0f, 1.0f, 0.0f  // bottom-right
        };

        std::vector<float> texture_coords = {
            0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f};

        return {{"vertices", vertices}, {"colors", colors}, {"texture_coords", texture_coords}, {"count", 6}};
    }

    // ======= 3D SHAPES =======

    /// @brief Cube object
    /// @return {{"vertices", vertices}, {"colors", colors}, {"texture_coords", texture_coords}, {"count", 36}};
    static std::unordered_map<std::string, std::variant<int, std::vector<float>>> cube()
    {
        std::vector<float> vertices = {
            // front
            -0.5f, -0.5f, 0.5f,
            0.5f, -0.5f, 0.5f,
            0.5f, 0.5f, 0.5f,
            0.5f, 0.5f, 0.5f,
            -0.5f, 0.5f, 0.5f,
            -0.5f, -0.5f, 0.5f,

            // back
            -0.5f, -0.5f, -0.5f,
            -0.5f, 0.5f, -0.5f,
            0.5f, 0.5f, -0.5f,
            0.5f, 0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,

            // top
            -0.5f, 0.5f, -0.5f,
            -0.5f, 0.5f, 0.5f,
            0.5f, 0.5f, 0.5f,
            0.5f, 0.5f, 0.5f,
            0.5f, 0.5f, -0.5f,
            -0.5f, 0.5f, -0.5f,

            // bottom
            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, 0.5f,
            0.5f, -0.5f, 0.5f,
            -0.5f, -0.5f, 0.5f,
            -0.5f, -0.5f, -0.5f,

            // right
            0.5f, -0.5f, -0.5f,
            0.5f, 0.5f, -0.5f,
            0.5f, 0.5f, 0.5f,
            0.5f, 0.5f, 0.5f,
            0.5f, -0.5f, 0.5f,
            0.5f, -0.5f, -0.5f,

            // left
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, 0.5f,
            -0.5f, 0.5f, 0.5f,
            -0.5f, 0.5f, 0.5f,
            -0.5f, 0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f};

        std::vector<float> colors = {
            // front: red
            1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,

            // back: green
            0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f,

            // top: blue
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,

            // bottom: yellow
            1.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 0.0f,

            // right: magenta
            1.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 1.0f,

            // left: cyan
            0.0f, 1.0f, 1.0f,
            0.0f, 1.0f, 1.0f,
            0.0f, 1.0f, 1.0f,
            0.0f, 1.0f, 1.0f,
            0.0f, 1.0f, 1.0f,
            0.0f, 1.0f, 1.0f};

        std::vector<float> texture_coords = {
            0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,

            0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,

            0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,

            0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,

            0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,

            0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f};

        return {{"vertices", vertices}, {"colors", colors}, {"texture_coords", texture_coords}, {"count", 36}};
    }
};
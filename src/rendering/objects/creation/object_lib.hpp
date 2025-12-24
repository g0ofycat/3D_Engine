#pragma once

#include <vector>
#include <unordered_map>
#include <variant>

// ======= object macros =======

#define PI 3.1415926f

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

    static std::unordered_map<std::string, std::variant<int, std::vector<float>>> sphere(int lat_segments = 16, int lon_segments = 16)
    {
        std::vector<float> vertices;
        std::vector<float> colors;
        std::vector<float> texture_coords;

        for (int i = 0; i <= lat_segments; ++i)
        {
            float theta = i * PI / lat_segments;
            float sinTheta = sin(theta);
            float cosTheta = cos(theta);

            for (int j = 0; j <= lon_segments; ++j)
            {
                float phi = j * 2.0f * PI / lon_segments;
                float sinPhi = sin(phi);
                float cosPhi = cos(phi);

                float x = cosPhi * sinTheta;
                float y = cosTheta;
                float z = sinPhi * sinTheta;

                vertices.push_back(x * 0.5f);
                vertices.push_back(y * 0.5f);
                vertices.push_back(z * 0.5f);

                colors.push_back((x + 1.0f) / 2.0f);
                colors.push_back((y + 1.0f) / 2.0f);
                colors.push_back((z + 1.0f) / 2.0f);

                texture_coords.push_back(j / (float)lon_segments);
                texture_coords.push_back(i / (float)lat_segments);
            }
        }

        std::vector<float> sphere_vertices;
        std::vector<float> sphere_colors;
        std::vector<float> sphere_texcoords;

        int count = 0;

        for (int i = 0; i < lat_segments; ++i)
        {
            for (int j = 0; j < lon_segments; ++j)
            {
                int first = (i * (lon_segments + 1)) + j;
                int second = first + lon_segments + 1;

                auto add_vertex = [&](int idx)
                {
                    sphere_vertices.push_back(vertices[3 * idx]);
                    sphere_vertices.push_back(vertices[3 * idx + 1]);
                    sphere_vertices.push_back(vertices[3 * idx + 2]);
                    sphere_colors.push_back(colors[3 * idx]);
                    sphere_colors.push_back(colors[3 * idx + 1]);
                    sphere_colors.push_back(colors[3 * idx + 2]);
                    sphere_texcoords.push_back(texture_coords[2 * idx]);
                    sphere_texcoords.push_back(texture_coords[2 * idx + 1]);
                };

                add_vertex(first);
                add_vertex(second);
                add_vertex(first + 1);

                add_vertex(second);
                add_vertex(second + 1);
                add_vertex(first + 1);

                count += 6;
            }
        }

        return {{"vertices", sphere_vertices}, {"colors", sphere_colors}, {"texture_coords", sphere_texcoords}, {"count", count}};
    }
};
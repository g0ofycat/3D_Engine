#pragma once

#include <vector>
#include <variant>

#include "../modifying/object_interface.hpp"

// ======= object_manager =======

class object_manager
{
private:
    std::vector<object_interface> objects;

public:
    // ======= CONSTRUCTOR =======

    /// @brief Constructor for object_manager
    object_manager()
    {
        objects.reserve(10000); // no realloc for 10k obj
    }

    // ======= MAIN API =======

    /// @brief Add a new object to the manager
    /// @param obj: The object to add
    void add_object(object_interface &&obj)
    {
        objects.emplace_back(std::move(obj));
    }

    /// @brief Render all objects
    void render_all()
    {
        for (auto &obj : objects)
            obj.render();
    }

    // ======= UTILITY API =======

    /// @brief Create and add a new object to the manager
    /// @param shader: Reference to the shader
    /// @param mesh: Mesh data containing VAO and vertex count
    /// @return size_t: Index of the created object
    size_t create_new_object(shader_class &shader, const Mesh &mesh)
    {
        objects.emplace_back(shader, mesh);

        return objects.size() - 1;
    }

    /// @brief Get object by index
    /// @param index: Index of the object to retrieve
    /// @return object_interface&: Reference to the object
    object_interface &get_object(size_t index)
    {
        return objects[index];
    }

    /// @brief Creates a new object with mesh data and transformations
    /// @param shader: The shader program to use
    /// @param shapeData: Shape data from object_lib containing vertices, colors, and count
    /// @param pos: Initial position of the object (default: origin)
    /// @param scale: Initial scale of the object (default: 1, 1, 1)
    /// @return size_t: Index of the spawned object
    size_t spawn_object(
        shader_class &shader,
        const std::unordered_map<std::string, std::variant<int, std::vector<float>>> &shapeData,
        const glm::vec3 &pos = {0.0f, 0.0f, 0.0f},
        const glm::vec3 &scale = {1.0f, 1.0f, 1.0f})
    {
        std::vector<float> vertices = std::get<std::vector<float>>(shapeData.at("vertices"));
        std::vector<float> colors = std::get<std::vector<float>>(shapeData.at("colors"));

        int count = std::get<int>(shapeData.at("count"));

        unsigned int vao = vertices_class::create_object(vertices, colors);

        size_t index = create_new_object(shader, Mesh{vao, count});

        objects[index].move_set(pos.x, pos.y, pos.z);

        objects[index].scale_set(scale.x, scale.y, scale.z);

        return index;
    }

    /// @brief Get all objects (read-only)
    /// @return A const reference to the list of objects
    const std::vector<object_interface> &get_objects() const { return objects; }
};
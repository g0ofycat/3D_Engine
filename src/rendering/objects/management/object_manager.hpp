#pragma once

#include <vector>

#include "../modifying/object_interface.hpp"

// ======= object_manager =======

class object_manager
{
private:
    std::vector<object_interface> objects;

public:
    // ======= MAIN API =======

    /// @brief Add a new object to the manager
    /// @param obj: The object to add
    void add_object(object_interface &&obj)
    {
        objects.emplace_back(std::move(obj));
    }

    /*
    /// @brief Update all objects
    void update_all()
    {
        for (auto &obj : objects)
        {

        }
    }
    */

    /// @brief Render all objects
    void render_all()
    {
        for (auto &obj : objects)
            obj.render();
    }

    // ======= UTILITY API =======

    /// @brief Create and add the object to the array
    /// @param shader
    /// @param mesh
    /// @return object_interface&: The created object
    object_interface &create_new_object(shader_class &shader, const Mesh &mesh)
    {
        object_interface obj(shader, mesh);

        objects.emplace_back(std::move(obj));

        return objects.back();
    }

    /// @brief Get all objects (read-only)
    /// @return A const reference to the list of objects
    const std::vector<object_interface> &get_objects() const { return objects; }
};
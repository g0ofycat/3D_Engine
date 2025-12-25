#pragma once

#include <functional>

#include "../../rendering/objects/modifying/object_interface.hpp"

// ======= object_interface =======

class object_interface;

// ======= namespaces =======

using preset_fn = std::function<void(object_interface &)>;

// ======= logic_presets =======

class logic_presets
{
public:
    /// @brief Gravity Preset
    /// @param gravitational_force: How strong gravity is
    /// @param delta_time: Delta time
    /// @return preset_fn: Preset function
    static preset_fn gravity(float gravitational_force, float delta_time)
    {
        return [gravitational_force, delta_time](object_interface &obj)
        {
            obj.velocity_add(0.0f, -gravitational_force / obj.get_mass() * delta_time, 0.0f);
            obj.update_position(delta_time);
        };
    }
};
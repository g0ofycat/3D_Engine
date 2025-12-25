#include "../src/engine/game_engine.hpp"

#include "../src/helpers/logic/logic_presets.hpp"

int main()
{
    game_engine engine(500, 500, "3d-engine", {GLFW_KEY_W, GLFW_KEY_A, GLFW_KEY_S, GLFW_KEY_D, GLFW_KEY_Q, GLFW_KEY_E});

    size_t obj_id = engine.create_new_object(object_lib::sphere(), {2, 2, 2}, {0, 0, 0}, {0, 0, 0});

    engine.run(
        [&engine, obj_id](float delta_time)
        {
            object_interface &obj_1 = engine.get_object(obj_id);

            obj_1.apply_preset(logic_presets::gravity(1.0f, delta_time));
        });

    return 0;
}
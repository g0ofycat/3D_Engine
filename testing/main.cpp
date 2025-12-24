#include "../src/engine/game_engine.hpp"

int main()
{
    game_engine engine(500, 500, "3d-engine", {GLFW_KEY_W, GLFW_KEY_A, GLFW_KEY_S, GLFW_KEY_D, GLFW_KEY_Q, GLFW_KEY_E});

    size_t obj_id = engine.create_new_object(object_lib::sphere(), {1, 1, 1}, {0, 0, 0}, {0, 0, 0});

    engine.run(
        [&engine, obj_id](float delta_time)
        {
            engine.get_object(obj_id).rotate_add(0.1, 0.1, 0.1);
        });

    return 0;
}
#include "../src/engine/game_engine.hpp"

#include "../src/helpers/logic/logic_presets.hpp"

#include "../src/helpers/lib/math_lib.hpp"

#include <vector>

int main()
{
	game_engine engine(500, 500, "3d-engine", {GLFW_KEY_W, GLFW_KEY_A, GLFW_KEY_S, GLFW_KEY_D, GLFW_KEY_Q, GLFW_KEY_E});
	size_t _ = engine.create_new_object(object_lib::sphere(), {1, 1, 1}, {0, 0, 0}, {0, 0, 0});
	engine.run();
	return 0;
}

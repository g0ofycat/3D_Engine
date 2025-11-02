#pragma once

#include <vector>

#include "../rendering/screen/screen_class.hpp"
#include "../rendering/screen/input/keybind_handler.hpp"

#include "../rendering/graphics/vertices_class.hpp"
#include "../rendering/graphics/shaders/shader_class.hpp"

#include "../rendering/objects/management/object_manager.hpp"
#include "../rendering/objects/creation/object_lib.hpp"

#include "../rendering/screen/input/movement_listener.hpp"
#include "../rendering/screen/camera/player_camera_controller.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// ======= game_engine =======

class game_engine
{
private:
    // ======= PLAYER CONTROLS =======

    screen_class screen;
    shader_class shader;
    keybind_handler key_handler;
    player_camera_controller camera;
    movement_listener mover;

    // ======= RENDERING =======

    unsigned int VAO;
    int vertexCount;

private:
    /// @brief Used for window resizing
    /// @param window
    /// @param width
    /// @param height
    static void framebuffer_size_callback(GLFWwindow *window, int width, int height)
    {
        glViewport(0, 0, width, height);

        if (height > 0)
        {
            player_camera_controller *cam = static_cast<player_camera_controller *>(glfwGetWindowUserPointer(window));
            cam->setAspectRatio(width / (float)height);
        }
    }

    /// @brief Setup User Input
    void setup_input()
    {
        glfwSetWindowUserPointer(screen.get_window(), &camera);
        glfwSetInputMode(screen.get_window(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetCursorPosCallback(screen.get_window(), player_camera_controller::mouse_callback);
        glfwSetFramebufferSizeCallback(screen.get_window(), framebuffer_size_callback);
    }

    /// @brief Render 3D World
    void render()
    {
        shader.setMat4("view", camera.getViewMatrix());
        shader.setMat4("projection", camera.getProjectionMatrix());

        world_objects.render_all();
    }

public:
    // ======= WORLD DATA =======

    object_manager world_objects;

public:
    // ======= CONSTRUCTOR =======

    /// @brief Constructor for game_engine
    /// @param width: Starting Width of window
    /// @param height: Starting Height of window
    /// @param title: Title of the window
    /// @param valid_keys: Keys that should be tracked
    game_engine(int width, int height, const char *title, const std::vector<int> &valid_keys)
        : screen(width, height, title),
          shader("../src/rendering/graphics/shaders/glsl_files/vertex_shader.glsl",
                 "../src/rendering/graphics/shaders/glsl_files/fragment_shader.glsl"),
          key_handler(screen, valid_keys),
          camera(),
          mover(key_handler, camera)
    {
        glEnable(GL_DEPTH_TEST);

        setup_input();

        camera.setAspectRatio(static_cast<float>(width) / static_cast<float>(height));
    }

    // ======= OBJECT API =======

    /// @brief Create a new object in the world
    /// @param shapeData: Shape data from object_lib containing vertices, colors, and count
    /// @param scale: Initial scale of the object (default: 1, 1, 1)
    /// @param pos: Initial position of the object (default: origin)
    /// @param rotation: Initial rotation of the object (default: 0.0f, 0.0f, 0.0f)
    /// @return size_t: The ID of the object
    size_t create_new_object(
        const std::unordered_map<std::string, std::variant<int, std::vector<float>>> &shapeData,
        const glm::vec3 &scale = {1.0f, 1.0f, 1.0f},
        const glm::vec3 &pos = {0.0f, 0.0f, 0.0f},
        const glm::vec3 &rotation = {0.0f, 0.0f, 0.0f})
    {
        size_t obj_id = world_objects.spawn_object(shader, shapeData, scale, pos, rotation);

        return obj_id;
    }

    /// @brief Delete a specfic object
    /// @param obj_id: The ID of the object
    void delete_object(size_t obj_id)
    {
        world_objects.delete_object(obj_id);
    }

    /// @brief Clear all objects in the world
    void clear_world()
    {
        world_objects.clear_world();
    }

    // ======= RENDERING API =======

    /// @brief Run the engine loop
    void run()
    {
        shader.use();

        while (!screen.should_close())
        {
            screen.clear();
            mover.update();

            render();

            screen.swap_buffers();
            screen.poll_events();
        }

        screen.destroy();
    }
};
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

    // ======= WORLD DATA =======

    object_manager world_objects;

    // ======= RENDERING =======

    unsigned int VAO;
    int vertexCount;

private:
    /// @brief Setup Scene
    void setup_scene()
    {
        auto square = object_lib::cube();

        std::vector<float> vertices = std::get<std::vector<float>>(square["vertices"]);
        std::vector<float> colors = std::get<std::vector<float>>(square["colors"]);
        vertexCount = std::get<int>(square["count"]);

        VAO = vertices_class::create_object(vertices, colors);

        auto &cubeObj = world_objects.create_new_object(shader, Mesh{VAO, vertexCount});

        glEnable(GL_DEPTH_TEST);
    }

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
        shader.use();

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = camera.getViewMatrix();
        glm::mat4 projection = camera.getProjectionMatrix();

        shader.setMat4("model", model);
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);

        world_objects.render_all();
    }

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
        setup_scene();

        setup_input();

        camera.setAspectRatio(static_cast<float>(width) / static_cast<float>(height));
    }

    // ======= MAIN API =======

    /// @brief Run the engine loop
    void run()
    {
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
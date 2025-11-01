#pragma once

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

// ======= screen_class =======

class screen_class
{
private:
    // ======= WINDOW VARIABLES =======

    int width;
    int height;
    const char *name;

    GLFWwindow *window = nullptr;

public:
    // ======= CONSTRUCTOR =======

    /// @brief Constructor for screen_class
    /// @param window_width
    /// @param window_height
    /// @param window_name
    /// @param fullscreen
    screen_class(int window_width, int window_height, const char *window_name, bool fullscreen)
        : width(window_width), height(window_height), name(window_name)
    {
        if (create_window(fullscreen) != 0)
        {
            throw std::runtime_error("Failed to create window");
        }
    }

    // ======= DESTRUCTOR =======

    /// @brief Destructor
    ~screen_class() { destroy(); }

    // ======= MAIN API =======

    /// @brief Creates a new window
    /// @return int: 0 on success, -1 if something failed
    int create_window(bool fullscreen)
    {
        if (!glfwInit())
            return -1;

        if (window != nullptr)
        {
            std::cout << "create_window(): Window is already initialized";
            return -1;
        }

        GLFWmonitor *monitor = fullscreen ? glfwGetPrimaryMonitor() : nullptr;

        if (fullscreen)
        {
            const GLFWvidmode *mode = glfwGetVideoMode(monitor);
            width = mode->width;
            height = mode->height;
        }

        window = glfwCreateWindow(width, height, name, nullptr, nullptr);

        if (!window)
        {
            glfwTerminate();
            return -1;
        }

        glfwMakeContextCurrent(window);

        if (glewInit() != GLEW_OK)
        {
            std::cerr << "Failed to initialize GLEW\n";
            return -1;
        }

        glViewport(0, 0, width, height);

        return 0;
    }

    // ======= UTILITY API =======

    /// @brief Returns the window
    /// @return GLFWwindow
    GLFWwindow *get_window() const
    {
        return window;
    }

    /// @brief Return screen width
    /// @return int
    int getWidth() const { return width; }

    /// @brief Return screen height
    /// @return int
    int getHeight() const { return height; }

    /// @brief If the window should close
    /// @return bool
    bool should_close() const
    {
        return glfwWindowShouldClose(window);
    }

    /// @brief glfwPollEvents() wrapper
    void poll_events()
    {
        glfwPollEvents();
    }

    /// @brief Wrapper for swap_buffers()
    void swap_buffers()
    {
        glfwSwapBuffers(window);
    }

    /// @brief Clears the color buffer
    /// @param r
    /// @param g
    /// @param b
    void clear(float r = 0.1f, float g = 0.1f, float b = 0.1f)
    {
        glClearColor(r, g, b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    /// @brief Destroys the window
    void destroy()
    {
        if (window)
        {
            glfwDestroyWindow(window);
            glfwTerminate();
            window = nullptr;
        }
    }
};
#pragma once

#include <iostream>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// ======= STRUCTS =======

struct Vec3
{
    float x, y, z;

    /// @brief Vec3 to GLM vec3
    /// @return glm::vec3
    glm::vec3 to_glm() const { return glm::vec3(x, y, z); }

    /// @brief GLM vec3 to Vec3
    /// @param v: const glm::vec3
    /// @return Vec3
    static Vec3 from_glm(const glm::vec3 &v) { return {v.x, v.y, v.z}; }
};

// ======= player_camera_controller =======

class player_camera_controller
{
private:
    Vec3 position;
    Vec3 front;
    Vec3 up;
    Vec3 right;
    Vec3 worldUp;

    float pitch;
    float yaw;

    float speed;
    float sensitivity;

    float lastX = 0;
    float lastY = 0;
    bool firstMouse = true;

    float aspectRatio = 3.0f / 3.0f;

private:
    /// @brief Transform and update vectors
    void updateVectors()
    {
        glm::vec3 direction;

        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

        glm::vec3 frontNorm = glm::normalize(direction);
        glm::vec3 rightNorm = glm::normalize(glm::cross(frontNorm, worldUp.to_glm()));
        glm::vec3 upNorm = glm::cross(rightNorm, frontNorm);

        front = Vec3::from_glm(frontNorm);
        right = Vec3::from_glm(rightNorm);
        up = Vec3::from_glm(upNorm);
    }

    /// @brief Move position along a direction vector
    void move(const Vec3 &direction, float velocity)
    {
        position.x += direction.x * velocity;
        position.y += direction.y * velocity;
        position.z += direction.z * velocity;
    }

public:
    // ======= CONSTRUCTOR =======

    /// @brief Constructor for player_camera_controller
    /// @param pos: Default position
    /// @param upDir: Up direction of the camera
    /// @param yaw_: X axis rotation
    /// @param pitch_: Y axis rotation
    player_camera_controller(Vec3 pos = {0, 0, 3}, Vec3 upDir = {0, 1, 0}, float yaw_ = -90.0f, float pitch_ = 0.0f)
        : position(pos), worldUp(upDir), yaw(yaw_), pitch(pitch_), speed(2.5f), sensitivity(0.1f)
    {
        updateVectors();
    }

    // ======= MAIN API =======

    /// @brief Process keyboard input
    /// @param keysDown
    /// @param deltaTime
    void processKeyboard(const std::vector<int> &keysDown, float deltaTime)
    {
        if (deltaTime <= 0.0f || std::isnan(deltaTime) || std::isinf(deltaTime))
            return;

        float velocity = speed * deltaTime;

        for (int key : keysDown)
        {
            switch (key)
            {
            case GLFW_KEY_W:
                move(front, velocity);
                break;
            case GLFW_KEY_S:
                move(front, -velocity);
                break;
            case GLFW_KEY_A:
                move(right, -velocity);
                break;
            case GLFW_KEY_D:
                move(right, velocity);
                break;
            case GLFW_KEY_Q:
                move(up, velocity);
                break;
            case GLFW_KEY_E:
                move(up, -velocity);
                break;
            default:
                break;
            }
        }
    }

    /// @brief Handler for mouse movement
    /// @param xoffset
    /// @param yoffset
    /// @param constrainPitch
    void processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true)
    {
        yaw += xoffset * sensitivity;
        pitch += yoffset * sensitivity;

        if (constrainPitch)
        {
            pitch = glm::clamp(pitch, -89.0f, 89.0f);
        }

        updateVectors();
    }

    /// @brief Mouse callback for GLFW
    /// @param window: The window to track
    /// @param xpos: Current X position
    /// @param ypos: Current Y position
    static void mouse_callback(GLFWwindow *window, double xpos, double ypos)
    {
        player_camera_controller *cam = static_cast<player_camera_controller *>(glfwGetWindowUserPointer(window));
        if (!cam)
            return;

        if (cam->firstMouse)
        {
            cam->lastX = xpos;
            cam->lastY = ypos;
            cam->firstMouse = false;
        }

        float xoffset = xpos - cam->lastX;
        float yoffset = cam->lastY - ypos;

        cam->lastX = xpos;
        cam->lastY = ypos;

        cam->processMouseMovement(xoffset, yoffset);
    }

    // ======= ASPECT RATIO =======

    /// @brief Set the aspect ratio
    /// @param ratio
    void setAspectRatio(float ratio)
    {
        if (ratio > 0.0f)
            aspectRatio = ratio;
    }

    /// @brief Get the aspect ratio
    /// @return
    float getAspectRatio() const { return aspectRatio; }

    // ======= UTILITY API =======

    /// @brief Get position
    /// @return Vec3
    Vec3 getPosition() const { return position; }

    /// @brief Get front position
    /// @return Vec3
    Vec3 getFront() const { return front; }

    /// @brief Get view matrix
    /// @return glm::mat4
    glm::mat4 getViewMatrix() const
    {
        return glm::lookAt(position.to_glm(),
                           (position.to_glm() + front.to_glm()),
                           up.to_glm());
    }

    /// @brief Get projection matrix
    /// @param fov
    /// @param nearPlane
    /// @param farPlane
    /// @return glm::mat4
    glm::mat4 getProjectionMatrix(float fov = 45.0f, float nearPlane = 0.1f, float farPlane = 100.0f) const
    {
        return glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
    }
};
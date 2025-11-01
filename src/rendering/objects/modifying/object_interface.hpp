#pragma once

#include <unordered_map>

#include "../../graphics/shaders/shader_class.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// ======= STRUCTS =======

struct Mesh
{
    unsigned int VAO;
    int vertexCount;
};

// ======= object_interface =======

class object_interface
{
private:
    glm::vec3 offset{0.0f};
    glm::vec3 scale{1.0f};
    glm::mat4 modelMatrix{1.0f};

    shader_class &shader;
    Mesh mesh;

private:
    /// @brief Update the model matrix based on current transform
    void updateModelMatrix()
    {
        modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::translate(modelMatrix, offset);
        modelMatrix = glm::scale(modelMatrix, scale);
    }

public:
    // ======= CONSTRUCTOR =======

    /// @brief Constructor for object_interface
    /// @param shaderRef: Reference to the shader
    /// @param meshRef: Reference to the mesh
    object_interface(shader_class &shaderRef, const Mesh &meshRef)
        : shader(shaderRef), mesh(meshRef)
    {
        updateModelMatrix();
    }

    // ======= TRANSFORM CONTROL =======

    /// @brief Move the shader a certain direction
    /// @param dx: X Offset
    /// @param dy: Y Offset
    /// @param dz: Z Offset
    void move_shader(float dx, float dy, float dz)
    {
        offset += glm::vec3(dx, dy, dz);
        updateModelMatrix();
    }

    /// @brief Set the shader a certain direction
    /// @param dx: X Offset
    /// @param dy: Y Offset
    /// @param dz: Z Offset
    void move_set(float dx, float dy, float dz)
    {
        offset = glm::vec3(dx, dy, dz);
        updateModelMatrix();
    }

    /// @brief Scale the shader
    /// @param sx: X Scale
    /// @param sy: Y Scale
    /// @param sz: Z Scale
    void scale_set(float sx, float sy, float sz)
    {
        scale = glm::vec3(sx, sy, sz);
        updateModelMatrix();
    }

    // ======= RENDERING =======

    /// @brief Render the object
    void render()
    {
        shader.setMat4("model", modelMatrix);

        glBindVertexArray(mesh.VAO);
        glDrawArrays(GL_TRIANGLES, 0, mesh.vertexCount);
    }

    // ======= UTILITY API =======

    /// @brief Return offset of the current shader
    /// @return const glm::vec3&
    const glm::vec3 &get_offset() const { return offset; }

    /// @brief Return scale of the current shader
    /// @return const glm::vec3&
    const glm::vec3 &get_scale() const { return scale; }
};
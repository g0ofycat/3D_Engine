#pragma once

#include <unordered_map>

#include "../../graphics/shaders/shader_class.hpp"

#include <glm/glm.hpp>

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

    shader_class &shader;
    Mesh mesh;

public:
    // ======= CONSTRUCTOR =======

    /// @brief Constructor for object_interface
    /// @param shaderRef: Reference to the shader
    /// @param meshRef: Reference to the mesh
    object_interface(shader_class &shaderRef, const Mesh &meshRef)
        : shader(shaderRef), mesh(meshRef) {}

    // ======= TRANSFORM CONTROL =======

    /// @brief Move the shader a certain direction
    /// @param dx: X Offset
    /// @param dy: Y Offset
    /// @param dz: Z Offset
    void move_shader(float dx, float dy, float dz)
    {
        offset += glm::vec3(dx, dy, dz);
    }

    /// @brief Scale the shader
    /// @param sx: X Scale
    /// @param sy: Y Scale
    /// @param sz: Z Scale
    void scale_shader(float sx, float sy, float sz)
    {
        scale += glm::vec3(sx, sy, sz);
    }

    // ======= RENDERING =======

    /// @brief Render the object
    void render()
    {
        apply_to_shader();
        glBindVertexArray(mesh.VAO);
        glDrawArrays(GL_TRIANGLES, 0, mesh.vertexCount);
    }

    /// @brief: Apply the scale to a shader
    /// @param name: Name of the vec3
    /// @param shader
    void apply_to_shader()
    {
        shader.setVec3("objPos", offset);
        shader.setVec3("objScale", scale);
    }

    // ======= UTILITY API =======

    /// @brief Return offset of the current shader
    /// @return const glm::vec3&
    const glm::vec3 &get_offset() const { return offset; }

    /// @brief Return scale of the current shader
    /// @return const glm::vec3&
    const glm::vec3 &get_scale() const { return scale; }
};
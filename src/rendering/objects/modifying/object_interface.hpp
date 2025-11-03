#pragma once

#include <unordered_map>

#include "../../graphics/textures/texture_handler.hpp"

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
    glm::vec3 scale{1.0f};
    glm::vec3 offset{0.0f};
    glm::vec3 rotation{0.0f};

    glm::mat4 modelMatrix{1.0f};

    shader_class *shader;
    texture_handler texture;
    Mesh mesh;

private:
    /// @brief Update the model matrix based on current transformations
    void updateModelMatrix()
    {
        modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::translate(modelMatrix, offset);
        modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.x), glm::vec3{1, 0, 0});
        modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3{0, 1, 0});
        modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), glm::vec3{0, 0, 1});
        modelMatrix = glm::scale(modelMatrix, scale);
    }

public:
    // ======= CONSTRUCTOR =======

    /// @brief Constructor for object_interface
    /// @param shaderRef: Reference to the shader
    /// @param meshRef: Reference to the mesh
    object_interface(shader_class &shaderRef, const Mesh &meshRef)
        : shader(&shaderRef), mesh(meshRef)
    {
        updateModelMatrix();
    }

    // ======= TRANSFORM CONTROL =======

    /// @brief Add the shader offset a certain direction
    /// @param dx: X Offset
    /// @param dy: Y Offset
    /// @param dz: Z Offset
    void move_add(float dx, float dy, float dz)
    {
        offset += glm::vec3(dx, dy, dz);
        updateModelMatrix();
    }

    /// @brief Set the shader offset a certain direction
    /// @param dx: X Offset
    /// @param dy: Y Offset
    /// @param dz: Z Offset
    void move_set(float dx, float dy, float dz)
    {
        offset = glm::vec3(dx, dy, dz);
        updateModelMatrix();
    }

    /// @brief Add to a shaders rotation
    /// @param rx: X Rotation
    /// @param ry: Y Rotation
    /// @param rz: Z Rotation
    void rotate_add(float rx, float ry, float rz)
    {
        rotation += glm::vec3(rx, ry, rz);
        updateModelMatrix();
    }

    /// @brief Set a shaders rotation
    /// @param rx: X Rotation
    /// @param ry: Y Rotation
    /// @param rz: Z Rotation
    void rotate_set(float rx, float ry, float rz)
    {
        rotation = glm::vec3(rx, ry, rz);
        updateModelMatrix();
    }

    /// @brief Add to a shaders scale
    /// @param sx: X Scale
    /// @param sy: Y Scale
    /// @param sz: Z Scale
    void scale_add(float sx, float sy, float sz)
    {
        scale += glm::vec3(sx, sy, sz);
        updateModelMatrix();
    }

    /// @brief Set a shaders scale
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
    void render() const
    {
        shader->setMat4("model", modelMatrix);

        texture.bind(0);
        shader->set_uniform1i("texture_diffuse", 0);

        glBindVertexArray(mesh.VAO);
        glDrawArrays(GL_TRIANGLES, 0, mesh.vertexCount);
    }

    // ======= TEXTURING API =======

    /// @brief Applies a image as a texture to the current object
    /// @param image_path: Path to the texture
    void apply_texture(const std::string &image_path) {
        texture.load_image(image_path);
    }

    // ======= UTILITY API =======

    /// @brief Return scale of the current shader
    /// @return const glm::vec3&
    const glm::vec3 &get_scale() const { return scale; }

    /// @brief Return offset of the current shader
    /// @return const glm::vec3&
    const glm::vec3 &get_offset() const { return offset; }

    /// @brief Return rotation of the current shader
    /// @return const glm::vec3 &
    const glm::vec3 &get_rotation() const { return rotation; }

    /// @brief Get the current shader
    /// @return shader_class*
    shader_class *get_shader() const { return shader; }

    /// @brief Get the current mesh
    /// @return const Mesh&
    const Mesh &get_mesh() const { return mesh; }
};
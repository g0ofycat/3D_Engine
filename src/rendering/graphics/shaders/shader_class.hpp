#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// ======= shader_class =======

class shader_class
{
private:
    unsigned int ID;

public:
    // ======= CONSTRUCTOR =======

    /// @brief Constructor for shader_class
    /// @param vertexPath: File path for the vertex code (.glsl)
    /// @param fragmentPath: File path for the fragment code (.glsl)
    shader_class(const char *vertexPath, const char *fragmentPath)
    {
        std::string vertexCode = shader_class::load_shader(vertexPath);
        std::string fragmentCode = shader_class::load_shader(fragmentPath);

        unsigned int vertex, fragment;
        int success;
        char infoLog[512];

        vertex = glCreateShader(GL_VERTEX_SHADER);

        const char *vShaderCode = vertexCode.c_str();
        glShaderSource(vertex, 1, &vShaderCode, nullptr);
        glCompileShader(vertex);
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
            std::cout << "Vertex shader error:\n"
                      << infoLog << std::endl;
        }

        fragment = glCreateShader(GL_FRAGMENT_SHADER);

        const char *fShaderCode = fragmentCode.c_str();
        glShaderSource(fragment, 1, &fShaderCode, nullptr);
        glCompileShader(fragment);
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
            std::cout << "Fragment shader error:\n"
                      << infoLog << std::endl;
        }

        ID = glCreateProgram();

        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);
        glGetProgramiv(ID, GL_LINK_STATUS, &success);

        if (!success)
        {
            glGetProgramInfoLog(ID, 512, nullptr, infoLog);
            std::cout << "Shader linking error:\n"
                      << infoLog << std::endl;
        }

        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    // ======= MAIN API =======

    /// @brief Use the shader program
    void use() const { glUseProgram(ID); }

    /// @brief Destroy the shader program
    void destroy() const { glDeleteProgram(ID); }

    /// @brief Set a matrix
    /// @param name: Name of the matrix
    /// @param mat: The matrix
    void setMat4(const std::string &name, const glm::mat4 &mat) const
    {
        int loc = glGetUniformLocation(ID, name.c_str());
        glUniformMatrix4fv(loc, 1, GL_FALSE, &mat[0][0]);
    }

    /// @brief Set a vec3 uniform
    void set_uniform3f(const std::string &name, float x, float y, float z) const
    {
        int loc = glGetUniformLocation(ID, name.c_str());
        glUniform3f(loc, x, y, z);
    }

    // ======= STATIC METHODS =======

    /// @brief Load shader source from file
    /// @return std::string: Extracted file code
    static std::string load_shader(const std::string &filepath)
    {
        std::ifstream file(filepath);

        if (!file.is_open())
            throw std::runtime_error("Failed to open shader file: " + filepath);

        std::stringstream ss;

        ss << file.rdbuf();

        return ss.str();
    }
};
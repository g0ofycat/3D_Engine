#pragma once

#include <vector>

// ======= vertices_class =======

class vertices_class
{
public:
    // ======= MAIN API =======

    /// @brief Creates a new object using the vertices
    /// @param vertices
    /// @param colors
    /// @return unsigned int: VAO
    static unsigned int create_object(const std::vector<float> &vertices, const std::vector<float> &colors)
    {
        unsigned int VAO, VBO[2];

        glGenVertexArrays(1, &VAO);
        glGenBuffers(2, VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
        glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(float), colors.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        return VAO;
    }
};
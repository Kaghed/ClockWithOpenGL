#include "Rectangle.h"

#include <glm/gtc/type_ptr.hpp>

Rectangle::Rectangle(const std::vector<float>& vertices)
{
    transform = glm::mat4(1.0f);
    vertexCount = vertices.size() / 6;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void Rectangle::transformation(const glm::mat4& mat)
{
    transform = mat;
}

void Rectangle::draw(unsigned int shaderID)
{
    glUseProgram(shaderID);
    int loc = glGetUniformLocation(shaderID, "transform");
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(transform));

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount);
}

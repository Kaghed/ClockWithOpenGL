#pragma once
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>

class Rectangle
{
public:
    Rectangle(const std::vector<float>& vertices);
    void transformation(const glm::mat4& mat);
    void draw(unsigned int shaderID);
private:
    unsigned int VAO, VBO;
    glm::mat4 transform;
    int vertexCount;
};


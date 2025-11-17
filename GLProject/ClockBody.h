#pragma once
#include "Rectangle.h"
#include <glm/glm.hpp>

class ClockBody {
private:
    Rectangle rect;
    glm::mat4 model;

public:
    ClockBody(); 
    void transformation(const glm::mat4& t);
    void draw(unsigned int shaderID);
};

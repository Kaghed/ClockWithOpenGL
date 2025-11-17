#pragma once
#include "Circle.h"
#include <glm/glm.hpp>

class ClockCircle {
private:
    Circle circle;
    glm::mat4 model;

public:
    ClockCircle();
    void transformation(const glm::mat4& t);
    void draw(unsigned int shaderID);
};

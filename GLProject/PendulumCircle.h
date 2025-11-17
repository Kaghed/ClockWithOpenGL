#pragma once
#include <glm/glm.hpp>

class PendulumCircle {
public:
    PendulumCircle();
    ~PendulumCircle();
    void update(float time);
     void draw(unsigned int shaderID);
    glm::mat4 getModelMatrix() const;

private:
    glm::mat4 model;
    unsigned int VAO, VBO;
};

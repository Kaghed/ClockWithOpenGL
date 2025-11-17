#ifndef CLOCKHAND_H
#define CLOCKHAND_H

#include <glad/glad.h>
#include <glm/glm.hpp>

class ClockHand {
public:
    ClockHand(float length, float width, float x = 0.0f, float y = 0.52f, float z = 0.1f);
    void setAngle(float angleRadians);

    void update(float timeSeconds); 
    void draw(unsigned int shaderID, const glm::mat4& viewProj);
private:
    unsigned int VAO, VBO;
    glm::mat4 model;
    float centerX, centerY;

};

#endif

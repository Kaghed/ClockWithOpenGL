#include "PendulumRod.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

PendulumRod::PendulumRod()
    : model(glm::mat4(1.0f))
{
    float w = 0.01f;
    float d = 0.01f;

    float leftX = 0.0f;
    float topY = 0.2f;

    float rightX = 0.1f;
    float bottomY = -0.3f;

    float frontZ = 0.05f;
    float backZ = frontZ+ 2 * d;
    float color = 0.6f;
    float vertices[] = {
        leftX - w, topY,    frontZ,  color, color, color,
        rightX - w, bottomY, frontZ,  color, color, color,
        rightX + w, bottomY, frontZ,  color, color, color,
        leftX - w, topY,    frontZ,  color, color, color,
        rightX + w, bottomY, frontZ,  color, color, color,
        leftX + w, topY,    frontZ,  color, color, color,

        leftX - w, topY,    backZ,   color, color, color,
        rightX + w, bottomY, backZ,   color, color, color,
        rightX - w, bottomY, backZ,   color, color, color,
        leftX - w, topY,    backZ,   color, color, color,
        leftX + w, topY,    backZ,   color, color, color,
        rightX + w, bottomY, backZ,   color, color, color,

        leftX + w, topY,    frontZ,  color, color, color,
        rightX + w, bottomY, frontZ,  color, color, color,
        rightX + w, bottomY, backZ,   color, color, color,
        leftX + w, topY,    frontZ,  color, color, color,
        rightX + w, bottomY, backZ,   color, color, color,
        leftX + w, topY,    backZ,   color, color, color,

        leftX - w, topY,    backZ,   color, color, color,
        rightX - w, bottomY, backZ,   color, color, color,
        rightX - w, bottomY, frontZ,  color, color, color,
        leftX - w, topY,    backZ,   color, color, color,
        rightX - w, bottomY, frontZ,  color, color, color,
        leftX - w, topY,    frontZ,  color, color, color,

        leftX - w, topY,    backZ,   color, color, color,
        leftX - w, topY,    frontZ,  color, color, color,
        leftX + w, topY,    frontZ,  color, color, color,
        leftX - w, topY,    backZ,   color, color, color,
        leftX + w, topY,    frontZ,  color, color, color,
        leftX + w, topY,    backZ,   color, color, color,

        rightX - w, bottomY, frontZ,  color, color, color,
        rightX - w, bottomY, backZ,   color, color, color,
        rightX + w, bottomY, backZ,   color, color, color,
        rightX - w, bottomY, frontZ,  color, color, color,
        rightX + w, bottomY, backZ,   color, color, color,
        rightX + w, bottomY, frontZ,  color, color, color,
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

PendulumRod::~PendulumRod() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void PendulumRod::update(float time) {
    float angle = glm::radians(30.0f) * sin(2.0f * time);
    glm::vec3 pivot(0.0f, 0.2f, 0.0f);
    glm::mat4 swing = glm::translate(glm::mat4(1.0f), pivot)
        * glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 0.0f, 1.0f))
        * glm::translate(glm::mat4(1.0f), -pivot);
    model = swing;
}
glm::mat4 PendulumRod::getModelMatrix() const {
    return model;
}

void PendulumRod::draw(unsigned int shaderID) {
    glUseProgram(shaderID);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

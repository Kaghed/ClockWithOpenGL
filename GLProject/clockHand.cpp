#include "ClockHand.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>

ClockHand::ClockHand(float length, float width, float x, float y, float z)
    : centerX(x), centerY(y)
{
    float vertices[] = {
        0.0f,      -width / 2 + centerY, z,
        length,    -width / 2 + centerY, z,
        length,     width / 2 + centerY, z,
        0.0f,       width / 2 + centerY, z
    };


    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    model = glm::mat4(1.0f);
}

void ClockHand::update(float timeSeconds)
{
    float angle = glm::radians(-6.0f * fmod(timeSeconds, 60.0f));
    float centerY = 0.52f;

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, centerY, 0.0f));      
    model = glm::rotate(model, angle, glm::vec3(0, 0, 1));              
    model = glm::translate(model, glm::vec3(0.0f, -centerY, 0.0f));     
}
void ClockHand::setAngle(float angleRadians)
{
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(centerX, centerY, 0.0f));
    model = glm::rotate(model, angleRadians, glm::vec3(0, 0, 1));
    model = glm::translate(model, glm::vec3(-centerX, -centerY, 0.0f));
}


void ClockHand::draw(unsigned int shaderID, const glm::mat4& viewProj)
{
    glUniform3f(glGetUniformLocation(shaderID, "color"), 1.0f, 0.0f, 0.0f);

    //glUniform3f(glGetUniformLocation(shaderID, "color"), 1.0f, 1.0f, 0.0f); 
    glm::mat4 transform = viewProj * model;
    glUniformMatrix4fv(glGetUniformLocation(shaderID, "transform"), 1, GL_FALSE, glm::value_ptr(transform));



    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glBindVertexArray(0);
}


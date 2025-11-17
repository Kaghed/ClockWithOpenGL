#include "ClockMarks.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>
const float PI = 3.14159265359f;

ClockMarks::ClockMarks(float clockZ)
{
    const int marks = 12;
    float marksVertices[marks * 6];
    float centerY = 0.52f;
    float inner = 0.3f;
    float outer = 0.19f;

    for (int i = 0; i < marks; i++) {
        float theta = 2.0f * PI * i / marks;

        marksVertices[i * 6 + 0] = inner * cos(theta);
        marksVertices[i * 6 + 1] = inner * sin(theta) + centerY;
        marksVertices[i * 6 + 2] = clockZ;

        marksVertices[i * 6 + 3] = outer * cos(theta);
        marksVertices[i * 6 + 4] = outer * sin(theta) + centerY;
        marksVertices[i * 6 + 5] = clockZ;
    }

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(marksVertices), marksVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    model = glm::mat4(1.0f);
}

ClockMarks::~ClockMarks()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void ClockMarks::transformation(const glm::mat4& transform)
{
    model = transform;
}

void ClockMarks::draw(unsigned int shaderID)
{
    glUniformMatrix4fv(glGetUniformLocation(shaderID, "transform"), 1, GL_FALSE, glm::value_ptr(model));
    glBindVertexArray(VAO);
    glDrawArrays(GL_LINES, 0, 24);
    glBindVertexArray(0);
}

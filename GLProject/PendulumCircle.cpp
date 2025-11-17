    #include "PendulumCircle.h"
    #include <glad/glad.h>
    #include <glm/gtc/type_ptr.hpp>
    #include <glm/gtc/matrix_transform.hpp>
    #include <cmath>
    #include <vector>

    const float PI = 3.14159265359f;

    PendulumCircle::PendulumCircle()
        : model(glm::mat4(1.0f))
    {
        float r = 0.05f;
        float depth = 0.01f;


        float rightX = 0.1f;
        float bottomY = -0.3f;
        float frontZ = 0.05f;
        float backZ = frontZ + 0.02f;

        float xCenter = rightX;
        float yCenter = bottomY - r;
        float zCenter = (frontZ + backZ) / 2.0f;

        std::vector<float> vertices;
        int segments = 150;


        for (int i = 0; i < segments; ++i) {
            float angle1 = 2.0f * PI * i / segments;
            float angle2 = 2.0f * PI * (i + 1) / segments;

            float x1 = r * cos(angle1);
            float y1 = r * sin(angle1);
            float x2 = r * cos(angle2);
            float y2 = r * sin(angle2);

            vertices.insert(vertices.end(), {
                xCenter, yCenter, zCenter + depth, 1.0f, 1.0f, 0.0f,
                xCenter + x1, yCenter + y1, zCenter + depth, 1.0f, 1.0f, 0.0f,
                xCenter + x2, yCenter + y2, zCenter + depth, 1.0f, 1.0f, 0.0f
                });
        }

         for (int i = 0; i < segments; ++i) {
            float angle1 = 2.0f * PI * i / segments;
            float angle2 = 2.0f * PI * (i + 1) / segments;

            float x1 = r * cos(angle1);
            float y1 = r * sin(angle1);
            float x2 = r * cos(angle2);
            float y2 = r * sin(angle2);

            vertices.insert(vertices.end(), {
                xCenter, yCenter, zCenter - depth, 1.0f, 1.0f, 0.0f,
                xCenter + x1, yCenter + y1, zCenter - depth, 1.0f, 1.0f, 0.0f,
                xCenter + x2, yCenter + y2, zCenter - depth, 1.0f, 1.0f, 0.0f
                });
        }

  
        for (int i = 0; i <= segments; ++i) {
            float angle = 2.0f * PI * i / segments;
            float x = r * cos(angle);
            float y = r * sin(angle);
                
            vertices.insert(vertices.end(), {
                xCenter + x, yCenter + y, zCenter + depth, 1.0f, 1.0f, 0.0f,
                xCenter + x, yCenter + y, zCenter - depth, 1.0f, 1.0f, 0.0f
                });
        }

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindVertexArray(0);
    }

    PendulumCircle::~PendulumCircle() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }

    void PendulumCircle::update(float time) {
        float angle = glm::radians(30.0f) * sin(2.0f * time);
        glm::vec3 pivot(0.0f, 0.2f, 0.0f);

        glm::mat4 swing = glm::translate(glm::mat4(1.0f), pivot)
            * glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 0.0f, 1.0f))
            * glm::translate(glm::mat4(1.0f), -pivot);

      /*  glm::mat4 tilt = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));*/

        model = swing ;
    }

    glm::mat4 PendulumCircle::getModelMatrix() const {
        return model;
    }

    void PendulumCircle::draw(unsigned int shaderID) {
        glUseProgram(shaderID);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(150 * 6 + 2 * (150 + 1)));
        glBindVertexArray(0);
    }

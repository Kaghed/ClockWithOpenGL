#ifndef CLOCKMARKS_H
#define CLOCKMARKS_H

#include <glad/glad.h>
#include <glm/glm.hpp>

class ClockMarks {
public:
    ClockMarks(float clockZ = 0.088f);
    ~ClockMarks();

    void draw(unsigned int shaderID);
    void transformation(const glm::mat4& transform);

private:
    unsigned int VAO, VBO;
    glm::mat4 model;
};

#endif

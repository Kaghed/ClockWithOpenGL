#include "ClockCircle.h"
#include <cmath>
#include <glm/gtc/type_ptr.hpp>

const float PI = 3.14159265359f;

ClockCircle::ClockCircle()
    : model(glm::mat4(1.0f)),
    circle([]
        {
            std::vector<float> vertices;

            float r = 0.33f;
            int segments = 150;
            float depth = 0.08f;
            
            float centerY =  0.52f;

          
            for (int i = 0; i < segments; ++i) {
                float angle1 = 2.0f * PI * i / segments;
                float angle2 = 2.0f * PI * (i + 1) / segments;

                float x1 = r * cos(angle1);
                float y1 = r * sin(angle1);
                float x2 = r * cos(angle2);
                float y2 = r * sin(angle2);

                vertices.push_back(0.0f);
                vertices.push_back(0.5f);
                vertices.push_back(+depth);
                vertices.push_back(1.0f);
                vertices.push_back(1.0f);
                vertices.push_back(0.0f);   

                vertices.push_back(x1);
                vertices.push_back(y1 + centerY);
                vertices.push_back(+depth);
                vertices.push_back(1.0f);
                vertices.push_back(1.0f);
                vertices.push_back(0.0f);

                vertices.push_back(x2);
                vertices.push_back(y2 + centerY);
                vertices.push_back(+depth);
                vertices.push_back(1.0f);
                vertices.push_back(1.0f);
                vertices.push_back(0.0f);
            }

           
            for (int i = 0; i < segments; ++i) {
                float angle1 = 2.0f * PI * i / segments;
                float angle2 = 2.0f * PI * (i + 1) / segments;

                float x1 = r * cos(angle1);
                float y1 = r * sin(angle1);
                float x2 = r * cos(angle2);
                float y2 = r * sin(angle2);

                vertices.push_back(0.0f);
                vertices.push_back(0.5f);
                vertices.push_back(-depth);
                vertices.push_back(1.0f);
                vertices.push_back(1.0f);
                vertices.push_back(0.0f);

                vertices.push_back(x1);
                vertices.push_back(y1 + centerY);
                vertices.push_back(-depth);
                vertices.push_back(1.0f);
                vertices.push_back(1.0f);
                vertices.push_back(0.0f);
               
                vertices.push_back(x2);
                vertices.push_back(y2 + centerY);
                vertices.push_back(-depth);
                vertices.push_back(1.0f);
                vertices.push_back(1.0f);
                vertices.push_back(0.0f);
            }

            
            for (int i = 0; i <= segments; ++i) {
                float angle = 2.0f * PI * i / segments;
                float x = r * cos(angle);
                float y = r * sin(angle);

               
                vertices.push_back(x);
                vertices.push_back(y + centerY);
                vertices.push_back(+depth);
                vertices.push_back(1.0f);
                vertices.push_back(1.0f);
                vertices.push_back(0.0f);

                vertices.push_back(x);
                vertices.push_back(y + centerY);
                vertices.push_back(-depth);
                vertices.push_back(1.0f);
                vertices.push_back(1.0f);
                vertices.push_back(0.0f);
            }

            return vertices;
        }())
{
}

void ClockCircle::transformation(const glm::mat4& t) {
    model = t;
    circle.transformation(model);
}

void ClockCircle::draw(unsigned int shaderID) {
    circle.draw(shaderID);
}

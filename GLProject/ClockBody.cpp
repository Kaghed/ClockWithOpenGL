#include "ClockBody.h"
#include <glm/gtc/type_ptr.hpp>

float leftX = -0.25f;
float rightX = 0.25f;
float topY = 0.30f;
float bottomY = -0.55f;
float frontZ = 0.05f;
float backZ = -0.05f;

float r = 0.8f, g = 0.2f, b = 0.2f;



ClockBody::ClockBody()
    : model(glm::mat4(1.0f)),

    
    rect({
   
    // Front face (z = +0.05)
leftX,  topY,  frontZ, r, g, b,
leftX, bottomY,  frontZ, r, g, b,
 rightX, bottomY,  frontZ, r, g, b,

leftX,  topY,  frontZ, r, g, b,
 rightX, bottomY,  frontZ, r, g, b,
 rightX,  topY,  frontZ, r, g, b,

 // Back face (-Z)
leftX,  topY, backZ, r, g, b,
 rightX, bottomY, backZ, r, g, b,
leftX, bottomY, backZ, r, g, b,

leftX,  topY, backZ, r, g, b,
 rightX,  topY, backZ, r, g, b,
 rightX, bottomY, backZ, r, g, b,


// Right face (x = +0.25)
 rightX,  topY,  frontZ, r, g, b,
 rightX, bottomY,  frontZ, r, g, b,
 rightX, bottomY, backZ, r, g, b,

 rightX,  topY,  frontZ, r, g, b,
 rightX, bottomY, backZ, r, g, b,
 rightX,  topY, backZ, r, g, b,

 // Left face (x = -0.25)
leftX,  topY, backZ, r, g, b,
leftX, bottomY, backZ, r, g, b,
leftX, bottomY,  frontZ, r, g, b,

leftX,  topY, backZ, r, g, b,
leftX, bottomY,  frontZ, r, g, b,
leftX,  topY,  frontZ, r, g, b,

// Top face (y = +0.30)
leftX,  topY, backZ, r, g, b,  
leftX,  topY,  frontZ, r, g, b,  
 rightX,  topY,  frontZ, r, g, b,  

leftX,  topY, backZ, r, g, b, 
 rightX,  topY,  frontZ, r, g, b,  
 rightX,  topY, backZ, r, g, b,
 // Bottom face (y = -0.55)
leftX, bottomY,  frontZ, r, g, b,  
leftX, bottomY, backZ, r, g, b,  
 rightX, bottomY, backZ, r, g, b,  

leftX, bottomY,  frontZ, r, g, b, 
 rightX, bottomY, backZ, r, g, b,  
 rightX, bottomY,  frontZ, r, g, b, 

        })
{
}

void ClockBody::transformation(const glm::mat4& t) {
    model = t;
    rect.transformation(model);
}

void ClockBody::draw(unsigned int shaderID) {
    rect.draw(shaderID);
}

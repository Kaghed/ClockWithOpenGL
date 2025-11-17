#include <vector>
#include <iostream>
#include <cmath>
#include <math.h>
#include "ClockBody.h"
#include "ClockCircle.h"
#include "ClockHand.h"
#include "ClockMarks.h"
#include "PendulumRod.h"
#include "PendulumCircle.h"
#include "Rectangle.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <learnopengl/shader_s.h>
#include <learnopengl/camera.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

Camera camera(vec3(0.0f, 0.0f, 4.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

void generateMarks(float radius, int marks, float* vertices, float z) {
    for (int i = 0; i < marks; i++) {
        float theta = 2.0f * 3.1415926f * i / marks;
        float inner = radius * 0.85f;
        float outer = radius;
        vertices[i * 6] = inner * cos(theta);
        vertices[i * 6 + 1] = inner * sin(theta);
        vertices[i * 6 + 2] = z;
        vertices[i * 6 + 3] = outer * cos(theta);
        vertices[i * 6 + 4] = outer * sin(theta);
        vertices[i * 6 + 5] = z;
    }
}

void processInput(GLFWwindow* window)
{
    float speed = 2.5f * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main()
{
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Lecture 2", NULL, NULL);
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glEnable(GL_DEPTH_TEST);

    Shader ourShader("./shaders/vs/withTransform.vs", "./shaders/fs/color.fs");

    ClockBody clockBody;
    ClockCircle clockCircle;
    PendulumRod pendulumRod;
    PendulumCircle  pendulumCircle;
    ClockMarks clockMarks;
    ClockHand secondHand(0.28f, 0.01f); 

    ClockHand minuteHand(0.25f, 0.02f);
    ClockHand hourHand(0.18f, 0.025f, 0.0f, 0.52f);



    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    while (!glfwWindowShouldClose(window))
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ourShader.use();

        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / SCR_HEIGHT, 0.1f, 100.0f);

        glm::mat4 circleModel = glm::mat4(1.0f);
        glm::mat4 circleTransform = projection * view * circleModel;
        clockCircle.transformation(circleTransform);
        clockCircle.draw(ourShader.ID);

        glm::mat4 bodyModel = glm::mat4(1.0f);
        glm::mat4 bodyTransform = projection * view * bodyModel;
        clockBody.transformation(bodyTransform);
        clockBody.draw(ourShader.ID);

        pendulumRod.update(glfwGetTime());
        glm::mat4 rodTransform = projection * view * pendulumRod.getModelMatrix();
        glUniformMatrix4fv(glGetUniformLocation(ourShader.ID, "transform"), 1, GL_FALSE, glm::value_ptr(rodTransform));
        pendulumRod.draw(ourShader.ID);

        pendulumCircle.update(glfwGetTime());
        glm::mat4 pcircleTransform = projection * view * pendulumCircle.getModelMatrix();
        glUniformMatrix4fv(glGetUniformLocation(ourShader.ID, "transform"), 1, GL_FALSE, glm::value_ptr(pcircleTransform));
        pendulumCircle.draw(ourShader.ID);


            glm::mat4 marksModel = glm::mat4(1.0f);
        glm::mat4 marksTransform = projection * view * marksModel;
        clockMarks.transformation(marksTransform);
        clockMarks.draw(ourShader.ID);
 

            secondHand.update(glfwGetTime());

        glm::mat4 viewProj = projection * view;
        secondHand.draw(ourShader.ID, viewProj);
     
  
        minuteHand.draw(ourShader.ID, viewProj);
        hourHand.setAngle(glm::radians(90.0f)); 


        hourHand.draw(ourShader.ID, viewProj);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

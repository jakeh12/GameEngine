//
//  main.cpp
//  GameEngine
//
//  Created by Jakub Hladik on 12/28/17.
//  Copyright © 2017 Jakub Hladik. All rights reserved.
//
#include <iostream>

#include <glad/glad.h>
#pragma clang diagnostic ignored "-Wdocumentation"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#pragma clang diagnostic pop

#include "stb_image.h"

#include "Shader.hpp"
#include "Camera.hpp"
#include "Model.hpp"
#include "Terrain.hpp"

const int screenWidth = 800;
const int screenHeight = 600;

Camera camera;

// mouse input callback
void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
    static float lastX = xpos, lastY = ypos;
    float xOffset = (float)(xpos - lastX);
    float yOffset = (float)(lastY - ypos); // reverse y-axis coordinates
    
    // update camera euler angles
    camera.processOrientation(xOffset, yOffset);
    
    lastX = xpos;
    lastY = ypos;
}

// input handling function
void processInput(GLFWwindow *window, float deltaTime)
{
    // if escape is pressed, close the application
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.processPosition(FORWARD, deltaTime);
    
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.processPosition(BACKWARD, deltaTime);
    
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.processPosition(LEFT, deltaTime);
    
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.processPosition(RIGHT, deltaTime);
}

int main(void)
{
    Terrain terrain(10);
    
    // initialize glfw
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    
    // set up opengl core 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    // enable msaa 4x
    glfwWindowHint(GLFW_SAMPLES, 4);
    
    // create a window
    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "GameEngine", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    // set current context to the window
    glfwMakeContextCurrent(window);
    
    // set cursor position callback
    glfwSetCursorPosCallback(window, cursorPositionCallback);
    
    // catch mouse cursor inside the window
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    // initialize glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    
    // enable depth testing
    glEnable(GL_DEPTH_TEST);
    
    // enable alpha blending
    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // load shaders
    Shader shaderProgram("shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl");
    shaderProgram.use();

    // load model
    Model modelData("models/mushroom/mushroom.obj");

    // timing
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    
    // set up camera
    camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);
    glm::mat4 view;
    view = camera.getViewMatrix();
    shaderProgram.setUniform("view", view);
    
    // set up projection matrix
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(60.0f), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
    shaderProgram.setUniform("projection", projection);
    
    glm::vec3 modelPositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };
    
    // main game loop
    while(!glfwWindowShouldClose(window))
    {
        // frame timing
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        // handle input
        processInput(window, deltaTime);
        view = camera.getViewMatrix();
        shaderProgram.setUniform("view", view);
        
        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // render models
        for (int i = 0; i < 10; i++)
        {
            shaderProgram.use();
            glm::mat4 model = glm::mat4();
            model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::translate(model, modelPositions[i]);
            model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));    // it's a bit too big for our scene, so scale it down
            shaderProgram.setUniform("model", model);
            modelData.Draw(shaderProgram);
        }
        
        // swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    // free resources
    glfwTerminate();
    return 0;
}


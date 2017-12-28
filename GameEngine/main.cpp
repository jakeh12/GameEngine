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
#pragma clang diagnostic pop

#include "Shader.hpp"

// input handling function
void processInput(GLFWwindow *window)
{
    // if escape is pressed, close the application
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main(void)
{
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
    
    // create a window
    GLFWwindow* window = glfwCreateWindow(800, 600, "GameEngine", nullptr,
                                          nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    // set current context to the window
    glfwMakeContextCurrent(window);
    
    // initialize glew
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    
    // load shaders
    Shader* aShader = new Shader("shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl");
    std::cout << aShader << std::endl;
    
    // set up viewport size
    glViewport(0, 0, 800, 600);
    
    // timing
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    // main game loop
    while(!glfwWindowShouldClose(window))
    {
        // frame timing
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        // handle input
        processInput(window);

        
        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        // swap buffers
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    
    // free resources
    glfwTerminate();
    return 0;
}


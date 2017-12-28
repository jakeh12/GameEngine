//
//  main.cpp
//  GameEngine
//
//  Created by Jakub Hladik on 12/28/17.
//  Copyright © 2017 Jakub Hladik. All rights reserved.
//
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

// keyboard input callback
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // if escape is pressed, exit the application
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

int main(void)
{
    // initialize glfw
    if (glfwInit() != GLFW_TRUE)
    {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    
    // set up opengl core 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
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
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cout << "Failed to initialize GLEW" << std::endl;
        glfwTerminate();
        return -1;
    }

    // set keyboard input callback
    glfwSetKeyCallback(window, key_callback);
    
    // set up viewport size
    glViewport(0, 0, 800, 600);
    
    // clear the buffer
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    
    // main game loop
    while(!glfwWindowShouldClose(window))
    {
        // check all input events
        glfwPollEvents();
        
        // render
        
        // swap buffers
        glfwSwapBuffers(window);
    }
    
    // free resources
    glfwTerminate();
    return 0;
}


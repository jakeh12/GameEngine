//
//  Shader.hpp
//  GameEngine
//
//  Created by Jakub Hladik on 12/28/17.
//  Copyright © 2017 Jakub Hladik. All rights reserved.
//

#ifndef SHADER_HPP
#define SHADER_HPP

#include <glad/glad.h>

#pragma clang diagnostic ignored "-Wdocumentation"
#include <GLFW/glfw3.h>
#pragma clang diagnostic pop

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

class Shader {
private:
    GLuint id;
    void checkShaderCompileErrors(GLuint shader);
    void checkProgramCompileErrors(GLuint program);
public:
    Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
    ~Shader();
    void use();
};

#endif /* Shader_hpp */
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
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#pragma clang diagnostic pop

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

class Shader {
private:
    GLuint id;
    void checkShaderCompileErrors(GLuint shader);
    void checkProgramCompileErrors(GLuint program);
    GLuint uniformLocation(string &uniformName);
public:
    Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
    ~Shader();
    void use();
    void setUniform(string name, GLuint value);
    void setUniform(string name, GLint value);
    void setUniform(string name, GLfloat value);
    void setUniform(string name, glm::mat4 value);
};

#endif /* Shader_hpp */

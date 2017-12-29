//
//  Shader.cpp
//  GameEngine
//
//  Created by Jakub Hladik on 12/28/17.
//  Copyright © 2017 Jakub Hladik. All rights reserved.
//

#include "Shader.hpp"

Shader::Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath)
{
    std::string vertexCodeString;
    std::string fragmentCodeString;
    std::string geometryCodeString;

    std::ifstream vertexShaderFile;
    std::ifstream fragmentShaderFile;
    std::ifstream geometryShaderFile;

    vertexShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fragmentShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    geometryShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        // open files
        vertexShaderFile.open(vertexPath);
        fragmentShaderFile.open(fragmentPath);
        std::stringstream vertexShaderStream, fragmentShaderStream, geometryShaderStream;
        // read file buffer contents into streams
        vertexShaderStream << vertexShaderFile.rdbuf();
        fragmentShaderStream << fragmentShaderFile.rdbuf();
        // close file handlers
        vertexShaderFile.close();
        fragmentShaderFile.close();
        // convert stream into string
        vertexCodeString = vertexShaderStream.str();
        fragmentCodeString = fragmentShaderStream.str();
        
        if (geometryPath != nullptr)
        {
            geometryShaderFile.open(geometryPath);
            geometryShaderStream << geometryShaderFile.rdbuf();
            geometryShaderFile.close();
            geometryCodeString = geometryShaderStream.str();
        }
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "Error reading shader source file." << std::endl;
    }
    const char* vertexShaderCode = vertexCodeString.c_str();
    const char* fragmentShaderCode = fragmentCodeString.c_str();
    const char* geometryShaderCode = geometryCodeString.c_str();

    GLuint vertex = -1, fragment = -1, geometry = -1;
    
    // create vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexShaderCode, nullptr);
    glCompileShader(vertex);
    checkShaderCompileErrors(vertex);
    
    // create fragment shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentShaderCode, nullptr);
    glCompileShader(fragment);
    checkShaderCompileErrors(fragment);
    
    if (geometryPath != nullptr)
    {
        // create geometry shader
        geometry = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometry, 1, &geometryShaderCode, nullptr);
        glCompileShader(geometry);
        checkShaderCompileErrors(geometry);
    }
    
    // create shader program
    id = glCreateProgram();
    
    // attach shaders
    glAttachShader(id, vertex);
    glAttachShader(id, fragment);
    if (geometryPath != nullptr)
        glAttachShader(id, geometry);

    // compile program
    glLinkProgram(id);
    // check for compilation errors
    checkProgramCompileErrors(id);

    // free shader resources
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    if (geometryPath != nullptr)
        glDeleteShader(geometry);
}

void Shader::checkShaderCompileErrors(GLuint shader)
{
    GLint success;
    // get status of compilation
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        GLint length;
        // get compilation log
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        GLchar* info = new GLchar[length];
        glGetShaderInfoLog(shader, length, &length, info);
        std::cout << "Error during shader compilation:" << std::endl << info << std::endl;
        delete[] info;
    }
}

void Shader::checkProgramCompileErrors(GLuint program)
{
    GLint success;
    // get status of compilation
    glGetProgramiv(program, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        GLint length;
        // get compilation log
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
        GLchar* info = new GLchar[length];
        glGetProgramInfoLog(program, length, &length, info);
        std::cout << "Error during shader program compilation:" << std::endl << info << std::endl;
        delete[] info;
    }
}

void Shader::use()
{
    glUseProgram(id);
}

Shader::~Shader()
{
    glDeleteProgram(id);
}

GLuint Shader::uniformLocation(std::string &uniformName)
{
    return glGetUniformLocation(id, uniformName.c_str());
}

void Shader::setUniform(std::string name, GLuint value)
{
    glUniform1ui(uniformLocation(name), value);
}

void Shader::setUniform(std::string name, GLint value)
{
    glUniform1i(uniformLocation(name), value);
}

void Shader::setUniform(std::string name, GLfloat value)
{
    glUniform1f(uniformLocation(name), value);
}

void Shader::setUniform(std::string name, glm::mat4 value)
{
    glUniformMatrix4fv(uniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}


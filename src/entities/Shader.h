#ifndef SHADER_H
#define SHADER_H

// Source: https://learnopengl.com/

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "../room.h"

class Shader {

    //static std::string SHADER_ROOT;

public:
    unsigned int id;

    Shader() {}

    Shader(std::string vertexPath, std::string fragmentPath) {
        std::string SHADER_ROOT = "shaders/";

        // Load shaders
        unsigned int vertexShader = createShader(GL_VERTEX_SHADER, "VERTEX", (SHADER_ROOT + vertexPath).c_str());
        unsigned int fragmentShader = createShader(GL_FRAGMENT_SHADER, "FRAGMENT", (SHADER_ROOT + fragmentPath).c_str());

        // Shader program
        id = glCreateProgram();
        glAttachShader(id, vertexShader);
        glAttachShader(id, fragmentShader);
        glLinkProgram(id);
        handleShaderLinkageError(id);

        // Cleanup
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    void use() const {
        glUseProgram(id);
    }
    // utility uniform functions
    // ------------------------------------------------------------------------
    void setBool(const std::string &name, bool value) const
    {
        glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
    }
    // ------------------------------------------------------------------------
    void setInt(const std::string &name, int value) const
    {
        glUniform1i(glGetUniformLocation(id, name.c_str()), value);
    }
    // ------------------------------------------------------------------------
    void setFloat(const std::string &name, float value) const
    {
        glUniform1f(glGetUniformLocation(id, name.c_str()), value);
    }
    // ------------------------------------------------------------------------
    void setVec2(const std::string &name, const glm::vec2 &value) const
    {
        glUniform2fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
    }
    void setVec2(const std::string &name, float x, float y) const
    {
        glUniform2f(glGetUniformLocation(id, name.c_str()), x, y);
    }
    // ------------------------------------------------------------------------
    void setVec3(const std::string &name, const glm::vec3 &value) const
    {
        glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
    }
    void setVec3(const std::string &name, float x, float y, float z) const
    {
        glUniform3f(glGetUniformLocation(id, name.c_str()), x, y, z);
    }
    // ------------------------------------------------------------------------
    void setVec4(const std::string &name, const glm::vec4 &value) const
    {
        glUniform4fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
    }
    void setVec4(const std::string &name, float x, float y, float z, float w) const
    {
        glUniform4f(glGetUniformLocation(id, name.c_str()), x, y, z, w);
    }
    // ------------------------------------------------------------------------
    void setMat2(const std::string &name, const glm::mat2 &mat) const
    {
        glUniformMatrix2fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void setMat3(const std::string &name, const glm::mat3 &mat) const
    {
        glUniformMatrix3fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void setMat4(const std::string &name, const glm::mat4 &mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

private:

    unsigned int createShader(unsigned int shaderType, const char * shaderName, const char * shaderPath) {
        std::string shaderSource;
        std::ifstream shaderFile;

        shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        try {
            shaderFile.open(shaderPath);
            std::stringstream shaderStream;
            shaderStream << shaderFile.rdbuf();
            shaderFile.close();
            shaderSource = shaderStream.str();
        } catch(std::ifstream::failure& e) {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        }

        const char * shaderSourcePointer = shaderSource.c_str();

        unsigned int shader = glCreateShader(shaderType);
        glShaderSource(shader, 1, &shaderSourcePointer, NULL);
        glCompileShader(shader);
        handleShaderCompilationError(shader, shaderName);
        return shader;
    }

    void handleShaderCompilationError(unsigned int shader_name,  const char * shader_repr) {
        int  success;
        char infoLog[512];
        glGetShaderiv(shader_name, GL_COMPILE_STATUS, &success);

        if(!success) {
            glGetShaderInfoLog(shader_name, 512, NULL, infoLog);
            std::cout << std::endl << "ERROR::SHADER::" << shader_repr << "::COMPILATION_FAILED\n" << infoLog << std::endl;
            glfwSetWindowShouldClose(window, true);
        }
    }

    void handleShaderLinkageError(unsigned int program_name) {
        int  success;
        char infoLog[512];
        glGetProgramiv(program_name, GL_LINK_STATUS, &success);

        if(!success) {
            glGetShaderInfoLog(program_name, 512, NULL, infoLog);
            std::cout << std::endl << "ERROR::SHADER::LINKAGE_FAILED\n" << infoLog << std::endl;
            glfwSetWindowShouldClose(window, true);
        }
    }
};

#endif

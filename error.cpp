#include <iostream>
#include <stdlib.h>
#include <glad/glad.h>

#include "room.h"
#include "error.h"

void handleGenericError(int error_code, const char * error_message) {
    std::cout << "Error code: " << error_code << "\n";
    std::cout << "Error message: " << error_message << "\n";
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

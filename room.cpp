#include <iostream>
#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "room.h"
#include "error.h"

GLFWwindow * window;
unsigned int VAO;
unsigned int shaderProgram;

void setup(void) {

    // Viewport
    glViewport(0, 0, 800, 600);

    // Shaders
    setVertexProgram();

    // Vertex data
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };  

    // Vertex Buffer Object
    unsigned int VBO;

    glGenBuffers(1, &VBO); // generates a unique buffer object name

    glBindBuffer(GL_ARRAY_BUFFER, VBO);// ids object as VBO ('glVertexAttribPointer')

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // allocates and specifies data to copy

    // Vertex Array Object
    glGenVertexArrays(1, &VAO);  

    glBindVertexArray(VAO); // binds VAO to single target

    // Vertex Attribute Pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); 

    glUseProgram(shaderProgram);
}

void render() {
    // Clear the screen
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // state-set
    glClear(GL_COLOR_BUFFER_BIT); // execute

    glDrawArrays(GL_TRIANGLES, 0, 3);
}


void setVertexProgram(void) {
    // Vertex Shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

    const char *vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);

    glCompileShader(vertexShader);
    handleShaderCompilationError(vertexShader, "VERTEX");

    // Fragment Shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    const char *fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n\0";
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);

    glCompileShader(fragmentShader);
    handleShaderCompilationError(fragmentShader, "FRAGMENT");

    // Shader program
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    handleShaderLinkageError(shaderProgram);

    // Shader cleanup
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);  
}


void processInput() {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main() {
    glfwInit();

    GLFWerrorfun errorCb = glfwSetErrorCallback(handleGenericError);
    
    // My GPU complies up to the 4.1 version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Fails if version is less
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // Fails if version is less
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // profile
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    // This actually fetches the functions (they segfault otherwise)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }    

    setup();

    while(!glfwWindowShouldClose(window)) {
        processInput();
        render();
        glfwSwapBuffers(window);
        glfwPollEvents();    
    }

    glDeleteVertexArrays(1, &VAO);
    //glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}

void framebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "room.h"
#include "error.h"

#include "Texture.h"
#include "Shader.h"

GLFWwindow * window;

Texture * textureBox;
Texture * textureSmile;
unsigned int VAO;
unsigned int shaderProgram;

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

void setShaderProgram(void) {
    // Load shaders
    unsigned int vertexShader = createShader(GL_VERTEX_SHADER, "VERTEX", "./vertex.glsl");
    unsigned int fragmentShader = createShader(GL_FRAGMENT_SHADER, "FRAGMENT", "fragment.glsl");

    // Shader program
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    handleShaderLinkageError(shaderProgram);

    // Cleanup
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}


void setVAO() {
    // Vertex Array Object
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO); // single target for VAO

    // Vertex Stream
    float vertices[] = {
            // positions          // colors           // texture coords
            0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
            0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
    };

    // Vertex Attributes
    //  Vertex Buffer Object
    unsigned int VBO;
    glGenBuffers(1, &VBO); // generates a unique buffer object name
    glBindBuffer(GL_ARRAY_BUFFER, VBO);// ids object as VBO ('glVertexAttribPointer')
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // allocates and specifies data to copy

    //  Vertex Attributes Pointers
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0); // over buffer bound to GL_ARRAY_BUFFER
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))); // over buffer bound to GL_ARRAY_BUFFER
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float))); // over buffer bound to GL_ARRAY_BUFFER

    // Element Object Buffer
    unsigned int indices[] = {  // note that we start from 0!
            0, 1, 3,   // first triangle
            1, 2, 3    // second triangle
    };

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Unbind
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void setTextures() {
    textureBox = new Texture("container.jpg");
    textureBox -> mapToTexUnit(0);
    textureSmile = new Texture("awesomeface.png");
    textureSmile -> mapToTexUnit(1);
}

void setup() {
    // Viewport
    glViewport(0, 0, 800, 600);

    // Shaders
    setShaderProgram();

    // VAO
    setVAO();

    // Texture
    setTextures();
}

void render() {
    // Clear the screen
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // state-set
    glClear(GL_COLOR_BUFFER_BIT); // execute

    // Set drawing context
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureBox->id);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textureSmile->id);

    // Set uniforms
    float timeValue = (float) glfwGetTime();
    float value = sin(timeValue) / 2.0f;
    int horizontalOffsetLocation = glGetUniformLocation(shaderProgram, "horizontalOffset");
    if (horizontalOffsetLocation == -1) {
        std::cout << "ERROR::RENDER::UNKNOWN_UNIFORM" << std::endl;
        glfwSetWindowShouldClose(window, true);
    }
    glUniform1f(horizontalOffsetLocation, value);

    int boxSamplerLocation = glGetUniformLocation(shaderProgram, "boxSampler");
    if (boxSamplerLocation == -1) {
        std::cout << "ERROR::RENDER::UNKNOWN_UNIFORM" << std::endl;
        glfwSetWindowShouldClose(window, true);
    }
    glUniform1i(boxSamplerLocation, 0);

    int smileSamplerLocation = glGetUniformLocation(shaderProgram, "smileSampler");
    if (smileSamplerLocation == -1) {
        std::cout << "ERROR::RENDER::UNKNOWN_UNIFORM" << std::endl;
        glfwSetWindowShouldClose(window, true);
    }
    glUniform1i(smileSamplerLocation, 1);

    glm::mat4 trans;
    trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
    trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));

    unsigned int transformLocation = glGetUniformLocation(shaderProgram, "transform");
    if (transformLocation == -1) {
        std::cout << "ERROR::RENDER::UNKNOWN_UNIFORM" << std::endl;
        glfwSetWindowShouldClose(window, true);
    }
    glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(trans));

    // Draw
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}


void processInput() {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main() {

    stbi_set_flip_vertically_on_load(true);

    glfwInit();

    glfwSetErrorCallback(handleGenericError);
    
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

    delete textureBox;
    delete textureSmile;
    glDeleteVertexArrays(1, &VAO);
    //glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}

void framebufferSizeCallback(GLFWwindow *window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

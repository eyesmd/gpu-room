#ifndef GRAPHICS_COMPUTING_ROOM_H
#define GRAPHICS_COMPUTING_ROOM_H

#include <GLFW/glfw3.h>

extern GLFWwindow * window;

extern unsigned int VAO;
extern unsigned int shaderProgram;

void framebufferSizeCallback(GLFWwindow * window, int width, int height);
void setVertexProgram(void);

#endif //GRAPHICS_COMPUTING_ROOM_H

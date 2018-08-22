//
// Created by Daro on 22/08/2018.
//

#include <iostream>
#include "Texture.h"
#include "stb_image.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <regex>
#include "room.h"


Texture::Texture() {}

Texture::Texture(std::string imagePath) {
    data = stbi_load(imagePath.c_str(), &width, &height, &nrChannels, 0);
    if (data == NULL) {
        std::cout << "ERROR::SETUP::TEXTURE_IMAGE_NOT_FOUND" << std::endl;
        glfwSetWindowShouldClose(window, true);
        return;
    }

    std::string extension = imagePath.substr(imagePath.find_last_of(".") + 1);
    if (extension == "jpg") {
        format = GL_RGB;
    } else if (extension == "png") {
        format = GL_RGBA;
    }

    glGenTextures(1, &id);
}

Texture::~Texture() {
    stbi_image_free(data);
}


void Texture::mapToTexUnit(unsigned int texUnit) {
    glActiveTexture(GL_TEXTURE0 + texUnit);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
    glActiveTexture(GL_TEXTURE0);
}


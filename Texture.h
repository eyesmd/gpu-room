//
// Created by Daro on 22/08/2018.
//

#ifndef GRAPHICS_COMPUTING_TEXTURE_H
#define GRAPHICS_COMPUTING_TEXTURE_H

#include <string>


class Texture {

public:
    unsigned int id;
    int width, height, nrChannels;
    unsigned int format;
    unsigned char * data;

    Texture();
    ~Texture();
    explicit Texture(std::string imagePath);
    void mapToTexUnit(unsigned int texUnit);
};


#endif //GRAPHICS_COMPUTING_TEXTURE_H

#ifndef GRAPHICS_COMPUTING_CAMERA_H
#define GRAPHICS_COMPUTING_CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

class BasicCamera {

private:
    static glm::vec3 UP_VECTOR;

    glm::vec3 position;
    float angle;
    glm::mat4 transform;

    void updateTransform();

public:

    BasicCamera(glm::vec3 position, float angle);
    glm::mat4 getViewTransform();

    void move(float displace_x, float displace_y);
    void rotate(float angle);

};


#endif //GRAPHICS_COMPUTING_CAMERA_H

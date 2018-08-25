
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "BasicCamera.h"

/*
 * Camera that only rotates over the Y axis
 */

glm::vec3 BasicCamera::UP_VECTOR = glm::vec3(0.0, 1.0, 0.0);

BasicCamera::BasicCamera(glm::vec3 position, float angle) {
    this->position = position;
    this->angle = -angle;
    updateTransform();
}

void BasicCamera::updateTransform() {
    glm::vec3 direction = glm::normalize(glm::vec3(cos(angle), 0.0, sin(angle)));
    transform = glm::lookAt(position, position + direction, UP_VECTOR);
}

glm::mat4 BasicCamera::getViewTransform() {
    return transform;
}

/*
 * Moves the world so that it appears the camera is moving towards (displace_x, displace_y)
 * (Remeber that OpenGL is right-handed!)
 */
void BasicCamera::move(float displace_x, float displace_y) {
    //displace_x = -displace_x; WHYYYYYYY
    displace_y = -displace_y;

    float angle_from_front = angle + glm::radians(90.0f);

    float rotated_displace_x = displace_x * cos(angle_from_front) - displace_y * sin(angle_from_front);
    float rotated_displace_y = displace_x * sin(angle_from_front) + displace_y * cos(angle_from_front);

    position += glm::vec3(rotated_displace_x, 0.0, rotated_displace_y);

    /*
    glm::vec4 displacement = glm::vec4(displace_x, 0.0, displace_y, 1.0);
    glm::mat4 trans;
    trans = glm::rotate(trans, angle, UP_VECTOR);
    displacement = trans * displacement;
    position += glm::vec3(displacement.x, displacement.y, displacement.z);
    */
    updateTransform();
}

/*
 * Rotates the camera by 'angle'
 */
void BasicCamera::rotate(float added_angle) {
    angle += added_angle;
    updateTransform();
}





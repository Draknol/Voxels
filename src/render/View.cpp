#include <render/View.h>

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include <algorithm>
#include <iostream>

View::View(const glm::vec2 &size, float fov)
    : View(size.x, size.y, fov) {}

View::View(float width, float height, float fov) {
    update();
    updateViewport(width, height, fov);
}

void View::updateViewport(float width, float height, float fov) {
    if (fov >= 0.0f) {
        this->fov = fov;
    }

    glViewport(0, 0, width, height);
    projMatrix = glm::perspective(glm::radians(this->fov), width / height, 0.1f, 100.0f);
    projViewMatrix = projMatrix * viewMatrix;
}

void View::updateViewport(const glm::ivec2 &size, float fov) {
    updateViewport(size.x, size.y, fov);
}

void View::update(const glm::ivec3 &moveDirection, float distance, float verticalDistance) {

    if (moveDirection.x != 0 || moveDirection.z != 0) {
        glm::vec3 moveVector;
        moveVector.x = cos(yaw) * moveDirection.z - sin(yaw) * moveDirection.x;
        moveVector.y = 0.0f;
        moveVector.z = sin(yaw) * moveDirection.z + cos(yaw) * moveDirection.x;

        position += glm::normalize(moveVector) * distance;
    }

    position.y += moveDirection.y * verticalDistance;

    glm::vec3 lookDirection;
    lookDirection.x = cos(yaw) * cos(pitch);
    lookDirection.y = sin(pitch);
    lookDirection.z = sin(yaw) * cos(pitch);

    viewMatrix = glm::lookAt(position, position + lookDirection, up);
    projViewMatrix = projMatrix * viewMatrix;
}

void View::rotate(float yawOffset, float pitchOffset) {
    yaw += glm::radians(yawOffset);
    pitch += glm::radians(pitchOffset);

    pitch = std::clamp(pitch, glm::radians(-89.0f), glm::radians(89.0f));
}
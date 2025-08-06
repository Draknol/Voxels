#include <render/View.h>

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include <algorithm>

View::View(const glm::vec2 &size, float fov)
    : View(size.x, size.y, fov) {}

View::View(float width, float height, float fov)
    : yaw(glm::radians(-90.0f)), pitch(glm::radians(0.0f)) {
    update();
    updateViewport(width, height, fov);
}

void View::updateViewport(float width, float height, float fov) {
    glViewport(0, 0, width, height);
    projMatrix = glm::perspective(glm::radians(fov), width / height, 0.1f, 100.0f);
    projViewMatrix = projMatrix * viewMatrix;
}

void View::updateViewport(const glm::ivec2 &size, float fov) {
    updateViewport(size.x, size.y, fov);
}

void View::update(const glm::ivec2 &moveDirection, float distance) {

    if (moveDirection != glm::ivec2(0)) {
        glm::vec3 moveVector;
        moveVector.x = cos(yaw) * moveDirection.y - sin(yaw) * moveDirection.x;
        moveVector.y = 0.0f;
        moveVector.z = sin(yaw) * moveDirection.y + cos(yaw) * moveDirection.x;

        position += glm::normalize(moveVector) * distance;
    }

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
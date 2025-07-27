#include <render/View.h>

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include <algorithm>

View::View(float width, float height)
    : yaw(glm::radians(-90.0f)), pitch(glm::radians(0.0f)) {
    update();
    resizeViewport(width, height);
}

void View::resizeViewport(float width, float height) {
    glViewport(0, 0, width, height);
    projMatrix = glm::perspective(glm::radians(fov), width / height, 0.1f, 100.0f);
    projViewMatrix = projMatrix * viewMatrix;
}

void View::update(float deltaTime) {
    float forwardInput = static_cast<float>(movingForward - movingBackward);
    float strafeInput = static_cast<float>(movingLeft - movingRight);

    if (forwardInput || strafeInput) {
        glm::vec3 moveDirection;
        moveDirection.x = cos(yaw) * forwardInput + sin(yaw) * strafeInput;
        moveDirection.y = 0.0f;
        moveDirection.z = sin(yaw) * forwardInput - cos(yaw) * strafeInput;

        position += glm::normalize(moveDirection) * cameraSpeed * deltaTime;
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
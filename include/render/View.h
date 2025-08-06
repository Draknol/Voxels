#ifndef VIEW_H
#define VIEW_H

#include <glm/mat4x4.hpp>

class View {
private:
    glm::mat4 projMatrix;
    glm::mat4 viewMatrix;
    glm::mat4 projViewMatrix;

    float yaw;
    float pitch;

    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
    constexpr static glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

public:
    View(float width, float height, float fov);
    View(const glm::vec2 &size, float fov);

    void updateViewport(float width, float height, float fov);
    void updateViewport(const glm::ivec2 &size, float fov);

    void update(const glm::ivec2 &moveDirection = glm::ivec2(0), float distance = 0.0f);

    void rotate(float yawOffset, float pitchOffset);

    const glm::mat4 &getProjView() { return projViewMatrix; }
    const glm::vec3 &getPosition() { return position; }
};

#endif
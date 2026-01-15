#ifndef VIEW_H
#define VIEW_H

#include <glm/mat4x4.hpp>

class View {
private:
    glm::mat4 projMatrix;
    glm::mat4 viewMatrix;
    glm::mat4 projViewMatrix;

    float fov = 90.0f;
    float yaw = 0.0f;
    float pitch = 0.0f;

    glm::vec3 position = glm::vec3(0.0f, 80.0f, 0.0f);
    constexpr static glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

protected:
    void update(const glm::ivec3 &moveDirection = glm::ivec3(0), float distance = 0.0f, float verticalDistance = 0.0f);

public:
    View(float width = 800.0f, float height = 800.0f, float fov = 90.0f);
    View(const glm::vec2 &size, float fov = 90.0f);

    // Uses previous fov by default
    void updateViewport(float width, float height, float fov = -1.0f);
    void updateViewport(const glm::ivec2 &size, float fov = -1.0f);

    void rotate(float yawOffset, float pitchOffset);

    const glm::mat4 &getProjView() { return projViewMatrix; }
    const glm::vec3 &getPosition() { return position; }
};

#endif
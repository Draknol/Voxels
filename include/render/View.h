#ifndef VIEW_H
#define VIEW_H

#include <glm/mat4x4.hpp>

/// @brief Acts as a camera, with a view, aspect ratio and projection
class View {
private:
    glm::mat4 projMatrix;
    glm::mat4 viewMatrix;
    glm::mat4 projViewMatrix;

    float yaw;
    float pitch;

    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
    constexpr static glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    float cameraSpeed = 16.0f;
    float fov = 90.0f;

    bool movingForward = false;
    bool movingLeft = false;
    bool movingBackward = false;
    bool movingRight = false;

public:
    /// @brief Create a view
    /// @param width Width of the window
    /// @param height Height of the window
    View(float width, float height);

    void resizeViewport(float width, float height);

    void update(float deltaTime = 0.0f);

    void rotate(float yawOffset, float pitchOffset);

    const glm::mat4 &getProjView() { return projViewMatrix; }
    const glm::vec3 &getPosition() { return position; }

    void setMovingForward(bool state) { movingForward = state; }
    void setMovingLeft(bool state) { movingLeft = state; }
    void setMovingBackward(bool state) { movingBackward = state; }
    void setMovingRight(bool state) { movingRight = state; }
};

#endif
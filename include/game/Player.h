#ifndef PLAYER_H
#define PLAYER_H

#include <render/View.h>

class Player : public View {
private:
    float walkSpeed = 16.0f;
    float sprintSpeed = 24.0f;
    float moveSpeed = walkSpeed;
    float flySpeed = 8.0f;
    float sensitivity = 0.15f;

    glm::ivec3 moveDirection = {0, 0, 0};

public:
    Player();

    void update(float deltaTime);

    void setMovingForward(bool state);
    void setMovingLeft(bool state);
    void setMovingBackward(bool state);
    void setMovingRight(bool state);
    void setJumping(bool state);
    void setCrouching(bool state);
    void setSprinting(bool state);

    void setSensitivity(float sensitivity) { this->sensitivity = sensitivity; }
    float getSensitivity() const { return sensitivity; }
};

#endif
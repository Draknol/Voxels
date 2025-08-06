#ifndef PLAYER_H
#define PLAYER_H

#include <render/View.h>
#include <util/Settings.h>

class Player {
private:
    std::shared_ptr<Settings> settings;

    View view;

    float moveSpeed = 16.0f;
    float fov = 90.0f;

    glm::ivec2 moveDirection = {0, 0};

public:
    Player(std::shared_ptr<Settings> settings);

    void update(float deltaTime);

    void resizeView(int width, int height);
    void resizeView(const glm::ivec2 &size);

    void rotateView(float yawOffset, float pitchOffset);

    void setMovingForward(bool state);
    void setMovingLeft(bool state);
    void setMovingBackward(bool state);
    void setMovingRight(bool state);

    const glm::mat4 &getProjView();
};

#endif
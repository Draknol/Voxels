#include <game/Player.h>

Player::Player(std::shared_ptr<Settings> settings)
    : settings(settings), fov(settings->getFOV()), sensitivity(settings->getSensitivity()), view(settings->getSize(), settings->getFOV()) {
}

void Player::update(float deltaTime) {
    view.update(moveDirection, moveSpeed * deltaTime);
}

void Player::resizeView(int width, int height) {
    view.updateViewport(width, height, fov);
}

void Player::resizeView(int width, int height, float fov) {
    this->fov = fov;
    view.updateViewport(width, height, fov);
}

void Player::resizeView(const glm::ivec2 &size) {
    view.updateViewport(size, fov);
}

void Player::resizeView(const glm::ivec2 &size, float fov) {
    this->fov = fov;
    view.updateViewport(size, fov);
}

void Player::rotateView(float yawOffset, float pitchOffset) {
    view.rotate(yawOffset, pitchOffset);
}

void Player::setMovingForward(bool state) {
    if (state) {
        moveDirection.y = 1;
    } else if (moveDirection.y == 1) {
        moveDirection.y = 0;
    }
}

void Player::setMovingLeft(bool state) {
    if (state) {
        moveDirection.x = -1;
    } else if (moveDirection.x == -1) {
        moveDirection.x = 0;
    }
}

void Player::setMovingBackward(bool state) {
    if (state) {
        moveDirection.y = -1;
    } else if (moveDirection.y == -1) {
        moveDirection.y = 0;
    }
}

void Player::setMovingRight(bool state) {
    if (state) {
        moveDirection.x = 1;
    } else if (moveDirection.x == 1) {
        moveDirection.x = 0;
    }
}

void Player::setSensitivity(float multiplier) {
    sensitivity = multiplier;
}

const glm::mat4 &Player::getProjView() {
    return view.getProjView();
}

float Player::getSensitivity() const {
    return sensitivity;
}
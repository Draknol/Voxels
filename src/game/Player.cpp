#include <game/Player.h>

#include <util/Settings.h>

#include <iostream>

Player::Player() : View(Settings::getSize(), Settings::getFOV()), sensitivity(Settings::getSensitivity()) {}

void Player::update(float deltaTime) {
    View::update(moveDirection, moveSpeed * deltaTime, flySpeed * deltaTime);
}

void Player::setMovingForward(bool state) {
    if (state) {
        moveDirection.z = 1;
    } else if (moveDirection.z == 1) {
        moveDirection.z = 0;
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
        moveDirection.z = -1;
    } else if (moveDirection.z == -1) {
        moveDirection.z = 0;
    }
}

void Player::setMovingRight(bool state) {
    if (state) {
        moveDirection.x = 1;
    } else if (moveDirection.x == 1) {
        moveDirection.x = 0;
    }
}

void Player::setJumping(bool state) {
    if (state) {
        moveDirection.y = 1;
    } else if (moveDirection.y == 1) {
        moveDirection.y = 0;
    }
}

void Player::setCrouching(bool state) {
    if (state) {
        moveDirection.y = -1;
    } else if (moveDirection.y == -1) {
        moveDirection.y = 0;
    }
}

void Player::setSprinting(bool state) {
    if (state) {
        moveSpeed = sprintSpeed;
    } else {
        moveSpeed = walkSpeed;
    }
}
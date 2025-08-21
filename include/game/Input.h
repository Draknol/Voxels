#ifndef INPUT_H
#define INPUT_H

#include <game/Player.h>

namespace Input {
// Sets functions to be called when a key is pressed
void setupKeyCallback(Player &player);

// Sets functions to be called when the window is resized
void setupResizeCallback(Player &player);

// Sets functions to be called when the cursor is moved
void setupCursorCallback(Player &player);
} // namespace Input

#endif
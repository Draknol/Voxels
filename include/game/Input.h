#ifndef INPUT_H
#define INPUT_H

#include <game/Game.h>

namespace Input {
// Sets functions to be called when a key is pressed
void setupKeyCallback(Game *game, Engine &engine, Player &player, std::shared_ptr<Settings> settings);

// Sets functions to be called when the window is resized
void setupResizeCallback(Engine &engine, Player &player);

// Sets functions to be called when the cursor is moved
void setupCursorCallback(Engine &engine, Player &player);
} // namespace Input

#endif
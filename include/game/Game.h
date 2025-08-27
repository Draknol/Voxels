#ifndef GAME_H
#define GAME_H

#include <game/World.h>

#include <string>

namespace Game {
// Call once before using Game
void init(const std::string &title, const std::string &settingsPath = "config/settings.ini", const std::string &colorPalletePath = "config/color-palette.ini");

// Stores a World* to use for rendering
void useWorld(const World *world);

// Call before exiting
void close();

// Renders one frame to the screen
void render();

// Checks if the game should continue running
bool isRunning();

void updateFromSettings();
} // namespace Game

#endif
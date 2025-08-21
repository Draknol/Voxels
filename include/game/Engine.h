#ifndef ENGINE_H
#define ENGINE_H

#include <game/World.h>
#include <util/Color.h>
#include <util/Key.h>

#include <glm/vec2.hpp>

#include <functional>
#include <string>

namespace Engine {
void init(const std::string &title);

// Call once before exit
void terminate();

// Renders a frame to the screen
void render(const World &world);

// Checks if the engine should continue running
bool isRunning();

// Mark the window for closing
void close();

void resize(int width, int height);
void resize(const glm::ivec2 &size);

glm::dvec2 getCursorDelta(double currentX, double currentY);
glm::dvec2 getCursorDelta(const glm::dvec2 &currentPos);

bool isFullscreen();
const glm::ivec2 &getFullscreenSize();

void setKeyCallback(std::function<void(Key::Action key, Key::State state)> callback);
void setResizeCallback(std::function<void(int width, int height)> callback);
void setCursorCallback(std::function<void(double xpos, double ypos)> callback);

void setVSync(bool state);
void toggleFullscreen();

// Sets the clear color of the window
void setSkyColor(const Color &color);
} // namespace Engine

#endif
#ifndef WINDOW_H
#define WINDOW_H

#include <util/Color.h>
#include <util/Key.h>

#include <glm/vec2.hpp>

#include <functional>
#include <string>

namespace Window {
void init(const glm::ivec2 &size, const std::string &title);
void init(int width, int height, const std::string &title);

// Call once before exit
void terminate();

// Checks if the Window is marked for closing
bool isOpen();

// Marks the Window for closing
void close();

// Swap buffers to display updated window
void display();

void resize(int width, int height);
void resize(const glm::ivec2 &size);

void setCursorVisible(bool state);
void setFullscreen(bool state);

void setKeyCallback(std::function<void(Key::Action key, Key::State state)> callback);
void setResizeCallback(std::function<void(int width, int height)> callback);
void setCursorCallback(std::function<void(double xpos, double ypos)> callback);

void clear();
void setClearColor(float red, float green, float blue, float alpha);
void setClearColor(const Color &color);
void setClearColor(uint32_t rgba);

void setVsync(bool isVSync);
void setDepthTest(bool state);
void setBackFaceCull(bool state);
void setFrontFaceCull(bool state);

void pollEvents();

// Gets last cursor position (updated after cursor callback)
glm::dvec2 getLastCursorPosition();

const glm::ivec2 &getFullscreenSize();
} // namespace Window

#endif
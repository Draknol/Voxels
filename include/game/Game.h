#ifndef GAME_H
#define GAME_H

#include <game/Engine.h>
#include <game/Player.h>
#include <util/Clock.h>

class Game {
private:
    std::shared_ptr<Settings> settings;
    Engine engine;
    Player player;
    World world;

    Shader voxelShader;

    Clock clock;

    float deltaTime;
    bool printFPS;

public:
    Game(const std::string &title, const std::string &settingsPath = "config/settings.ini");

    // Renders one frame to the screen
    void render();

    // Checks if the game should continue running
    bool isRunning();
};

#endif
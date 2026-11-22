#pragma once

#include "Input.h"
#include "Player.h"
#include "Renderer.h"

// Owns every game object and runs the main loop.
class Game {
public:
    Game();

    // Runs until the player quits. Blocks.
    void run();

private:
    void processEvents();
    void update(double deltaTime);
    void render();

    // NOTE: member order matters. Members are destroyed in reverse order,
    // so SdlContext (declared first) is destroyed last, as it must be.
    SdlContext sdl_;
    Renderer   renderer_;
    Input      input_;
    Player     player_;

    bool running_ = true;
};

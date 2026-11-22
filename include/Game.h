#pragma once

#include <vector>

#include "Bullet.h"
#include "Input.h"
#include "Player.h"
#include "Renderer.h"
#include "Texture.h"

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

    void spawnPlayerBullet();

    // NOTE: member order matters. Members are destroyed in reverse order:
    // textures must die before the renderer, and SDL itself must die last.
    SdlContext sdl_;
    Renderer   renderer_;
    Texture    spriteSheet_;
    Input      input_;
    Player     player_;

    std::vector<Bullet> playerBullets_;

    bool running_ = true;

};

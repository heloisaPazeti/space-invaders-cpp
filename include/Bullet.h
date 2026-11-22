#pragma once

#include <SDL.h>

class Renderer;
class Texture;

// A projectile that moves straight up or down.
// Used for the player's shots now, and for the invaders' shots later.
class Bullet {
public:
    // velocityY is in pixels per second: negative moves up, positive moves down.
    Bullet(float x, float y, float velocityY, const SDL_Rect& sprite);

    void update(double deltaTime);
    void render(Renderer& renderer, const Texture& spriteSheet) const;

    // True once the bullet has completely left the screen (vertically).
    bool isOffscreen() const;

private:
    float    x_;
    float    y_;
    float    velocityY_;
    SDL_Rect sprite_;  // Which part of the sprite sheet to draw
};

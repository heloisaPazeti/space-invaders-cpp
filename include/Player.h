#pragma once

class Input;
class Renderer;
class Texture;

// The player's cannon at the bottom of the screen.
class Player {
public:
    Player();

    void update(double deltaTime, const Input& input);
    void render(Renderer& renderer, const Texture& spriteSheet) const;

    // Where a bullet fired by the player should start.
    float centerX() const;  // Horizontal middle of the cannon
    float top() const;      // Top edge of the cannon

private:
    float x_;
    float y_;
};

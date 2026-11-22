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

private:
    float x_;
    float y_;
};

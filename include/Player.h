#pragma once

class Input;
class Renderer;

// The player's cannon at the bottom of the screen.
// TODO:  For now it is drawn as a green rectangle; sprites come in a later step.
class Player {
public:
    Player();

    void update(double deltaTime, const Input& input);
    void render(Renderer& renderer) const;

private:
    float x_;
    float y_;
};

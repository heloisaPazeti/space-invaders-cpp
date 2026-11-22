#include "Player.h"

#include <algorithm>

#include "Config.h"
#include "Input.h"
#include "Renderer.h"

Player::Player()
    : x_((Config::kLogicalWidth - Config::kPlayerWidth) / 2.0f),
      y_(Config::kPlayerStartY) {}

void Player::update(double deltaTime, const Input& input) {
    // Build a direction from the keys: -1 = left, +1 = right, 0 = still.
    // Pressing both keys cancels out, which is the behavior we want.
    float direction = 0.0f;
    if (input.isHeld(SDL_SCANCODE_LEFT)  || input.isHeld(SDL_SCANCODE_A)) direction -= 1.0f;
    if (input.isHeld(SDL_SCANCODE_RIGHT) || input.isHeld(SDL_SCANCODE_D)) direction += 1.0f;

    // distance = speed * time. Multiplying by deltaTime keeps the speed
    // independent of the update rate.
    x_ += direction * Config::kPlayerSpeed * static_cast<float>(deltaTime);

    // Keep the cannon inside the screen.
    const float maxX = Config::kLogicalWidth - Config::kPlayerWidth;
    x_ = std::clamp(x_, 0.0f, maxX);
}

void Player::render(Renderer& renderer) const {
    renderer.fillRect(x_, y_, Config::kPlayerWidth, Config::kPlayerHeight, 0, 255, 0);
}

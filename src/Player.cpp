#include "Player.h"

#include <algorithm>

#include "Config.h"
#include "Input.h"
#include "Renderer.h"
#include "Sprites.h"
#include "Texture.h"

namespace {
// The sprite size defines the player's size on screen.
constexpr float kWidth = static_cast<float>(Sprites::kPlayer.w);
}  // namespace

Player::Player()
    : x_((Config::kLogicalWidth - kWidth) / 2.0f),
      y_(Config::kPlayerStartY) {}

void Player::update(double deltaTime, const Input& input) {
    // Build a direction from the keys: -1 = left, +1 = right, 0 = still.
    // Pressing both keys cancels out, which is the behavior we want.
    float direction = 0.0f;
    if (input.isHeld(SDL_SCANCODE_LEFT)  || input.isHeld(SDL_SCANCODE_A)) direction -= 1.0f;
    if (input.isHeld(SDL_SCANCODE_RIGHT) || input.isHeld(SDL_SCANCODE_D)) direction += 1.0f;

    // distance = speed * time.
    x_ += direction * Config::kPlayerSpeed * static_cast<float>(deltaTime);

    // Keep the cannon inside the screen.
    x_ = std::clamp(x_, 0.0f, Config::kLogicalWidth - kWidth);
}

void Player::render(Renderer& renderer, const Texture& spriteSheet) const {
    renderer.drawTexture(spriteSheet, Sprites::kPlayer, x_, y_);
}

#include "Bullet.h"

#include "Config.h"
#include "Renderer.h"
#include "Texture.h"

Bullet::Bullet(float x, float y, float velocityY, const SDL_Rect& sprite)
    : x_(x), y_(y), velocityY_(velocityY), sprite_(sprite) {}

void Bullet::update(double deltaTime) {
    // distance = speed * time
    y_ += velocityY_ * static_cast<float>(deltaTime);
}

void Bullet::render(Renderer& renderer, const Texture& spriteSheet) const {
    renderer.drawTexture(spriteSheet, sprite_, x_, y_);
}

bool Bullet::isOffscreen() const {
    const float bottom = y_ + static_cast<float>(sprite_.h);
    return bottom < 0.0f || y_ > static_cast<float>(Config::kLogicalHeight);
}

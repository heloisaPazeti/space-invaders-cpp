#include "Texture.h"

#include <SDL_image.h>

#include <stdexcept>
#include <utility>

Texture::Texture(SDL_Renderer* renderer, const std::string& path) {
    texture_ = IMG_LoadTexture(renderer, path.c_str());
    if (texture_ == nullptr) {
        throw std::runtime_error("Could not load texture '" + path + "': " + IMG_GetError());
    }
    SDL_QueryTexture(texture_, nullptr, nullptr, &width_, &height_);
}

Texture::~Texture() {
    destroy();
}

// Move constructor: steal the resource and leave the other object empty.
// std::exchange(a, b) returns the old value of a and assigns b to it.
Texture::Texture(Texture&& other) noexcept
    : texture_(std::exchange(other.texture_, nullptr)),
      width_(std::exchange(other.width_, 0)),
      height_(std::exchange(other.height_, 0)) {}

Texture& Texture::operator=(Texture&& other) noexcept {
    if (this != &other) {
        destroy();  // Release whatever we currently own first
        texture_ = std::exchange(other.texture_, nullptr);
        width_   = std::exchange(other.width_, 0);
        height_  = std::exchange(other.height_, 0);
    }
    return *this;
}

void Texture::destroy() {
    if (texture_ != nullptr) {
        SDL_DestroyTexture(texture_);
        texture_ = nullptr;
    }
}

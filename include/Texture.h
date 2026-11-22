#pragma once

#include <SDL.h>

#include <string>

// RAII wrapper around SDL_Texture. Move-only: a texture has exactly one owner.
class Texture {
public:
    Texture() = default;

    // Loads an image file (PNG, ...). Throws std::runtime_error on failure.
    Texture(SDL_Renderer* renderer, const std::string& path);
    ~Texture();

    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;
    Texture(Texture&& other) noexcept;
    Texture& operator=(Texture&& other) noexcept;

    SDL_Texture* native() const { return texture_; }
    int width() const { return width_; }
    int height() const { return height_; }
    bool isValid() const { return texture_ != nullptr; }

private:
    void destroy();

    SDL_Texture* texture_ = nullptr;
    int width_  = 0;
    int height_ = 0;
};

#pragma once

#include <SDL.h>

#include <cstdint>
#include <string>

class Texture;

// RAII wrapper for SDL_Init / SDL_Quit and IMG_Init / IMG_Quit.
// Must be created BEFORE anything else that uses SDL, and therefore destroyed last.
class SdlContext {
public:
    SdlContext();
    ~SdlContext();

    SdlContext(const SdlContext&) = delete;
    SdlContext& operator=(const SdlContext&) = delete;
};

// Owns the SDL window and renderer. The rest of the game never calls SDL
// drawing functions directly; it goes through this class instead.
class Renderer {
public:
    Renderer(const std::string& title, int logicalWidth, int logicalHeight, int windowScale);
    ~Renderer();

    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;

    void clear();    // Fill the frame with the background color
    void present();  // Show the finished frame on screen

    // Draw a solid colored rectangle (handy for placeholders and debugging).
    void fillRect(float x, float y, float width, float height,
                  std::uint8_t r, std::uint8_t g, std::uint8_t b);

    // Draw a region (source) of a texture with its top-left corner at (x, y).
    void drawTexture(const Texture& texture, const SDL_Rect& source, float x, float y);

    // Raw SDL renderer, needed later to create textures.
    SDL_Renderer* native() const { return renderer_; }

private:
    SDL_Window*   window_   = nullptr;
    SDL_Renderer* renderer_ = nullptr;
};

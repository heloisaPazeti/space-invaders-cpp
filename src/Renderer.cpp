#include "Renderer.h"

#include <SDL_image.h>

#include <stdexcept>

// --- SdlContext --------------------------------------------------------------

SdlContext::SdlContext() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        throw std::runtime_error(std::string("SDL_Init failed: ") + SDL_GetError());
    }
    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) == 0) {
        SDL_Quit();
        throw std::runtime_error(std::string("IMG_Init failed: ") + IMG_GetError());
    }
}

SdlContext::~SdlContext() {
    IMG_Quit();
    SDL_Quit();
}

// --- Renderer ----------------------------------------------------------------

Renderer::Renderer(const std::string& title, int logicalWidth, int logicalHeight, int windowScale) {
    // Nearest-neighbor scaling keeps pixel art sharp instead of blurry.
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");

    window_ = SDL_CreateWindow(title.c_str(),
                               SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                               logicalWidth * windowScale, logicalHeight * windowScale,
                               SDL_WINDOW_RESIZABLE);
    if (window_ == nullptr) {
        throw std::runtime_error(std::string("SDL_CreateWindow failed: ") + SDL_GetError());
    }

    renderer_ = SDL_CreateRenderer(window_, -1,
                                   SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer_ == nullptr) {
        SDL_DestroyWindow(window_);
        throw std::runtime_error(std::string("SDL_CreateRenderer failed: ") + SDL_GetError());
    }

    // Draw everything at the original arcade resolution and let SDL scale it up.
    SDL_RenderSetLogicalSize(renderer_, logicalWidth, logicalHeight);
    SDL_RenderSetIntegerScale(renderer_, SDL_TRUE);
}

Renderer::~Renderer() {
    if (renderer_ != nullptr) SDL_DestroyRenderer(renderer_);
    if (window_ != nullptr) SDL_DestroyWindow(window_);
}

void Renderer::clear() {
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
    SDL_RenderClear(renderer_);
}

void Renderer::present() {
    SDL_RenderPresent(renderer_);
}

void Renderer::fillRect(float x, float y, float width, float height,
                        std::uint8_t r, std::uint8_t g, std::uint8_t b) {
    SDL_SetRenderDrawColor(renderer_, r, g, b, 255);
    const SDL_FRect rect{x, y, width, height};
    SDL_RenderFillRectF(renderer_, &rect);
}

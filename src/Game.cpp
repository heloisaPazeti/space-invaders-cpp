
#include "Game.h"
#include "Config.h"
#include "Sprites.h"

#include <algorithm>
#include <chrono>
#include <string>


namespace {

// Builds the full path of an asset. The path is relative to the executable
// (not to the current working directory), so the game works no matter where
// you launch it from.
std::string assetPath(const std::string& fileName) {
    char* basePath = SDL_GetBasePath();  // Ends with a path separator
    std::string result = (basePath != nullptr) ? basePath : "./";
    SDL_free(basePath);
    return result + "assets/" + fileName;
}

}  // namespace

Game::Game()
    : renderer_("Space Invaders",
                Config::kLogicalWidth, Config::kLogicalHeight, Config::kWindowScale),
      spriteSheet_(renderer_.native(), assetPath("SpaceInvaders.png")) {}

void Game::run() {
    using Clock = std::chrono::steady_clock;

    // Fixed timestep loop ("Fix Your Timestep" pattern):
    // logic always advances in identical 1/60 s steps, while rendering happens
    // as often as the display allows. This keeps the game deterministic.
    auto previousTime = Clock::now();
    double accumulator = 0.0;

    while (running_) {
        const auto currentTime = Clock::now();
        double frameTime = std::chrono::duration<double>(currentTime - previousTime).count();
        previousTime = currentTime;

        // If the game stalled (window drag, breakpoint...), don't try to catch up forever.
        frameTime = std::min(frameTime, Config::kMaxFrameTime);
        accumulator += frameTime;

        processEvents();

        // Run as many fixed steps as the elapsed time requires (possibly zero).
        while (accumulator >= Config::kFixedTimeStep) {
            update(Config::kFixedTimeStep);

            // A "just pressed" key must be seen by exactly one update, so we
            // clear it after each step. If this frame ran zero updates, the
            // press stays pending until the next update runs.
            input_.clearPressed();

            accumulator -= Config::kFixedTimeStep;
        }

        render();
    }
}

void Game::processEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        input_.handleEvent(event);
    }

    if (input_.quitRequested() || input_.wasPressed(SDL_SCANCODE_ESCAPE)) {
        running_ = false;
    }
}

void Game::update(double deltaTime) {
    player_.update(deltaTime, input_);

    // Space fires, but only if the player has not used up all its bullets.
    // wasPressed() is true for a single update, so holding the key down
    // does not fire a stream of bullets.
    if (input_.wasPressed(SDL_SCANCODE_SPACE) &&
        playerBullets_.size() < Config::kMaxPlayerBullets) {
        spawnPlayerBullet();
    }

    for (Bullet& bullet : playerBullets_) {
        bullet.update(deltaTime);
    }

    // Remove bullets that left the screen. We do this AFTER the loop above:
    // erasing from a vector while iterating over it invalidates iterators.
    std::erase_if(playerBullets_, [](const Bullet& bullet) {
        return bullet.isOffscreen();
    });
}

void Game::spawnPlayerBullet() {
    const SDL_Rect& sprite = Sprites::kPlayerBullet;

    // Center the bullet horizontally on the cannon, and place it just above it.
    const float x = player_.centerX() - static_cast<float>(sprite.w) / 2.0f;
    const float y = player_.top() - static_cast<float>(sprite.h);

    // Negative velocity = moving up the screen.
    playerBullets_.emplace_back(x, y, -Config::kPlayerBulletSpeed, sprite);
}

void Game::render() {
    renderer_.clear();

    player_.render(renderer_, spriteSheet_);
    for (const Bullet& bullet : playerBullets_) {
        bullet.render(renderer_, spriteSheet_);
    }

    renderer_.present();
}

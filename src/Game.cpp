#include "Game.h"

#include <algorithm>
#include <chrono>

#include "Config.h"

Game::Game()
    : renderer_("Space Invaders",
                Config::kLogicalWidth, Config::kLogicalHeight, Config::kWindowScale) {}

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
}

void Game::render() {
    renderer_.clear();
    player_.render(renderer_);
    renderer_.present();
}

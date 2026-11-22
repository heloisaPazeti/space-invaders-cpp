#pragma once

#include <SDL.h>

#include <array>

// Keeps track of the keyboard state so game code never touches SDL events.
class Input {
public:
    // Feed every SDL event here (called once per event in the main loop).
    void handleEvent(const SDL_Event& event);

    // Forget the "just pressed" keys. Call it after each logic update.
    void clearPressed();

    // True for as long as the key is down.
    bool isHeld(SDL_Scancode key) const { return held_[key]; }

    // True only on the update right after the key went down (good for shooting).
    bool wasPressed(SDL_Scancode key) const { return pressed_[key]; }

    bool quitRequested() const { return quitRequested_; }

private:
    std::array<bool, SDL_NUM_SCANCODES> held_{};
    std::array<bool, SDL_NUM_SCANCODES> pressed_{};
    bool quitRequested_ = false;
};

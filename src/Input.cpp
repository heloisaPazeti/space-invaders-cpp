#include "Input.h"

void Input::handleEvent(const SDL_Event& event) {
    switch (event.type) {
        case SDL_QUIT:
            quitRequested_ = true;
            break;
        case SDL_KEYDOWN:
            // Ignore OS key repeat, we only want the first press.
            if (event.key.repeat == 0) {
                held_[event.key.keysym.scancode]    = true;
                pressed_[event.key.keysym.scancode] = true;
            }
            break;
        case SDL_KEYUP:
            held_[event.key.keysym.scancode] = false;
            break;
        default:
            break;
    }
}

void Input::clearPressed() {
    pressed_.fill(false);
}

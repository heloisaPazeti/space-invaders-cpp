#pragma once

#include <SDL.h>

// Source rectangles (x, y, width, height) inside SpaceInvaders.png.
namespace Sprites {

constexpr SDL_Rect kPlayer{68, 4, 9, 10};
constexpr SDL_Rect kPlayerBullet{39, 5, 1, 6};
}  // namespace Sprites

#pragma once

// Central place for every tweakable game constant.
namespace Config {

// --- Display ---------------------------------------------------------------
// The original arcade resolution. The whole game is drawn at this size and
// SDL scales it up to the real window, which keeps pixels sharp.
constexpr int kLogicalWidth  = 224;
constexpr int kLogicalHeight = 256;
constexpr int kWindowScale   = 3;   // Initial window = logical size * scale

// --- Game loop -------------------------------------------------------------
constexpr double kFixedTimeStep = 1.0 / 60.0;  // Game logic runs at 60 updates/s
constexpr double kMaxFrameTime  = 0.25;        // Clamp to avoid the "spiral of death"

// --- Player ----------------------------------------------------------------
constexpr float kPlayerSpeed  = 100.0f;  // Pixels per second
constexpr float kPlayerStartY = 220.0f;

}  // namespace Config


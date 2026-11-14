#ifndef ARKANOID_ARCANOIDCONFIG_HPP
#define ARKANOID_ARCANOIDCONFIG_HPP

#include "Engine/S2DVector2.hpp"

namespace Arkanoid {

constexpr float kPi = 3.14159265358979323846f;

// Logical canvas.
constexpr float kDesignWidth = 1920.f;
constexpr float kDesignHeight = 1080.f;

// Playfield, in logical coordinates.  The origin is the centre of the canvas.
constexpr float kFieldLeft = -880.f;
constexpr float kFieldRight = 880.f;
constexpr float kFieldTop = -440.f;
constexpr float kFieldBottom = 500.f;
constexpr float kFieldWall = 16.f;

constexpr float kInnerLeft = kFieldLeft + kFieldWall;
constexpr float kInnerRight = kFieldRight - kFieldWall;
constexpr float kInnerTop = kFieldTop + kFieldWall;

// Paddle.
constexpr float kPaddleY = 450.f;
constexpr float kPaddleWidth = 220.f;
constexpr float kPaddleHeight = 26.f;
constexpr float kPaddleSpeed = 980.f;

// Ball.
constexpr float kBallRadius = 14.f;
constexpr float kBallBaseSpeed = 650.f;
constexpr float kBallSpeedPerLevel = 65.f;
constexpr float kBallMaxSpeed = 1100.f;
constexpr float kBallLostY = kFieldBottom + 70.f;

// Bricks.
constexpr int kBrickColumns = 12;
constexpr int kBrickRows = 6;
constexpr float kBrickWidth = 124.f;
constexpr float kBrickHeight = 42.f;
constexpr float kBrickGapX = 6.f;
constexpr float kBrickGapY = 8.f;
constexpr float kBrickTop = -350.f;

// Keep a single fixed step for physics so a slow frame cannot make the ball
// tunnel through a brick or catapult it across the field.
constexpr float kMaxDeltaTime = 1.f / 30.f;

constexpr int kStartLives = 3;
constexpr int kBrickPointsPerRow = 10;

// Rendering resources.  The textures are consumed by the engine's
// S2D::Renderable / S2D::RenderContext path; the game never draws them itself.
inline constexpr const char* kPaddleTexturePath = "./assets/sprites/paddle.png";
inline constexpr const char* kBallTexturePath = "./assets/sprites/ball.png";
inline constexpr const char* kBallTrailTexturePath = "./assets/sprites/ball_trail.png";
inline constexpr const char* kBackgroundTexturePath = "./assets/textures/background.png";
inline constexpr const char* kLetterboxTexturePath = "./assets/textures/letterbox.png";
inline constexpr const char* kDimTexturePath = "./assets/textures/dim.png";
inline constexpr const char* kPromptPanelTexturePath = "./assets/textures/prompt_panel.png";
inline constexpr const char* kUiFontPath = "./assets/chintzy.ttf";

inline constexpr const char* kBrickTexturePaths[6] = {
    "./assets/sprites/brick_0.png",
    "./assets/sprites/brick_1.png",
    "./assets/sprites/brick_2.png",
    "./assets/sprites/brick_3.png",
    "./assets/sprites/brick_4.png",
    "./assets/sprites/brick_5.png",
};

enum class GameState {
    Title,
    Ready,
    Playing,
    Paused,
    GameOver,
    LevelClear
};

} // namespace Arkanoid

#endif // ARKANOID_ARCANOIDCONFIG_HPP

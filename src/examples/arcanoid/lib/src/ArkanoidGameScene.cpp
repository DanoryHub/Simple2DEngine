//
// Complete Arkanoid game scene implementation.
//
// Gameplay sprites are engine S2D::Renderable objects, the paddle consumes
// input through S2D::Movable, collisions use S2D::Collidable, HUD/overlay text
// uses S2D::Text, and sounds use S2D::Sound.  The scene itself only coordinates
// those engine facilities.
//

#include "Arkanoid/ArkanoidGameScene.hpp"

#include "Engine/S2DCamera.hpp"
#include "Engine/S2DRenderContext.hpp"
#include "Engine/S2DSound.hpp"

#include "SDL3/SDL_events.h"

#include <algorithm>
#include <cstdio>

namespace {

constexpr S2D::Vector4<float> kWhite{0.91f, 0.96f, 1.f, 1.f};
constexpr S2D::Vector4<float> kCyan{0.34f, 0.91f, 1.f, 1.f};
constexpr S2D::Vector4<float> kPink{1.f, 0.35f, 0.61f, 1.f};
constexpr S2D::Vector4<float> kGreen{0.44f, 1.f, 0.74f, 1.f};
constexpr S2D::Vector4<float> kDimText{0.44f, 0.56f, 0.69f, 1.f};

S2D::Vector2<float> brickCenter(int row, int column) {
    constexpr float totalWidth =
        static_cast<float>(Arkanoid::kBrickColumns) * Arkanoid::kBrickWidth +
        static_cast<float>(Arkanoid::kBrickColumns - 1) * Arkanoid::kBrickGapX;
    constexpr float firstCenterX = -totalWidth * 0.5f + Arkanoid::kBrickWidth * 0.5f;

    return S2D::Vector2<float>(
        firstCenterX + static_cast<float>(column) * (Arkanoid::kBrickWidth + Arkanoid::kBrickGapX),
        Arkanoid::kBrickTop + static_cast<float>(row) * (Arkanoid::kBrickHeight + Arkanoid::kBrickGapY));
}

const S2D::Vector2<float> kParkedPosition{100000.f, 100000.f};

} // namespace

namespace Arkanoid {

// ---------------------------------------------------------------------------
// Construction / setup
// ---------------------------------------------------------------------------

ArkanoidGameScene::ArkanoidGameScene()
    : S2D::GameScene() {
    auto camera = std::make_shared<S2D::Camera>();
    camera->setPosition(S2D::Vector2<float>(0.f, 0.f));
    camera->setScale(S2D::Vector2<float>(1.f, 1.f));
    setSceneCamera(camera);

    letterbox = std::make_shared<S2D::Renderable>(kLetterboxTexturePath);
    letterbox->setName("Letterbox");
    letterbox->SetScale(S2D::Vector2<float>(3000.f, 3000.f));
    registerGameObject(letterbox);

    background = std::make_shared<S2D::Renderable>(kBackgroundTexturePath);
    background->setName("Backdrop");
    background->SetPosition(S2D::Vector2<float>(0.f, 0.f));
    registerGameObject(background);

    for (int row = 0; row < kBrickRows; ++row) {
        for (int column = 0; column < kBrickColumns; ++column) {
            auto brick = std::make_shared<Brick>(row, column);
            bricks.push_back(brick);
            registerGameObject(brick);
        }
    }

    paddle = std::make_shared<Paddle>();
    registerGameObject(paddle);

    ball = std::make_shared<Ball>();
    registerGameObject(ball);

    dimOverlay = std::make_shared<S2D::Renderable>(kDimTexturePath);
    dimOverlay->setName("DimOverlay");
    dimOverlay->SetScale(S2D::Vector2<float>(kDesignWidth / 4.f, kDesignHeight / 4.f));
    dimOverlay->SetPosition(kParkedPosition);
    registerGameObject(dimOverlay);

    promptPanel = std::make_shared<S2D::Renderable>(kPromptPanelTexturePath);
    promptPanel->setName("PromptPanel");
    promptPanel->SetPosition(kParkedPosition);
    registerGameObject(promptPanel);

    scoreText = std::make_shared<UiText>("SCORE 000000",
                                        S2D::Vector2<float>(80.f, 22.f), 36.f, kWhite);
    levelText = std::make_shared<UiText>("LEVEL 01",
                                        S2D::Vector2<float>(883.f, 26.f), 32.f, kWhite);
    livesText = std::make_shared<UiText>("LIVES 3",
                                        S2D::Vector2<float>(1690.f, 22.f), 36.f, kWhite);
    controlsText = std::make_shared<UiText>("A / D OR LEFT / RIGHT  MOVE      SPACE  LAUNCH      P  PAUSE",
        S2D::Vector2<float>(616.f, 69.f), 19.f, kDimText);
    titleText = std::make_shared<UiText>("ARKANOID",
                                        S2D::Vector2<float>(578.f, 300.f), 150.f, kCyan);
    overlayTitle = std::make_shared<UiText>("",
                                           S2D::Vector2<float>(776.f, 420.f), 86.f, kCyan);
    overlaySubtitle = std::make_shared<UiText>("",
                                              S2D::Vector2<float>(793.f, 540.f), 34.f, kWhite);
    overlayHint = std::make_shared<UiText>("",
                                          S2D::Vector2<float>(753.f, 600.f), 27.f, kWhite);

    for (const auto& text : {scoreText, levelText, livesText, controlsText,
                             titleText, overlayTitle, overlaySubtitle, overlayHint}) {
        registerGameObject(text);
    }

    brickSound = std::make_shared<S2D::Sound>("./assets/sounds/brick.wav");
    paddleSound = std::make_shared<S2D::Sound>("./assets/sounds/paddle.wav");
    loseSound = std::make_shared<S2D::Sound>("./assets/sounds/lose.wav");
    levelSound = std::make_shared<S2D::Sound>("./assets/sounds/level.wav");
    registerGameObject(brickSound);
    registerGameObject(paddleSound);
    registerGameObject(loseSound);
    registerGameObject(levelSound);

    ball->onBrickHit = [this](int row, int column, const S2D::Vector2<float>& position) {
        onBrickHit(row, column, position);
    };
    ball->onPaddleHit = [this] {
        paddleSoundPending = true;
    };

    buildBricks();
    ball->attachTo(paddle);
    state = GameState::Title;
    updateUi();
}

void ArkanoidGameScene::buildBricks() {
    remainingBricks = 0;

    for (const auto& brick : bricks) {
        const int row = brick->getRow();
        const int column = brick->getColumn();

        const bool present = level <= 1 ||
            ((row * 5 + column * 3 + level * 7) % 11) != 0;

        if (present) {
            brick->activate(brickCenter(row, column),
                            kBrickTexturePaths[rowPaletteIndex(row)]);
            ++remainingBricks;
        } else {
            brick->deactivate();
        }
    }
}

void ArkanoidGameScene::startNewGame() {
    score = 0;
    lives = kStartLives;
    level = 1;
    launchCounter = 0;
    paddle->SetPosition(S2D::Vector2<float>(0.f, kPaddleY));
    paddle->stopMoving();
    buildBricks();
    ball->attachTo(paddle);
    state = GameState::Playing;
    launchBall();
    levelSoundPending = true;
}

void ArkanoidGameScene::launchBall() {
    float direction = paddle->GetPosition().x < 0.f ? 1.f : -1.f;
    if ((launchCounter++ % 2) != 0) {
        direction = -direction;
    }
    ball->launch(currentBallSpeed(), direction);
    state = GameState::Playing;
}

void ArkanoidGameScene::nextLevel() {
    ++level;
    paddle->SetPosition(S2D::Vector2<float>(0.f, kPaddleY));
    paddle->stopMoving();
    buildBricks();
    ball->attachTo(paddle);
    levelSoundPending = true;
    launchBall();
}

void ArkanoidGameScene::loseLife() {
    --lives;
    loseSoundPending = true;
    ball->attachTo(paddle);

    if (lives <= 0) {
        lives = 0;
        state = GameState::GameOver;
    } else {
        state = GameState::Ready;
    }
}

void ArkanoidGameScene::togglePause() {
    if (state == GameState::Playing) {
        state = GameState::Paused;
        paddle->stopMoving();
        ball->setCollisionsEnabled(false);
    } else if (state == GameState::Paused) {
        state = GameState::Playing;
        ball->setCollisionsEnabled(true);
    }
}

void ArkanoidGameScene::handleAction() {
    switch (state) {
        case GameState::Title:
        case GameState::GameOver:
            startNewGame();
            break;
        case GameState::Ready:
            launchBall();
            break;
        case GameState::LevelClear:
            nextLevel();
            break;
        case GameState::Paused:
            state = GameState::Playing;
            ball->setCollisionsEnabled(true);
            break;
        case GameState::Playing:
            break;
    }
}

float ArkanoidGameScene::currentBallSpeed() const {
    return std::min(kBallBaseSpeed + static_cast<float>(level - 1) * kBallSpeedPerLevel,
                    kBallMaxSpeed);
}

int ArkanoidGameScene::rowPaletteIndex(int row) const {
    return ((row % 6) + 6) % 6;
}

void ArkanoidGameScene::onBrickHit(int row, int column, const S2D::Vector2<float>& position) {
    (void) column;
    (void) position;

    score += (row + 1) * kBrickPointsPerRow * level;
    --remainingBricks;
    brickSoundPending = true;

    if (remainingBricks <= 0 && state == GameState::Playing) {
        score += 250 * level;
        state = GameState::LevelClear;
        ball->attachTo(paddle);
        levelSoundPending = true;
    }
}

void ArkanoidGameScene::Iterate(float deltaTime) {
    const float dt = std::min(deltaTime, kMaxDeltaTime);

    if (state == GameState::Title ||
        state == GameState::Ready ||
        state == GameState::Playing) {
        S2D::GameScene::Iterate(dt);
    }

    if (state == GameState::Playing && ball->consumeLost()) {
        loseLife();
    }

    brickSoundCooldown = std::max(0.f, brickSoundCooldown - dt);
    playPendingSounds();
    updateUi();
}

void ArkanoidGameScene::playPendingSounds() {
    if (brickSoundPending) {
        if (brickSoundCooldown <= 0.f && brickSound) {
            brickSound->playSound();
            brickSoundCooldown = 0.06f;
        }
        brickSoundPending = false;
    }

    if (paddleSoundPending) {
        if (paddleSound) {
            paddleSound->playSound();
        }
        paddleSoundPending = false;
    }

    if (loseSoundPending) {
        if (loseSound) {
            loseSound->playSound();
        }
        loseSoundPending = false;
    }

    if (levelSoundPending) {
        if (levelSound) {
            levelSound->playSound();
        }
        levelSoundPending = false;
    }
}

void ArkanoidGameScene::receiveInput(const SDL_Event* event) {
    if (event->type == SDL_EVENT_KEY_DOWN && !event->key.repeat) {
        switch (event->key.scancode) {
            case SDL_SCANCODE_SPACE:
                handleAction();
                break;
            case SDL_SCANCODE_P:
            case SDL_SCANCODE_ESCAPE:
                togglePause();
                break;
            case SDL_SCANCODE_R:
                startNewGame();
                break;
            default:
                break;
        }
    }

    if (event->type == SDL_EVENT_WINDOW_FOCUS_LOST && paddle) {
        paddle->stopMoving();
    }

    const bool forwardToObjects =
        event->type == SDL_EVENT_KEY_UP ||
        state == GameState::Title ||
        state == GameState::Ready ||
        state == GameState::Playing;

    if (forwardToObjects) {
        S2D::GameScene::receiveInput(event);
    }
}

void ArkanoidGameScene::updateCameraScale(
    const std::shared_ptr<S2D::RenderContext>& renderContext) {
    if (!renderContext) {
        return;
    }

    const S2D::Vector2<float> unit = renderContext->logicalToWindow(
        S2D::Vector2<float>(1.f, 1.f));

    // The engine collision segments are sized from the initial 1920x1080
    // window, so the collision camera must never magnify beyond 1:1.  Shrinking
    // to fit a smaller window is safe and keeps sprites and AABBs aligned.
    const float scale = std::max(0.0001f, std::min(1.f, std::min(unit.x, unit.y)));
    if (auto camera = getSceneCamera()) {
        camera->setScale(S2D::Vector2<float>(scale, scale));
    }
}

void ArkanoidGameScene::setRenderableVisible(
    const std::shared_ptr<S2D::Renderable>& renderable,
    bool visible,
    const S2D::Vector2<float>& visiblePosition) {
    if (renderable) {
        renderable->SetPosition(visible ? visiblePosition : kParkedPosition);
    }
}

void ArkanoidGameScene::updateUi() {
    char buffer[96];

    std::snprintf(buffer, sizeof(buffer), "SCORE %06d", score);
    scoreText->setLabel(buffer);

    std::snprintf(buffer, sizeof(buffer), "LEVEL %02d", level);
    levelText->setLabel(buffer);

    std::snprintf(buffer, sizeof(buffer), "LIVES %d", lives);
    livesText->setLabel(buffer);

    const bool showDim =
        state == GameState::Title ||
        state == GameState::Paused ||
        state == GameState::GameOver ||
        state == GameState::LevelClear;

    setRenderableVisible(dimOverlay, showDim, S2D::Vector2<float>(0.f, 0.f));
    setRenderableVisible(promptPanel, state == GameState::Ready,
                         S2D::Vector2<float>(0.f, 170.f));

    titleText->setLabel(state == GameState::Title ? "ARKANOID" : "");
    titleText->setWindowPosition(S2D::Vector2<float>(578.f, 300.f));

    overlayTitle->setLabel("");
    overlaySubtitle->setLabel("");
    overlayHint->setLabel("");

    switch (state) {
        case GameState::Title:
            overlaySubtitle->setLabel("NEON BREAKOUT");
            overlaySubtitle->setColor(kPink);
            overlaySubtitle->setWindowPosition(S2D::Vector2<float>(819.f, 480.f));
            overlayHint->setLabel("PRESS SPACE TO START");
            overlayHint->setColor(kWhite);
            overlayHint->setWindowPosition(S2D::Vector2<float>(704.f, 600.f));
            break;

        case GameState::Ready:
            overlayHint->setLabel("PRESS SPACE TO LAUNCH");
            overlayHint->setColor(kWhite);
            overlayHint->setWindowPosition(S2D::Vector2<float>(753.f, 694.f));
            break;

        case GameState::Paused:
            overlayTitle->setLabel("PAUSED");
            overlayTitle->setColor(kCyan);
            overlayTitle->setWindowPosition(S2D::Vector2<float>(776.f, 420.f));
            overlaySubtitle->setLabel("PRESS P TO RESUME");
            overlaySubtitle->setColor(kWhite);
            overlaySubtitle->setWindowPosition(S2D::Vector2<float>(793.f, 545.f));
            break;

        case GameState::GameOver:
            overlayTitle->setLabel("GAME OVER");
            overlayTitle->setColor(kPink);
            overlayTitle->setWindowPosition(S2D::Vector2<float>(688.f, 380.f));
            std::snprintf(buffer, sizeof(buffer), "FINAL SCORE  %06d", score);
            overlaySubtitle->setLabel(buffer);
            overlaySubtitle->setColor(kWhite);
            overlaySubtitle->setWindowPosition(S2D::Vector2<float>(754.f, 505.f));
            overlayHint->setLabel("PRESS SPACE TO PLAY AGAIN");
            overlayHint->setColor(kCyan);
            overlayHint->setWindowPosition(S2D::Vector2<float>(747.f, 600.f));
            break;

        case GameState::LevelClear:
            std::snprintf(buffer, sizeof(buffer), "LEVEL %d CLEARED", level);
            overlayTitle->setLabel(buffer);
            overlayTitle->setColor(kGreen);
            overlayTitle->setWindowPosition(S2D::Vector2<float>(525.f, 380.f));
            std::snprintf(buffer, sizeof(buffer), "SCORE  %06d", score);
            overlaySubtitle->setLabel(buffer);
            overlaySubtitle->setColor(kWhite);
            overlaySubtitle->setWindowPosition(S2D::Vector2<float>(805.f, 505.f));
            overlayHint->setLabel("PRESS SPACE FOR NEXT LEVEL");
            overlayHint->setColor(kCyan);
            overlayHint->setWindowPosition(S2D::Vector2<float>(730.f, 600.f));
            break;

        case GameState::Playing:
            break;
    }
}

void ArkanoidGameScene::Render(
    const std::shared_ptr<S2D::RenderContext>& renderContext) {
    if (!renderContext) {
        return;
    }

    updateCameraScale(renderContext);

    S2D::GameScene::Render(renderContext);
}

} // namespace Arkanoid

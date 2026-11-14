#ifndef ARKANOID_ARCANOIDGAMESCENE_HPP
#define ARKANOID_ARCANOIDGAMESCENE_HPP

#include "Arkanoid/ArkanoidConfig.hpp"
#include "Arkanoid/ArkanoidGameObjects.hpp"
#include "Arkanoid/ArkanoidUiText.hpp"

#include "Engine/S2DGameScene.hpp"
#include "Engine/S2DRenderable.hpp"

#include <memory>
#include <vector>

namespace S2D {
class RenderContext;
class Sound;
} // namespace S2D

namespace Arkanoid {

class ArkanoidGameScene final: public S2D::GameScene {
public:
    ArkanoidGameScene();
    ~ArkanoidGameScene() override = default;

    void Iterate(float deltaTime) override;
    void Render(const std::shared_ptr<S2D::RenderContext>& renderContext) override;
    void receiveInput(const SDL_Event* event) override;

private:
    void startNewGame();
    void launchBall();
    void nextLevel();
    void loseLife();
    void togglePause();
    void handleAction();
    void buildBricks();
    void playPendingSounds();
    void updateUi();
    void updateCameraScale(const std::shared_ptr<S2D::RenderContext>& renderContext);
    void onBrickHit(int row, int column, const S2D::Vector2<float>& position);

    float currentBallSpeed() const;
    int rowPaletteIndex(int row) const;

    static void setRenderableVisible(const std::shared_ptr<S2D::Renderable>& renderable,
                                     bool visible,
                                     const S2D::Vector2<float>& visiblePosition);

    GameState state = GameState::Title;
    int score = 0;
    int lives = kStartLives;
    int level = 1;
    int remainingBricks = 0;
    int launchCounter = 0;
    float brickSoundCooldown = 0.f;

    std::shared_ptr<S2D::Renderable> letterbox;
    std::shared_ptr<S2D::Renderable> background;
    std::shared_ptr<S2D::Renderable> dimOverlay;
    std::shared_ptr<S2D::Renderable> promptPanel;

    std::shared_ptr<Paddle> paddle;
    std::shared_ptr<Ball> ball;
    std::vector<std::shared_ptr<Brick>> bricks;

    std::shared_ptr<UiText> scoreText;
    std::shared_ptr<UiText> levelText;
    std::shared_ptr<UiText> livesText;
    std::shared_ptr<UiText> controlsText;
    std::shared_ptr<UiText> titleText;
    std::shared_ptr<UiText> overlayTitle;
    std::shared_ptr<UiText> overlaySubtitle;
    std::shared_ptr<UiText> overlayHint;

    std::shared_ptr<S2D::Sound> brickSound;
    std::shared_ptr<S2D::Sound> paddleSound;
    std::shared_ptr<S2D::Sound> loseSound;
    std::shared_ptr<S2D::Sound> levelSound;

    bool brickSoundPending = false;
    bool paddleSoundPending = false;
    bool loseSoundPending = false;
    bool levelSoundPending = false;
};

} // namespace Arkanoid

#endif // ARKANOID_ARCANOIDGAMESCENE_HPP

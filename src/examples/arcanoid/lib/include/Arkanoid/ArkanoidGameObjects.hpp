#ifndef ARKANOID_ARCANOIDGAMEOBJECTS_HPP
#define ARKANOID_ARCANOIDGAMEOBJECTS_HPP

#include "Arkanoid/ArkanoidConfig.hpp"

#include "Engine/S2DCollidable.hpp"
#include "Engine/S2DMovable.hpp"
#include "Engine/S2DRenderable.hpp"

#include <atomic>
#include <deque>
#include <functional>
#include <memory>
#include <string>

namespace Arkanoid {

class Entity: public S2D::Renderable, public S2D::Collidable {
public:
    Entity(const std::string& texturePath,
           const S2D::Vector2<float>& initialPosition,
           const S2D::Vector2<float>& collisionSize,
           const std::string& name);
    ~Entity() override = default;

    void Iterate(float deltaTime) override;
    void setTexture(const std::string& texturePath);

protected:
    S2D::Vector2<float> worldCollisionSize;
};

class Paddle final: public S2D::Movable, public S2D::Collidable {
public:
    Paddle();

    void Iterate(float deltaTime) override;
    void stopMoving();

private:
    bool movingLeft = false;
    bool movingRight = false;
};

class Brick final: public Entity {
public:
    Brick(int newRow, int newColumn);

    void activate(const S2D::Vector2<float>& newPosition, const std::string& texturePath);
    void deactivate();

    bool isActive() const { return active; }
    int getRow() const { return row; }
    int getColumn() const { return column; }
    S2D::Vector2<float> getSize() const { return S2D::Vector2<float>(kBrickWidth, kBrickHeight); }

private:
    int row = 0;
    int column = 0;
    bool active = true;
};

class Ball final: public Entity {
public:
    Ball();

    void attachTo(const std::shared_ptr<Paddle>& newPaddle);
    void launch(float speed, float horizontalDirection);
    void stop();
    void setCollisionsEnabled(bool enabled);

    bool consumeLost();

    void Iterate(float deltaTime) override;
    void Render(const std::shared_ptr<S2D::RenderContext>& renderContext) override;

    std::function<void(int row, int column, const S2D::Vector2<float>& position)> onBrickHit;
    std::function<void()> onPaddleHit;

    bool isAttached() const { return attached.load(std::memory_order_relaxed); }

private:
    void followPaddle();
    void handleCollision(std::shared_ptr<S2D::GameObject>& other);
    void bounceFromPaddle(const Paddle& paddle);
    void bounceOffAABB(const S2D::Vector2<float>& center, const S2D::Vector2<float>& size);

    std::shared_ptr<Paddle> paddle;
    S2D::Vector2<float> velocity{0.f, 0.f};
    std::deque<S2D::Vector2<float>> trail;

    std::atomic<bool> attached{true};
    std::atomic<bool> collisionLocked{false};
    std::atomic<bool> collisionsEnabled{true};
    std::atomic<bool> lost{false};
    float speed = kBallBaseSpeed;
};

} // namespace Arkanoid

#endif // ARKANOID_ARCANOIDGAMEOBJECTS_HPP

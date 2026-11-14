//
// Game object implementations for the Arkanoid example.
//

#include "Arkanoid/ArkanoidGameObjects.hpp"

#include "Engine/S2DHelpers.hpp"
#include "Engine/S2DRenderContext.hpp"

#include "SDL3/SDL_events.h"

#include <algorithm>
#include <cmath>
#include <utility>

namespace Arkanoid {

namespace {

S2D::Vector2<float> ballRestPosition(const Paddle& paddle) {
    return S2D::Vector2<float>(
        paddle.GetPosition().x,
        paddle.GetPosition().y - kPaddleHeight * 0.5f - kBallRadius - 2.f);
}

} // namespace

// ---------------------------------------------------------------------------
// Entity
// ---------------------------------------------------------------------------

Entity::Entity(const std::string& texturePath,
               const S2D::Vector2<float>& initialPosition,
               const S2D::Vector2<float>& collisionSize,
               const std::string& name)
    : S2D::Renderable(texturePath),
      worldCollisionSize(collisionSize) {
    setName(name);
    SetPosition(initialPosition);
    setBBSize(collisionSize);
    setBBPos(initialPosition);
}

void Entity::Iterate(float deltaTime) {
    (void) deltaTime;
    setBBSize(worldCollisionSize);
}

void Entity::setTexture(const std::string& newTexturePath) {
    texturePath = newTexturePath;
}

// ---------------------------------------------------------------------------
// Paddle
// ---------------------------------------------------------------------------

Paddle::Paddle()
    : S2D::Movable(kPaddleTexturePath) {
    setName("Paddle");
    SetPosition(S2D::Vector2<float>(0.f, kPaddleY));
    setBBSize(S2D::Vector2<float>(kPaddleWidth, kPaddleHeight));
    setBBPos(GetPosition());

    registerKeyEvent(SDL_EVENT_KEY_DOWN, SDL_SCANCODE_A,
                     [this] { movingLeft = true; });
    registerKeyEvent(SDL_EVENT_KEY_DOWN, SDL_SCANCODE_LEFT,
                     [this] { movingLeft = true; });
    registerKeyEvent(SDL_EVENT_KEY_DOWN, SDL_SCANCODE_D,
                     [this] { movingRight = true; });
    registerKeyEvent(SDL_EVENT_KEY_DOWN, SDL_SCANCODE_RIGHT,
                     [this] { movingRight = true; });

    registerKeyEvent(SDL_EVENT_KEY_UP, SDL_SCANCODE_A,
                     [this] { movingLeft = false; });
    registerKeyEvent(SDL_EVENT_KEY_UP, SDL_SCANCODE_LEFT,
                     [this] { movingLeft = false; });
    registerKeyEvent(SDL_EVENT_KEY_UP, SDL_SCANCODE_D,
                     [this] { movingRight = false; });
    registerKeyEvent(SDL_EVENT_KEY_UP, SDL_SCANCODE_RIGHT,
                     [this] { movingRight = false; });
}

void Paddle::Iterate(float deltaTime) {
    // Restore the world-space collision size before the next engine collision
    // pass (the engine leaves it in screen space after checking).
    setBBSize(S2D::Vector2<float>(kPaddleWidth, kPaddleHeight));

    const float dt = std::min(deltaTime, kMaxDeltaTime);
    const float direction = (movingRight ? 1.f : 0.f) - (movingLeft ? 1.f : 0.f);
    if (direction == 0.f) {
        return;
    }

    const float halfWidth = kPaddleWidth * 0.5f;
    const float minX = kInnerLeft + halfWidth;
    const float maxX = kInnerRight - halfWidth;
    position.x = std::clamp(position.x + direction * kPaddleSpeed * dt, minX, maxX);
}

void Paddle::stopMoving() {
    movingLeft = false;
    movingRight = false;
}

// ---------------------------------------------------------------------------
// Brick
// ---------------------------------------------------------------------------

Brick::Brick(int newRow, int newColumn)
    : Entity(kBrickTexturePaths[0],
             S2D::Vector2<float>(0.f, 0.f),
             S2D::Vector2<float>(kBrickWidth, kBrickHeight),
             "Brick"),
      row(newRow),
      column(newColumn) {}

void Brick::activate(const S2D::Vector2<float>& newPosition, const std::string& texturePath) {
    active = true;
    setTexture(texturePath);
    SetPosition(newPosition);
    setBBPos(newPosition);
}

void Brick::deactivate() {
    active = false;
    // Park inactive bricks far outside the playfield.  The engine collision
    // system still holds them, but they no longer overlap anything.
    const S2D::Vector2<float> parked(100000.f, 100000.f);
    SetPosition(parked);
    setBBPos(parked);
}

// ---------------------------------------------------------------------------
// Ball
// ---------------------------------------------------------------------------

Ball::Ball()
    : Entity(kBallTexturePath,
             S2D::Vector2<float>(0.f, kPaddleY - kPaddleHeight * 0.5f - kBallRadius - 2.f),
             S2D::Vector2<float>(kBallRadius * 2.f, kBallRadius * 2.f),
             "Ball") {
    setCallback(CollisionCallbackType::ON_COLLISION_START,
                [this](std::shared_ptr<S2D::GameObject>& other) {
                    handleCollision(other);
                });
}

void Ball::attachTo(const std::shared_ptr<Paddle>& newPaddle) {
    paddle = newPaddle;
    attached.store(true, std::memory_order_relaxed);
    lost.store(false, std::memory_order_relaxed);
    velocity = S2D::Vector2<float>(0.f, 0.f);
    trail.clear();
    followPaddle();
}

void Ball::followPaddle() {
    if (!paddle) {
        return;
    }
    SetPosition(ballRestPosition(*paddle));
}

void Ball::launch(float newSpeed, float horizontalDirection) {
    if (!paddle) {
        return;
    }

    speed = std::clamp(newSpeed, kBallBaseSpeed, kBallMaxSpeed);
    const float x = std::clamp(horizontalDirection, -1.f, 1.f) * 0.58f;
    const float y = -std::sqrt(std::max(0.01f, 1.f - x * x));
    velocity = S2D::Vector2<float>(x, y) * speed;

    attached.store(false, std::memory_order_relaxed);
    collisionLocked.store(false, std::memory_order_relaxed);
    collisionsEnabled.store(true, std::memory_order_relaxed);
    lost.store(false, std::memory_order_relaxed);
    trail.clear();
}

void Ball::setCollisionsEnabled(bool enabled) {
    collisionsEnabled.store(enabled, std::memory_order_relaxed);
    if (enabled) {
        collisionLocked.store(false, std::memory_order_relaxed);
    }
}

void Ball::stop() {
    velocity = S2D::Vector2<float>(0.f, 0.f);
    attached.store(true, std::memory_order_relaxed);
    followPaddle();
}

bool Ball::consumeLost() {
    return lost.exchange(false, std::memory_order_relaxed);
}

void Ball::Iterate(float deltaTime) {
    // Reset the collision box that the engine transformed to screen space
    // during the previous frame's collision pass.
    Entity::Iterate(deltaTime);

    // Collision callbacks for this frame have already finished.  Unlock so the
    // next collision pass can resolve one brick hit.
    collisionLocked.store(false, std::memory_order_relaxed);

    if (attached.load(std::memory_order_relaxed)) {
        followPaddle();
        return;
    }

    if (lost.load(std::memory_order_relaxed)) {
        return;
    }

    const float dt = std::min(deltaTime, kMaxDeltaTime);

    // Move first, then resolve the field bounds.  This keeps code simple and
    // is stable at the speeds used by the game.
    position += velocity * dt;

    if (position.x - kBallRadius < kInnerLeft) {
        position.x = kInnerLeft + kBallRadius;
        velocity.x = std::abs(velocity.x);
    } else if (position.x + kBallRadius > kInnerRight) {
        position.x = kInnerRight - kBallRadius;
        velocity.x = -std::abs(velocity.x);
    }

    if (position.y - kBallRadius < kInnerTop) {
        position.y = kInnerTop + kBallRadius;
        velocity.y = std::abs(velocity.y);
    }

    trail.push_back(position);
    if (trail.size() > 16) {
        trail.pop_front();
    }

    if (position.y - kBallRadius > kBallLostY) {
        lost.store(true, std::memory_order_relaxed);
        velocity = S2D::Vector2<float>(0.f, 0.f);
    }
}

void Ball::Render(const std::shared_ptr<S2D::RenderContext>& renderContext) {
    if (!renderContext) {
        return;
    }

    // The trail is drawn through the engine's render context, before the ball
    // itself, so the ball always stays on top of its own glow.
    const std::size_t trailSize = trail.size();
    for (std::size_t i = 0; i < trailSize; ++i) {
        const float progress = static_cast<float>(i + 1) / static_cast<float>(trailSize);
        const float trailScale = 0.22f + 0.72f * progress;
        renderContext->drawTexture(kBallTrailTexturePath, trail[i],
                                   S2D::Vector2<float>(trailScale, trailScale), 0.f);
    }

    S2D::Renderable::Render(renderContext);
}

void Ball::handleCollision(std::shared_ptr<S2D::GameObject>& other) {
    if (attached.load(std::memory_order_relaxed) ||
        lost.load(std::memory_order_relaxed) ||
        !collisionsEnabled.load(std::memory_order_relaxed)) {
        return;
    }

    if (auto hitPaddle = std::dynamic_pointer_cast<Paddle>(other)) {
        bounceFromPaddle(*hitPaddle);
        if (onPaddleHit) {
            onPaddleHit();
        }
        return;
    }

    auto brick = std::dynamic_pointer_cast<Brick>(other);
    if (!brick || !brick->isActive()) {
        return;
    }

    // A ball can touch two bricks in one collision pass.  Only resolve one hit
    // per frame so the ball cannot bounce twice and reverse itself.
    bool expected = false;
    if (!collisionLocked.compare_exchange_strong(expected, true, std::memory_order_acq_rel)) {
        return;
    }

    const S2D::Vector2<float> brickCenter = brick->GetPosition();
    bounceOffAABB(brickCenter, brick->getSize());

    const int hitRow = brick->getRow();
    const int hitColumn = brick->getColumn();
    brick->deactivate();

    if (onBrickHit) {
        onBrickHit(hitRow, hitColumn, brickCenter);
    }
}

void Ball::bounceFromPaddle(const Paddle& hitPaddle) {
    const float hitOffset = position.x - hitPaddle.GetPosition().x;
    const float normalized = std::clamp(
        hitOffset / (kPaddleWidth * 0.5f + kBallRadius), -1.f, 1.f);

    // The closer to an edge the ball hits, the sharper the outgoing angle.
    const float angle = normalized * (65.f * kPi / 180.f);
    velocity.x = std::sin(angle) * speed;
    velocity.y = -std::cos(angle) * speed;

    // Push the ball just above the paddle so the pair does not repeat next
    // frame.
    position.y = hitPaddle.GetPosition().y - kPaddleHeight * 0.5f - kBallRadius - 1.f;
}

void Ball::bounceOffAABB(const S2D::Vector2<float>& center,
                         const S2D::Vector2<float>& size) {
    const float dx = position.x - center.x;
    const float dy = position.y - center.y;
    const float overlapX = (kBallRadius + size.x * 0.5f) - std::abs(dx);
    const float overlapY = (kBallRadius + size.y * 0.5f) - std::abs(dy);

    if (overlapX <= 0.f || overlapY <= 0.f) {
        return;
    }

    if (overlapX < overlapY) {
        const float direction = dx >= 0.f ? 1.f : -1.f;
        position.x = center.x + direction * (kBallRadius + size.x * 0.5f + 0.5f);
        velocity.x = std::abs(velocity.x) * direction;
    } else {
        const float direction = dy >= 0.f ? 1.f : -1.f;
        position.y = center.y + direction * (kBallRadius + size.y * 0.5f + 0.5f);
        velocity.y = std::abs(velocity.y) * direction;
    }
}

} // namespace Arkanoid

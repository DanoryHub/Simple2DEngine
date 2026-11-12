//
// Created by ivan_miatselski on 2026-08-31.
//

#ifndef ENGINE_S2DCOLLIDABLE_HPP
#define ENGINE_S2DCOLLIDABLE_HPP

#include "Engine/S2DHelpers.hpp"
#include "Engine/S2DVector2.hpp"
#include "Engine/S2DVector4.hpp"
#include "Engine/S2DGameObject.hpp"

#include <map>
#include <memory>
#include <functional>

struct SDL_Renderer;
enum class CollisionCallbackType;

S2DENGINE_NAMESPACE_BEGIN

struct BoundingBox{
    S2D::Vector2<float> pos{0.f, 0.f};
    S2D::Vector2<float> size{100.f, 100.f};

    S2D::Vector4<float> getWorldPoints() const;
    S2D::Vector4<float> getPoints(const S2D::Vector2<float>& cameraPos, const S2D::Vector2<float>& cameraScale, float screenWidth, float screenHeight) const;
};

class Collidable: virtual public S2D::GameObject{
public:
    Collidable();
    S2D::Vector4<float> getBoundingBoxDimensions();
    void setCallback(CollisionCallbackType callbackType, std::function<void(std::shared_ptr<S2D::GameObject>& )> callback);
    void executeCallback(CollisionCallbackType callbackType, std::shared_ptr<S2D::GameObject>& otherObject);
    void setBBPos(const S2D::Vector2<float>& newPos);
    S2D::Vector2<float> getBBPos();
    bool checkCollidableAgainstThisBB(const std::shared_ptr<Collidable>& collidable);
    void setBBSize(const S2D::Vector2<float>& newSize);
    void transformBBToScreenSpace(const S2D::Vector2<float>& cameraPos, const S2D::Vector2<float>& cameraScale, float screenWidth, float screenHeight);
    void drawDebugBox(SDL_Renderer* renderer);
protected:
    BoundingBox boundingBox;
    std::map<CollisionCallbackType, std::function<void(std::shared_ptr<S2D::GameObject>&)>> callbacks;
};

S2DENGINE_NAMESPACE_END

#endif //ENGINE_S2DCOLLIDABLE_HPP

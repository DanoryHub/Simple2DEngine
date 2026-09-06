//
// Created by ivan_miatselski on 2026-08-31.
//

#ifndef ENGINE_S2DCOLLIDABLE_HPP
#define ENGINE_S2DCOLLIDABLE_HPP

#include "Engine/S2DVector2.hpp"
#include "Engine/S2DVector4.hpp"
#include "Engine/S2DGameObject.hpp"

#include <map>
#include <memory>
#include <functional>

struct SDL_Renderer;
enum class CollisionCallbackType;

struct BoundingBox{
    S2DVector2<float> pos{0.f, 0.f};
    S2DVector2<float> size{100.f, 100.f};

    S2DVector4<float> getWorldPoints() const;
    S2DVector4<float> getPoints(const S2DVector2<float>& cameraPos, const S2DVector2<float>& cameraScale, float screenWidth, float screenHeight) const;
};

class S2DCollidable: virtual public S2DGameObject{
public:
    S2DCollidable();
    S2DVector4<float> getBoundingBoxDimensions();
    void setCallback(CollisionCallbackType callbackType, std::function<void(std::shared_ptr<S2DGameObject>& )> callback);
    void executeCallback(CollisionCallbackType callbackType, std::shared_ptr<S2DGameObject>& otherObject);
    void updateBBPos(const S2DVector2<float>& newPos);
    void drawDebugBox(SDL_Renderer* renderer, const S2DVector2<float>& cameraPos, const S2DVector2<float>& cameraScale);
protected:
    BoundingBox boundingBox;
    std::map<CollisionCallbackType, std::function<void(std::shared_ptr<S2DGameObject>&)>> callbacks;
};

#endif //ENGINE_S2DCOLLIDABLE_HPP

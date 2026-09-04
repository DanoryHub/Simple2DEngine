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

enum class CollisionCallbackType;

struct BoundingBox{
    S2DVector2<float> pos{0.f, 0.f};
    S2DVector2<float> size{10.f, 10.f};

    S2DVector4<float> getPoints();
};

class S2DCollidable {
public:
    S2DCollidable();
    S2DVector4<float> getBoundingBoxDimensions();
    void setCallback(CollisionCallbackType callbackType, std::function<void(std::shared_ptr<S2DGameObject>& )> callback);
    void executeCallback(CollisionCallbackType callbackType, std::shared_ptr<S2DGameObject>& otherObject);
protected:
    BoundingBox boundingBox;
    std::map<CollisionCallbackType, std::function<void(std::shared_ptr<S2DGameObject>&)>> callbacks;
};

#endif //ENGINE_S2DCOLLIDABLE_HPP

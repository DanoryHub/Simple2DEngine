//
// Created by ivan_miatselski on 2026-08-18.
//

#ifndef ENGINE_S2DMOVABLE_HPP
#define ENGINE_S2DMOVABLE_HPP

#include <functional>
#include <unordered_map>

#include "Engine/S2DHelpers.hpp"
#include "Engine/S2DIInputReceiver.hpp"
#include "Engine/S2DRenderable.hpp"

S2DENGINE_NAMESPACE_BEGIN

class Movable: public S2D::Renderable, public S2D::IInputReceiver {
public:
    using Renderable::Renderable;

    void receiveInput(const SDL_Event *event) override;
    void registerKeyEvent(Uint32 eventType, const SDL_Scancode& scancode, const std::function<void()>& callback);
protected:
    std::unordered_map<SDL_Scancode, std::function<void()>> keyDownEvents;
    std::unordered_map<SDL_Scancode, std::function<void()>> keyUpEvents;
};

S2DENGINE_NAMESPACE_END

#endif //ENGINE_S2DMOVABLE_HPP

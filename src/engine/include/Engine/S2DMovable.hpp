//
// Created by ivan_miatselski on 2026-08-18.
//

#ifndef ENGINE_S2DMOVABLE_HPP
#define ENGINE_S2DMOVABLE_HPP

#include <functional>
#include <unordered_map>

#include "Engine/S2DIInputReceiver.hpp"
#include "Engine/S2DPlaceable.hpp"

class S2DMovable: public S2DPlaceable, public S2DIInputReceiver  {
public:
    using S2DPlaceable::S2DPlaceable;

    void receiveInput(const SDL_Event *event) override;
    void registerKeyEvent(Uint32 eventType, const SDL_Scancode& scancode, const std::function<void()>& callback);
protected:
    std::unordered_map<SDL_Scancode, std::function<void()>> keyDownEvents;
    std::unordered_map<SDL_Scancode, std::function<void()>> keyUpEvents;
};


#endif //ENGINE_S2DMOVABLE_HPP

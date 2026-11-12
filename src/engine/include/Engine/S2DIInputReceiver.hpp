//
// Created by ivan_miatselski on 2026-08-18.
//

#ifndef ENGINE_S2DIINPUTRECEIVER_HPP
#define ENGINE_S2DIINPUTRECEIVER_HPP

#include "Engine/S2DHelpers.hpp"

#include "SDL3/SDL.h"

S2DENGINE_NAMESPACE_BEGIN

class IInputReceiver {
public:
    virtual ~IInputReceiver() = default;
    virtual void receiveInput(const SDL_Event* event) = 0;
};

S2DENGINE_NAMESPACE_END

#endif //ENGINE_S2DIINPUTRECEIVER_HPP

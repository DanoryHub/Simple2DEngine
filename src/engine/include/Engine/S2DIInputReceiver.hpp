//
// Created by ivan_miatselski on 2026-08-18.
//

#ifndef ENGINE_S2DIINPUTRECEIVER_HPP
#define ENGINE_S2DIINPUTRECEIVER_HPP

#include "SDL3/SDL.h"

namespace S2D {

class IInputReceiver {
public:
    virtual ~IInputReceiver() = default;
    virtual void receiveInput(const SDL_Event* event) = 0;
};

} // namespace S2D

#endif //ENGINE_S2DIINPUTRECEIVER_HPP

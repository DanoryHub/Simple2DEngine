//
// Created by ivan_miatselski on 2026-08-18.
//

#ifndef ENGINE_S2DIINPUTRECEIVER_HPP
#define ENGINE_S2DIINPUTRECEIVER_HPP

#include "SDL3/SDL.h"

class S2DIInputReceiver {
public:
    virtual ~S2DIInputReceiver() = default;
    virtual void receiveInput(const SDL_Event* event) = 0;
};

#endif //ENGINE_S2DIINPUTRECEIVER_HPP

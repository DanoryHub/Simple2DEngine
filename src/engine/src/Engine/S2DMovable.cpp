//
// Created by ivan_miatselski on 2026-08-18.
//

#include "Engine/S2DMovable.hpp"

#include "SDL3/SDL.h"

S2DENGINE_NAMESPACE_BEGIN

void Movable::receiveInput(const SDL_Event *event) {
    if (event->type == SDL_EVENT_KEY_DOWN) {
        if (keyDownEvents.contains(event->key.scancode)) {
            keyDownEvents[event->key.scancode]();
        }
    }
    if (event->type == SDL_EVENT_KEY_UP) {
        if (keyUpEvents.contains(event->key.scancode)) {
            keyUpEvents[event->key.scancode]();
        }
    }
}

void Movable::registerKeyEvent(Uint32 eventType, const SDL_Scancode &scancode, const std::function<void()>& callback) {
    if (eventType == SDL_EVENT_KEY_DOWN) {
        keyDownEvents[scancode] = callback;
    }
    if (eventType == SDL_EVENT_KEY_UP) {
        keyUpEvents[scancode] = callback;
    }
}

S2DENGINE_NAMESPACE_END

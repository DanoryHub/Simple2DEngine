//
// Created by IvanMiatselski on 09.07.2026.
//

#include "Arcanoid/ArcanoidPlaceable.hpp"

#include <iostream>
#include <chrono>
#include <cmath>

#include "Engine/S2DVector2.hpp"
#include "Engine/S2DMacros.hpp"
#include "Engine/S2DMatrix.hpp"

#include "SDL3/SDL_events.h"

ArcanoidPlaceable::ArcanoidPlaceable(const std::string &newTexturePath): S2DMovable(newTexturePath) {
    registerKeyEvent(SDL_EVENT_KEY_DOWN, SDL_SCANCODE_W, methodCallback(moveForward));
    registerKeyEvent(SDL_EVENT_KEY_DOWN, SDL_SCANCODE_S, methodCallback(moveBackward));
    registerKeyEvent(SDL_EVENT_KEY_DOWN, SDL_SCANCODE_D, methodCallback(rotateRight));
    registerKeyEvent(SDL_EVENT_KEY_DOWN, SDL_SCANCODE_A, methodCallback(rotateLeft));
    registerKeyEvent(SDL_EVENT_KEY_UP, SDL_SCANCODE_W, methodCallback(stopMoving));
    registerKeyEvent(SDL_EVENT_KEY_UP, SDL_SCANCODE_S, methodCallback(stopMoving));
    registerKeyEvent(SDL_EVENT_KEY_UP, SDL_SCANCODE_A, methodCallback(stopRotating));
    registerKeyEvent(SDL_EVENT_KEY_UP, SDL_SCANCODE_D, methodCallback(stopRotating));
}

void ArcanoidPlaceable::moveForward() {
    if (currForwardSpeed >= speedMax){
        currForwardSpeed = speedMax;
        return;
    }
    currForwardSpeed += speedMax;
}

void ArcanoidPlaceable::moveBackward() {
    if (currForwardSpeed <= -speedMax){
        currForwardSpeed = -speedMax;
        return;
    }
    currForwardSpeed += speedMax * -1;
}

void ArcanoidPlaceable::rotateRight() {
    if (currentRotationDeg >= rotationSpeedMax){
        currentRotationDeg = rotationSpeedMax;
        return;
    }
    currentRotationDeg += rotationSpeedMax;
}

void ArcanoidPlaceable::rotateLeft() {
    if (currentRotationDeg <= -rotationSpeedMax){
        currentRotationDeg = -rotationSpeedMax;
        return;
    }
    currentRotationDeg += rotationSpeedMax * -1;
}

void ArcanoidPlaceable::stopRotating() {
    currentRotationDeg = 0.f;
}

void ArcanoidPlaceable::stopMoving() {
    currForwardSpeed = 0.f;
}

void ArcanoidPlaceable::Iterate(float deltaTime) {
    S2DPlaceable::Iterate(deltaTime);

    float deltaRotation = currentRotationDeg * deltaTime;
    rotation += deltaRotation;
    fwdVec = S2DMatrix<float>::Rotation(deltaRotation) * fwdVec;
    position += fwdVec * currForwardSpeed * deltaTime;
}

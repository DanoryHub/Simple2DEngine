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
   registerMovingActions();
}

void ArcanoidPlaceable::registerMovingActions() {
    registerKeyEvent(SDL_EVENT_KEY_DOWN, SDL_SCANCODE_W, methodCallback(moveForward));
    registerKeyEvent(SDL_EVENT_KEY_DOWN, SDL_SCANCODE_S, methodCallback(moveBackward));
    registerKeyEvent(SDL_EVENT_KEY_DOWN, SDL_SCANCODE_D, methodCallback(rotateRight));
    registerKeyEvent(SDL_EVENT_KEY_DOWN, SDL_SCANCODE_A, methodCallback(rotateLeft));
    registerKeyEvent(SDL_EVENT_KEY_UP, SDL_SCANCODE_W, methodCallback(stopMovingFwd));
    registerKeyEvent(SDL_EVENT_KEY_UP, SDL_SCANCODE_S, methodCallback(stopMovingBckwd));
    registerKeyEvent(SDL_EVENT_KEY_UP, SDL_SCANCODE_A, methodCallback(stopRotatingLeft));
    registerKeyEvent(SDL_EVENT_KEY_UP, SDL_SCANCODE_D, methodCallback(stopRotatingRight));
}

void ArcanoidPlaceable::moveForward() {
    movingForward = true;
}

void ArcanoidPlaceable::moveBackward() {
    movingBackward = true;
}

void ArcanoidPlaceable::rotateRight() {
    rotatingRight = true;
}

void ArcanoidPlaceable::rotateLeft() {
    rotatingLeft = true;
}

void ArcanoidPlaceable::stopRotatingLeft() {
    rotatingLeft = false;
}

void ArcanoidPlaceable::stopRotatingRight() {
    rotatingRight = false;
}

void ArcanoidPlaceable::stopMovingFwd() {
    movingForward = false;
}

void ArcanoidPlaceable::stopMovingBckwd() {
    movingBackward = false;
}

void ArcanoidPlaceable::processMoving(float deltaTime) {
    currentRotationDeg = 0.f;
    if (rotatingLeft) currentRotationDeg -= rotationSpeedMax;
    if (rotatingRight) currentRotationDeg += rotationSpeedMax;

    float deltaRotation = currentRotationDeg * deltaTime;
    rotation += deltaRotation;
    fwdVec = S2DMatrix<float>::Rotation(deltaRotation) * fwdVec;

    currMovingSpeed = 0.f;
    if (movingForward) currMovingSpeed += speedMax;
    if (movingBackward) currMovingSpeed -= speedMax;
    position += fwdVec * currMovingSpeed * deltaTime;
}

void ArcanoidPlaceable::Iterate(float deltaTime) {
    S2DPlaceable::Iterate(deltaTime);

    processMoving(deltaTime);
}

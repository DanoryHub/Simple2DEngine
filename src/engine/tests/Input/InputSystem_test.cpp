//
// Tests for the input system: Movable key bindings and IInputReceiver dispatch.
//

#include "Engine/S2DIInputReceiver.hpp"
#include "Engine/S2DMovable.hpp"

#include "SDL3/SDL.h"

#include "gtest/gtest.h"

namespace {

SDL_Event makeKeyEvent(Uint32 eventType, SDL_Scancode scancode) {
    SDL_Event event{};
    event.type = eventType;
    event.key.scancode = scancode;
    return event;
}

SDL_Event makeNonKeyEvent(Uint32 eventType) {
    SDL_Event event{};
    event.type = eventType;
    return event;
}

} // namespace

TEST(InputSystemTest, KeyDownCallbackFires) {
    S2D::Movable movable("test_texture.png");
    int calls = 0;

    movable.registerKeyEvent(SDL_EVENT_KEY_DOWN, SDL_SCANCODE_W, [&calls] { ++calls; });
    SDL_Event event = makeKeyEvent(SDL_EVENT_KEY_DOWN, SDL_SCANCODE_W);
    movable.receiveInput(&event);

    EXPECT_EQ(calls, 1);
}

TEST(InputSystemTest, KeyUpCallbackFires) {
    S2D::Movable movable("test_texture.png");
    int calls = 0;

    movable.registerKeyEvent(SDL_EVENT_KEY_UP, SDL_SCANCODE_S, [&calls] { ++calls; });
    SDL_Event event = makeKeyEvent(SDL_EVENT_KEY_UP, SDL_SCANCODE_S);
    movable.receiveInput(&event);

    EXPECT_EQ(calls, 1);
}

TEST(InputSystemTest, KeyDownDoesNotTriggerKeyUpCallback) {
    S2D::Movable movable("test_texture.png");
    int downCalls = 0;
    int upCalls = 0;

    movable.registerKeyEvent(SDL_EVENT_KEY_DOWN, SDL_SCANCODE_W, [&downCalls] { ++downCalls; });
    movable.registerKeyEvent(SDL_EVENT_KEY_UP, SDL_SCANCODE_W, [&upCalls] { ++upCalls; });

    SDL_Event down = makeKeyEvent(SDL_EVENT_KEY_DOWN, SDL_SCANCODE_W);
    movable.receiveInput(&down);

    EXPECT_EQ(downCalls, 1);
    EXPECT_EQ(upCalls, 0);
}

TEST(InputSystemTest, KeyUpDoesNotTriggerKeyDownCallback) {
    S2D::Movable movable("test_texture.png");
    int downCalls = 0;
    int upCalls = 0;

    movable.registerKeyEvent(SDL_EVENT_KEY_DOWN, SDL_SCANCODE_W, [&downCalls] { ++downCalls; });
    movable.registerKeyEvent(SDL_EVENT_KEY_UP, SDL_SCANCODE_W, [&upCalls] { ++upCalls; });

    SDL_Event up = makeKeyEvent(SDL_EVENT_KEY_UP, SDL_SCANCODE_W);
    movable.receiveInput(&up);

    EXPECT_EQ(downCalls, 0);
    EXPECT_EQ(upCalls, 1);
}

TEST(InputSystemTest, UnregisteredKeyIsIgnored) {
    S2D::Movable movable("test_texture.png");
    int calls = 0;

    movable.registerKeyEvent(SDL_EVENT_KEY_DOWN, SDL_SCANCODE_W, [&calls] { ++calls; });
    SDL_Event event = makeKeyEvent(SDL_EVENT_KEY_DOWN, SDL_SCANCODE_A);
    movable.receiveInput(&event);

    EXPECT_EQ(calls, 0);
}

TEST(InputSystemTest, NonKeyEventIsIgnored) {
    S2D::Movable movable("test_texture.png");
    int calls = 0;

    movable.registerKeyEvent(SDL_EVENT_KEY_DOWN, SDL_SCANCODE_W, [&calls] { ++calls; });
    SDL_Event event = makeNonKeyEvent(SDL_EVENT_MOUSE_MOTION);
    movable.receiveInput(&event);

    EXPECT_EQ(calls, 0);
}

TEST(InputSystemTest, RepeatedKeyDownEventsFireEachTime) {
    S2D::Movable movable("test_texture.png");
    int calls = 0;

    movable.registerKeyEvent(SDL_EVENT_KEY_DOWN, SDL_SCANCODE_SPACE, [&calls] { ++calls; });
    SDL_Event event = makeKeyEvent(SDL_EVENT_KEY_DOWN, SDL_SCANCODE_SPACE);

    movable.receiveInput(&event);
    movable.receiveInput(&event);
    movable.receiveInput(&event);

    EXPECT_EQ(calls, 3);
}

TEST(InputSystemTest, RegisteringSameKeyReplacesCallback) {
    S2D::Movable movable("test_texture.png");
    int firstCalls = 0;
    int secondCalls = 0;

    movable.registerKeyEvent(SDL_EVENT_KEY_DOWN, SDL_SCANCODE_D, [&firstCalls] { ++firstCalls; });
    movable.registerKeyEvent(SDL_EVENT_KEY_DOWN, SDL_SCANCODE_D, [&secondCalls] { ++secondCalls; });

    SDL_Event event = makeKeyEvent(SDL_EVENT_KEY_DOWN, SDL_SCANCODE_D);
    movable.receiveInput(&event);

    EXPECT_EQ(firstCalls, 0);
    EXPECT_EQ(secondCalls, 1);
}

TEST(InputSystemTest, MultipleKeysAreIndependent) {
    S2D::Movable movable("test_texture.png");
    int wCalls = 0;
    int aCalls = 0;
    int sCalls = 0;
    int dCalls = 0;

    movable.registerKeyEvent(SDL_EVENT_KEY_DOWN, SDL_SCANCODE_W, [&wCalls] { ++wCalls; });
    movable.registerKeyEvent(SDL_EVENT_KEY_DOWN, SDL_SCANCODE_A, [&aCalls] { ++aCalls; });
    movable.registerKeyEvent(SDL_EVENT_KEY_DOWN, SDL_SCANCODE_S, [&sCalls] { ++sCalls; });
    movable.registerKeyEvent(SDL_EVENT_KEY_DOWN, SDL_SCANCODE_D, [&dCalls] { ++dCalls; });

    SDL_Event a = makeKeyEvent(SDL_EVENT_KEY_DOWN, SDL_SCANCODE_A);
    SDL_Event d = makeKeyEvent(SDL_EVENT_KEY_DOWN, SDL_SCANCODE_D);
    movable.receiveInput(&a);
    movable.receiveInput(&d);

    EXPECT_EQ(wCalls, 0);
    EXPECT_EQ(aCalls, 1);
    EXPECT_EQ(sCalls, 0);
    EXPECT_EQ(dCalls, 1);
}

TEST(InputSystemTest, DispatchesThroughIInputReceiverInterface) {
    S2D::Movable movable("test_texture.png");
    S2D::IInputReceiver* receiver = &movable;
    int calls = 0;

    movable.registerKeyEvent(SDL_EVENT_KEY_DOWN, SDL_SCANCODE_W, [&calls] { ++calls; });
    SDL_Event event = makeKeyEvent(SDL_EVENT_KEY_DOWN, SDL_SCANCODE_W);
    receiver->receiveInput(&event);

    EXPECT_EQ(calls, 1);
}

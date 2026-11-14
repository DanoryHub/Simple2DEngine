# Simple2DEngine

Simple2DEngine is a small, C++20 2D game engine built on top of SDL3, Dear ImGui,
SDL_image, SDL_mixer and TinyJSON. It provides a scene/object model, sprite rendering
with a camera, keyboard input bindings, a segmented collision-detection system,
ImGui-based UI widgets, JSON-backed configuration, and sound playback.

The repository also contains a playable **Arcanoid** example that doubles as the
reference application for the engine.

## Features

- Scene management with generated scene registration from JSON
- Game-object lifecycle (`Iterate`) and rendering (`Render`) interfaces
- Sprite rendering with texture caching, camera position, scale and rotation
- Keyboard input mapping (`Movable`)
- Collision detection with screen segmentation and multi-threaded pair checks
- ImGui UI: buttons, text and labels with custom fonts/colors
- Sound playback through SDL_mixer
- JSON/JSON5 configuration parsing through TinyJSON
- Vector2/Vector4 math types and a small matrix implementation
- GoogleTest unit-test suite

## Requirements

- CMake **4.0+**
- A C++20 compiler
- Python 3 (used by the scene generator and to install its requirements)
- Git and network access for the first configure, because dependencies are fetched
  with CMake `FetchContent`
- The usual SDL3 Linux build dependencies (X11/Wayland and audio development headers)

Dependencies are downloaded and built automatically:

| Dependency | Version |
| --- | --- |
| SDL3 | `release-3.4.10` |
| SDL3_image | `release-3.4.4` |
| SDL_mixer | `release-3.2.4` |
| Dear ImGui | `v1.92.9` |
| GoogleTest | `v1.17.0` |
| TinyJSON | `v0.2.8` |

## Project layout

```
src/
├── engine/
│   ├── include/Engine/   # Public engine headers
│   ├── src/Engine/       # Engine implementation
│   ├── tests/            # GoogleTest unit tests
│   ├── tools/            # Scene-generation script
│   ├── third_party/      # Fetched dependencies (git-ignored)
│   ├── main.cpp          # SDL3 application entry point
│   └── CMakeLists.txt
└── examples/
    └── arcanoid/         # Example game and reference build
        ├── assets/       # Textures, font, sound and scenes.json
        ├── lib/          # Example game library
        └── CMakeLists.txt
```

## Building and running

The example project is the recommended entry point; there is no top-level
`CMakeLists.txt`.

```bash
cd src/examples/arcanoid
cmake -S . -B cmake-build-debug
cmake --build cmake-build-debug -j 4
cd cmake-build-debug
./Arcanoid
```

The build copies `assets/` next to the executable, and the example loads assets with
relative paths such as `./assets/Bug.png`, so run the binary from its build
directory.

## Running the tests

```bash
cd src/examples/arcanoid/cmake-build-debug
ctest --output-on-failure
```

Or run the GoogleTest binary directly, optionally with a filter:

```bash
./Engine/tests/unit_tests
./Engine/tests/unit_tests --gtest_filter='CameraTest.*'
```

The suite currently contains 93 tests covering vectors, game objects, scenes,
placement, camera, input, render context, UI and collision detection.

## Quick start

### 1. Provide game settings

`main.cpp` calls the global `CreateGameSettings()` factory and reads the application
metadata from the returned `S2D::GameSettings`. `GameSettings` handles reading and
parsing the JSON configuration with
[TinyJSON](https://github.com/FFMG/TinyJSON); the game only tells it which file to
load and exposes the factory:

```cpp
#include "Engine/S2DGameSettings.hpp"

class MySettings : public S2D::GameSettings {
public:
    MySettings() : S2D::GameSettings("assets/scenes.json") {}
};

std::shared_ptr<S2D::GameSettings> CreateGameSettings() {
    return std::make_shared<MySettings>();
}
```

The file contains a `settings` object next to the scene definitions:

```json
{
  "settings": {
    "name": "Arcanoid",
    "title": "Arcanoid Game",
    "version": "0.0.1",
    "identifier": "arcanoid",
    "windowWidth": 1920,
    "windowHeight": 1080,
    "initialSceneName": "MainScene"
  }
}
```

### 2. Describe your scenes

Scenes are registered by a generated file. During configuration,
`tools/ScenesCreationGenerator.py` reads `assets/scenes.json` and emits
`InitializeScenes()`, which `MainApp::Init` calls.

```json
{
  "scenes": [
    {
      "id": "MainScene",
      "className": "MyScene",
      "includePath": "MyGame/MyScene.hpp"
    }
  ]
}
```

The generated code is git-ignored and should not be edited manually.

### 3. Implement a scene

A scene owns its objects. Registering an object makes it participate in iteration,
rendering, input dispatch and collision collection.

```cpp
#include "Engine/S2DGameScene.hpp"
#include "Engine/S2DRenderable.hpp"
#include "Engine/S2DCamera.hpp"

class MyScene : public S2D::GameScene {
public:
    MyScene() {
        auto sprite = std::make_shared<S2D::Renderable>("./assets/Bug.png");
        sprite->SetPosition(S2D::Vector2<float>(100.f, 100.f));
        sprite->SetScale(S2D::Vector2<float>(2.f, 2.f));

        registerGameObject(sprite);
        setSceneCamera(std::make_shared<S2D::Camera>());
    }

    void Iterate(float deltaTime) override {
        S2D::GameScene::Iterate(deltaTime);
    }
};
```

## Engine API overview

All engine types live in the `S2D` namespace. Headers use regular
`namespace S2D { ... }` blocks, and `Engine/S2DHelpers.hpp` also defines the
global `CollisionCallbackType` enum.

### Application and scenes

| Type | Purpose |
| --- | --- |
| `MainApp` | Owns the SDL window/renderer, ImGui context, mixer, current scene, render context and collision system. Its `Init`, `ProcessEvent`, `Iterate` and `Quit` methods are called by SDL3's callback-style entry point. |
| `S2D::GameSettings` | Loads application name, title, version, identifier, window size and initial scene from a JSON file. Games supply the file path through a subclass and create it via `CreateGameSettings()`. |
| `S2D::GameScene` | Holds game objects and the scene camera. Dispatches `Iterate`, `Render` and `receiveInput` to registered objects and exposes all `Collidable` objects. |
| `S2D::GameObject` | Base object with a name and an `Iterate(float deltaTime)` override. |

`MainApp::SetScenes` / `UpdateCurrScene` switch scenes, re-register the new scene's
collidables and camera, and pass the audio mixer to its sounds.

### JSON parsing with TinyJSON

JSON handling is provided by [TinyJSON](https://github.com/FFMG/TinyJSON), a
zero-dependency C++ JSON/JSON5 parser. The engine fetches it at configure time and
builds it as a static library. Game settings are read from `scenes.json` in strict
RFC 8259 mode, and parse failures are reported with the config path included.
TinyJSON also supports JSON5 input, value creation and serialization.

### Object capabilities

The engine composes behaviour through interfaces and mixins:

| Type | Purpose |
| --- | --- |
| `S2D::IIterable` | `Iterate(float deltaTime)` |
| `S2D::IRenderable` | `Render(const std::shared_ptr<S2D::RenderContext>&)` |
| `S2D::IInputReceiver` | `receiveInput(const SDL_Event*)` |
| `S2D::Placeable` | Position, scale and rotation (`Get*` / `Set*` methods) |
| `S2D::Renderable` | `Placeable` plus a texture path; renders itself through the `RenderContext` |
| `S2D::Movable` | `Renderable` plus keyboard bindings |
| `S2D::Collidable` | Bounding box, collision callbacks and screen-space transformation |

A typical game object derives from `Movable` and `Collidable`:

```cpp
class Player : public S2D::Movable, public S2D::Collidable {
public:
    explicit Player(const std::string& texturePath)
        : S2D::Movable(texturePath) {}

    void Iterate(float deltaTime) override {
        // update movement, animation, ...
    }
};
```

### Rendering and camera

`S2D::RenderContext` owns the SDL renderer, the active camera, the logical
resolution and a texture cache keyed by path.

```cpp
auto context = std::make_shared<S2D::RenderContext>();
context->registerRenderer(renderer);
context->setLogicalSize(1280, 720);
context->registerCamera(camera);

context->drawTexture(
    "./assets/Bug.png",
    S2D::Vector2<float>(100.f, 100.f),
    S2D::Vector2<float>(1.f, 1.f),
    0.f);
```

- `registerCamera` stores a `std::weak_ptr`; keep the camera alive for as long as it
  is used.
- `getTexture(path)` loads on first use and reuses the cached texture afterwards.
- `logicalToWindow(pos)` maps logical coordinates to the current render output size.
- `S2D::Camera` exposes `get/setPosition`, `get/setScale` and `get/setRotation`.

`S2D::Texture` wraps an `SDL_Texture` and is normally managed by the render context.
`S2D::Matrix` provides `Identity`, `Translation`, `Scaling`, `Rotation` and
matrix/vector multiplication; the render context uses it to build the camera matrix.

### Input

`S2D::Movable` stores callbacks per SDL scancode:

```cpp
player->registerKeyEvent(SDL_EVENT_KEY_DOWN, SDL_SCANCODE_W, [player] {
    player->SetPosition(player->GetPosition() + S2D::Vector2<float>(0.f, -10.f));
});

player->registerKeyEvent(SDL_EVENT_KEY_UP, SDL_SCANCODE_W, [] {
    // stop moving
});
```

Events are delivered by `GameScene::receiveInput`, which forwards them to every
registered `IInputReceiver`.

### Collision

`S2D::Collidable` has a bounding box (`setBBPos`, `setBBSize`) and callbacks for
`ON_COLLISION_START`, `ON_COLLISION_END` and `ON_OVERLAP`:

```cpp
ball->setBBSize(S2D::Vector2<float>(32.f, 32.f));
ball->setCallback(CollisionCallbackType::ON_COLLISION_START,
    [](std::shared_ptr<S2D::GameObject>& other) {
        // react to the other object
    });
```

`S2D::CollisionDetectionSystem` divides the screen into segments, registers
collidables into the segments they overlap, and checks each pair once per frame
across worker threads. `MainApp` owns the system and calls `checkAllCollisions` every
frame; scenes only need to register objects with `registerGameObject`.

### UI

UI widgets are rendered with Dear ImGui and require an active ImGui context
(`MainApp` creates one).

| Type | Description |
| --- | --- |
| `S2D::Label` | Plain struct with `text`, `textSize`, `fontSource` and `textColor` |
| `S2D::Button` | ImGui button with position/size, idle/hovered/pressed colors, a custom font and an `onClick` callback |
| `S2D::Text` | ImGui text with position, size, color and custom font |

```cpp
auto button = std::make_shared<S2D::Button>(
    "Quit",
    S2D::Vector2<float>(320.f, 240.f),
    S2D::Vector2<float>(160.f, 60.f));

button->setButtonColorIdle(S2D::Vector4<float>(0.2f, 0.6f, 0.4f, 1.f));
button->setButtonFont("./assets/chintzy.ttf", 24.f);
button->setOnClickCallback(methodCallback(OnQuit)); // macro capturing `this`

auto text = std::make_shared<S2D::Text>(
    "Score: 0",
    S2D::Vector2<float>(40.f, 40.f),
    32.f);
text->setTextColor(S2D::Vector4<float>(1.f, 1.f, 1.f, 1.f));
text->setTextFont("./assets/chintzy.ttf", 32.f);

registerGameObject(button);
registerGameObject(text);
```

`S2D::Macros` provides `methodCallback(methodName)`, which expands to a lambda that
calls `this->methodName()`.

### Sound

`S2D::Sound` loads and plays an audio file through the mixer supplied by the scene:

```cpp
auto sound = std::make_shared<S2D::Sound>("./assets/test.wav");
registerGameObject(sound); // the device mixer is passed when the scene becomes active
sound->playSound();
```

## Math utilities

- `S2D::Vector2<T>` — arithmetic 2D vector with `+`, `-`, `*`, `/`, compound
  assignment, length/normalization helpers and `operator==`
- `S2D::Vector4<T>` — lightweight 4-component struct used for colors and screen
  rectangles (no `operator==`)
- `S2D::Matrix<T>` — square/rectangular matrix with transformation factories

## Testing

Tests are registered with `gtest_discover_tests`, so each test case appears as a
separate CTest test.

| Suite | Focus |
| --- | --- |
| `VectorTest` | `Vector2` arithmetic and comparisons |
| `GameObjectTest` | Object naming and iteration |
| `GameSceneTest` | Object registration, rendering/input dispatch, camera |
| `PlaceableTest` | Position/scale/rotation |
| `CameraTest` | Camera state and independence |
| `InputSystemTest` | Key bindings, event filtering, interface dispatch |
| `RenderContextTest` | Logical size, renderer/camera registration, coordinate mapping, texture cache |
| `LabelTest`, `UITest` | Label defaults, Button/Text constructors, colors, fonts, callbacks |
| `BoundingBoxTest`, `CollidableTest`, `CollisionDetectionSystemTest`, `CollisionSystemTest` | Bounding boxes, collision callbacks, segmentation and pair handling |

Tests that depend on bundled assets (font and texture) skip automatically when the
asset is not present.

## AI-assisted work

An AI assistant was used to:

- write the unit tests for the **UI**, **Camera**, **RenderContext**, **Input** and
  **Collision** systems under `src/engine/tests/`;
- write this README.

The generated tests were built and executed as part of the change; the full suite
passes with `ctest --output-on-failure`. The tests use subclasses to inspect
protected state and SDL's software renderer where a real window is unnecessary.

## Third-party notices

SDL3, SDL_image, SDL_mixer, Dear ImGui, GoogleTest and TinyJSON are fetched at
configure time and retain their respective licenses. TinyJSON is distributed under
the MIT license.

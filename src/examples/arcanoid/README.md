# Arkanoid

A complete, playable Arkanoid game built as a Simple2DEngine example. The game
uses the engine's public API for its scene, objects, rendering, input,
collision detection, UI text and sound playback. No engine headers or sources
are modified.

## Requirements

- CMake 4.0+
- A C++20 compiler
- Python 3 (used when configuring to generate scene registration)
- The engine's usual SDL3/X11- or Wayland/audio development dependencies

CMake fetches the engine dependencies on the first configure. If the dependency
cache is already populated and network access is unavailable, configure with:

```bash
cmake -S . -B cmake-build-debug -DFETCHCONTENT_FULLY_DISCONNECTED=ON
```

## Build

```bash
cd src/examples/arcanoid
cmake -S . -B cmake-build-debug
cmake --build cmake-build-debug -j 4
```

## Run

The executable loads assets through relative paths, so start it from its build
directory:

```bash
cd cmake-build-debug
./Arkanoid
```

If SDL picks the wrong video backend, select one explicitly, for example:

```bash
SDL_VIDEODRIVER=x11 ./Arkanoid
```

## Controls

| Input | Action |
| --- | --- |
| `A` / `D` or `Left` / `Right` | Move the paddle |
| `Space` | Start the game, launch the ball, continue after a level, restart after game over |
| `P` or `Esc` | Pause / resume |
| `R` | Restart the current run |

## Gameplay

- Clear all bricks to advance to the next level. Each level makes the ball
  faster, up to a cap.
- Bricks award more points on higher rows, and all points are multiplied by the
  current level. Clearing a level also awards a level bonus.
- The player starts with three lives. Losing the ball costs one life; losing the
  last life ends the run. The game-over screen (`Space`) starts a new run.
- The HUD shows score, lives and level. Brick hits, paddle hits, lost lives and
  level clears each have a generated sound effect under `assets/sounds/`.

## Engine usage

`Arkanoid::ArkanoidGameScene` is a `S2D::GameScene`; its gameplay objects are
registered through `registerGameObject()` and updated with `Iterate()`.

- `Arkanoid::Entity` derives from `S2D::Renderable` and `S2D::Collidable`.
  Bricks and the ball are entities.
- `Arkanoid::Paddle` derives from `S2D::Movable` and `S2D::Collidable`. It
  registers its `A`/`D` and arrow-key bindings with `registerKeyEvent()`, so
  paddle input is dispatched by the engine's `IInputReceiver` path.
- `Arkanoid::Ball` overrides `Render()` to draw its trail with
  `S2D::RenderContext::drawTexture()` before delegating to
  `S2D::Renderable::Render()` for the ball sprite.
- `Arkanoid::UiText` extends `S2D::Text`. The HUD and all overlays are engine
  `Text` widgets, not raw ImGui draw lists.
- Background, letterbox, dim overlay and the launch-prompt panel are regular
  `S2D::Renderable` objects drawn by `S2D::GameScene::Render()`.
- `S2D::Sound` objects play the generated effects, and the scene camera is a
  `S2D::Camera`.

The camera is scaled down to fit the window but never magnified, because the
engine's collision segments are based on the initial 1920x1080 window. Each
frame the collidable game objects restore their world-space bounding-box size;
the engine's collision pass rewrites bounding boxes into screen space, and
restoring the size keeps scaled rendering collision-safe. This uses only public
engine methods.

## Assets

All game assets are generated and committed under `assets/`:

- `assets/sprites/` – paddle, ball, ball trail and six brick colors.
- `assets/textures/` – playfield backdrop, letterbox, dim overlay and prompt
  panel.
- `assets/sounds/` – brick, paddle, lose and level-clear effects.
- `assets/chintzy.ttf` – the HUD/overlay font.
- `assets/scenes.json` – registers `Arkanoid::ArkanoidGameScene` as the startup
  scene.

The game logic works in a fixed 1920x1080 logical space, so physics and scoring
are identical at any window size. Rendering scales that space to the window
through the engine camera.

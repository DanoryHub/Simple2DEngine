//
// Created by IvanMiatselski on 02.07.2026.
//

#ifndef ARCANOID_ARCANOIDSCENE_HPP
#define ARCANOID_ARCANOIDSCENE_HPP

#include "Engine/S2DGameScene.hpp"

#include <memory>

struct SDL_Renderer;
class ArcanoidPlaceable;

namespace S2D {
class Button;
class Text;
class Sound;
} // namespace S2D

class ArcanoidScene: public S2D::GameScene {
protected:
    std::shared_ptr<ArcanoidPlaceable> testPlaceable;
    std::shared_ptr<S2D::Button> testButton;
    std::shared_ptr<S2D::Text> testText;
    std::shared_ptr<S2D::Sound> testSound;

    float deltaSoundTime = 9.f;

public:
    ArcanoidScene();

    void buttonCallback();
    void Iterate(float deltaTime) override;
};


#endif //ARCANOID_ARCANOIDSCENE_HPP
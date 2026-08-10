//
// Created by IvanMiatselski on 02.07.2026.
//

#ifndef ARCANOID_ARCANOIDSCENE_HPP
#define ARCANOID_ARCANOIDSCENE_HPP

#include "Engine/S2DGameScene.hpp"

#include <memory>

struct SDL_Renderer;
class ArcanoidPlaceable;
class S2DButton;

class ArcanoidScene: public S2DGameScene {
protected:
    std::shared_ptr<ArcanoidPlaceable> testPlaceable;
    std::shared_ptr<S2DButton> testButton;

public:
    ArcanoidScene();

    void buttonCallback();
    void Iterate(float deltaTime) override;
};


#endif //ARCANOID_ARCANOIDSCENE_HPP
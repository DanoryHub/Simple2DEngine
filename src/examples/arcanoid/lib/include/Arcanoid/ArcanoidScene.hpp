//
// Created by IvanMiatselski on 02.07.2026.
//

#ifndef ARCANOID_ARCANOIDSCENE_HPP
#define ARCANOID_ARCANOIDSCENE_HPP

#include "Engine/S2DGameScene.hpp"

struct SDL_Renderer;
class ArcanoidPlaceable;

class ArcanoidScene: public S2DGameScene {
protected:
    ArcanoidPlaceable *testPlaceable;

public:
    ArcanoidScene(SDL_Renderer* renderer);

    void Iterate(float deltaTime) override;
};


#endif //ARCANOID_ARCANOIDSCENE_HPP
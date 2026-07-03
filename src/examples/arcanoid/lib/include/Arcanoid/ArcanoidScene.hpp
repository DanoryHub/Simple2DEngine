//
// Created by IvanMiatselski on 02.07.2026.
//

#ifndef ARCANOID_ARCANOIDSCENE_HPP
#define ARCANOID_ARCANOIDSCENE_HPP

#include "Engine/S2DGameScene.hpp"

class ArcanoidScene: public S2DGameScene {
public:
    ArcanoidScene();

    void Iterate(float deltaTime) override;
};


#endif //ARCANOID_ARCANOIDSCENE_HPP
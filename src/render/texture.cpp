//
// Created by IvanMiatselski on 26.05.2026.
//

#include "texture.h"

S2DTexture::S2DTexture():
    texture{nullptr},
    tWidth{0},
    tHeight{0}
{

}

S2DTexture::~S2DTexture() {
    S2DTexture::destroy();
}
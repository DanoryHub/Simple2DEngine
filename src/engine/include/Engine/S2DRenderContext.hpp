//
// Created by IvanMiatselski on 24.07.2026.
//

#ifndef ARCANOID_S2DRENDERCONTEXT_HPP
#define ARCANOID_S2DRENDERCONTEXT_HPP

#include <string>
#include <memory>
#include <unordered_map>

#include "Engine/S2DVector2.hpp"

struct SDL_Renderer;
class S2DTexture;
class S2DCamera;

class S2DRenderContext {
public:
    S2DRenderContext();
    ~S2DRenderContext();

    void clearTextureCache();
    void registerRenderer(SDL_Renderer* newRenderer);
    void registerCamera(const std::shared_ptr<S2DCamera>& newCamera);
    void drawTexture(const std::string &tPath,  const S2DVector2<float> &position, const S2DVector2<float> &scale, float rotation);
    S2DTexture* getTexture(const std::string &tPath);

protected:
    SDL_Renderer* renderer;
    std::shared_ptr<S2DCamera> currCamera;

    std::unordered_map<std::string, S2DTexture*> textureCache;
};

#endif //ARCANOID_S2DRENDERCONTEXT_HPP
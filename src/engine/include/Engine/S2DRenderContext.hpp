//
// Created by IvanMiatselski on 24.07.2026.
//

#ifndef ARCANOID_S2DRENDERCONTEXT_HPP
#define ARCANOID_S2DRENDERCONTEXT_HPP

#include <string>
#include <memory>
#include <unordered_map>

#include "Engine/S2DHelpers.hpp"
#include "Engine/S2DVector2.hpp"

struct SDL_AudioSpec;
struct SDL_Renderer;

S2DENGINE_NAMESPACE_BEGIN

class Texture;
class Camera;

class RenderContext {
public:
    RenderContext();
    ~RenderContext();

    void clearTextureCache();
    void registerRenderer(SDL_Renderer* newRenderer);
    void registerCamera(const std::shared_ptr<S2D::Camera>& newCamera);
    void registerAudioSpec(SDL_AudioSpec* newAudioSpec);
    void setLogicalSize(int width, int height);
    S2D::Vector2<float> logicalToWindow(const S2D::Vector2<float>& logicalPos) const;
    void drawTexture(const std::string &tPath,  const S2D::Vector2<float> &position, const S2D::Vector2<float> &scale, float rotation);
    S2D::Texture* getTexture(const std::string &tPath);
    SDL_Renderer* getRenderer();
    S2D::Vector2<float> getCameraPosition();
    S2D::Vector2<float> getCameraScale();
    int getLogicalWidth() const;
    int getLogicalHeight() const;
protected:
    SDL_Renderer* renderer;
    SDL_AudioSpec* audioSpec;
    std::weak_ptr<S2D::Camera> currCamera;
    int logicalWidth = 1920;
    int logicalHeight = 1080;

    std::unordered_map<std::string, std::unique_ptr<S2D::Texture>> textureCache;
};

S2DENGINE_NAMESPACE_END

#endif //ARCANOID_S2DRENDERCONTEXT_HPP

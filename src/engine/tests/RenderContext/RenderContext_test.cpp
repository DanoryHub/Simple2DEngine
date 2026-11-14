#include "Engine/S2DCamera.hpp"
#include "Engine/S2DRenderContext.hpp"

#include "SDL3/SDL.h"

#include "gtest/gtest.h"

#include <atomic>
#include <filesystem>
#include <memory>
#include <string>

namespace {

std::filesystem::path temporaryTexturePath() {
    static std::atomic<int> counter{0};
    const int index = counter.fetch_add(1);
    return std::filesystem::temp_directory_path() /
           ("s2d_rendercontext_test_" + std::to_string(index) + ".bmp");
}

// Exposes the texture cache size so cache behaviour can be asserted.
class RenderContextAccess : public S2D::RenderContext {
public:
    std::size_t textureCount() const { return textureCache.size(); }
};

class RenderContextFixture : public ::testing::Test {
protected:
    void SetUp() override {
        surface = SDL_CreateSurface(200, 100, SDL_PIXELFORMAT_RGBA8888);
        ASSERT_NE(surface, nullptr);
        renderer = SDL_CreateSoftwareRenderer(surface);
        ASSERT_NE(renderer, nullptr);

        ASSERT_TRUE(SDL_FillSurfaceRect(
            surface, nullptr, SDL_MapSurfaceRGBA(surface, 0x40, 0xC8, 0xFF, 0xFF)));

        texturePath = temporaryTexturePath();
        ASSERT_TRUE(SDL_SaveBMP(surface, texturePath.string().c_str()));
    }

    void TearDown() override {
        if (renderer != nullptr) {
            SDL_DestroyRenderer(renderer);
            renderer = nullptr;
        }
        if (surface != nullptr) {
            SDL_DestroySurface(surface);
            surface = nullptr;
        }
        std::error_code error;
        std::filesystem::remove(texturePath, error);
    }

    SDL_Surface* surface = nullptr;
    SDL_Renderer* renderer = nullptr;
    std::filesystem::path texturePath;
};

} // namespace

TEST(RenderContextTest, DefaultState) {
    S2D::RenderContext context;

    EXPECT_EQ(context.getRenderer(), nullptr);
    EXPECT_EQ(context.getLogicalWidth(), 1920);
    EXPECT_EQ(context.getLogicalHeight(), 1080);
}

TEST(RenderContextTest, LogicalSizeCanBeChanged) {
    S2D::RenderContext context;

    context.setLogicalSize(1280, 720);

    EXPECT_EQ(context.getLogicalWidth(), 1280);
    EXPECT_EQ(context.getLogicalHeight(), 720);
}

TEST(RenderContextTest, RendererCanBeRegistered) {
    S2D::RenderContext context;

    context.registerRenderer(nullptr);

    EXPECT_EQ(context.getRenderer(), nullptr);
}

TEST_F(RenderContextFixture, RendererIsStored) {
    S2D::RenderContext context;

    context.registerRenderer(renderer);

    EXPECT_EQ(context.getRenderer(), renderer);
}

TEST(RenderContextTest, CameraDefaultsWhenNoneRegistered) {
    S2D::RenderContext context;

    EXPECT_EQ(context.getCameraPosition(), S2D::Vector2<float>(0.f, 0.f));
    EXPECT_EQ(context.getCameraScale(), S2D::Vector2<float>(1.f, 1.f));
}

TEST(RenderContextTest, RegisteredCameraValuesAreRead) {
    S2D::RenderContext context;
    auto camera = std::make_shared<S2D::Camera>();
    camera->setPosition(S2D::Vector2<float>(15.f, -25.f));
    camera->setScale(S2D::Vector2<float>(2.f, 3.f));

    context.registerCamera(camera);

    EXPECT_EQ(context.getCameraPosition(), S2D::Vector2<float>(15.f, -25.f));
    EXPECT_EQ(context.getCameraScale(), S2D::Vector2<float>(2.f, 3.f));
}

TEST(RenderContextTest, ExpiredCameraFallsBackToDefaults) {
    S2D::RenderContext context;

    {
        auto camera = std::make_shared<S2D::Camera>();
        camera->setPosition(S2D::Vector2<float>(100.f, 200.f));
        camera->setScale(S2D::Vector2<float>(4.f, 5.f));
        context.registerCamera(camera);
    }

    EXPECT_EQ(context.getCameraPosition(), S2D::Vector2<float>(0.f, 0.f));
    EXPECT_EQ(context.getCameraScale(), S2D::Vector2<float>(1.f, 1.f));
}

TEST_F(RenderContextFixture, LogicalToWindowMapsCornersAndCenter) {
    S2D::RenderContext context;
    context.registerRenderer(renderer);
    context.setLogicalSize(1920, 1080);

    const S2D::Vector2<float> topLeft = context.logicalToWindow(S2D::Vector2<float>(0.f, 0.f));
    const S2D::Vector2<float> center = context.logicalToWindow(S2D::Vector2<float>(960.f, 540.f));
    const S2D::Vector2<float> bottomRight = context.logicalToWindow(S2D::Vector2<float>(1920.f, 1080.f));

    EXPECT_FLOAT_EQ(topLeft.x, 0.f);
    EXPECT_FLOAT_EQ(topLeft.y, 0.f);
    EXPECT_FLOAT_EQ(center.x, 100.f);
    EXPECT_FLOAT_EQ(center.y, 50.f);
    EXPECT_FLOAT_EQ(bottomRight.x, 200.f);
    EXPECT_FLOAT_EQ(bottomRight.y, 100.f);
}

TEST_F(RenderContextFixture, LogicalToWindowUsesCurrentLogicalSize) {
    S2D::RenderContext context;
    context.registerRenderer(renderer);
    context.setLogicalSize(100, 100);

    const S2D::Vector2<float> point = context.logicalToWindow(S2D::Vector2<float>(50.f, 50.f));

    EXPECT_FLOAT_EQ(point.x, 100.f);
    EXPECT_FLOAT_EQ(point.y, 50.f);
}

TEST_F(RenderContextFixture, TextureCacheReusesEntriesAndCanBeCleared) {
    RenderContextAccess context;
    context.registerRenderer(renderer);

    EXPECT_EQ(context.textureCount(), 0u);

    auto* first = context.getTexture(texturePath.string());
    ASSERT_NE(first, nullptr);
    EXPECT_EQ(context.textureCount(), 1u);

    auto* second = context.getTexture(texturePath.string());
    EXPECT_EQ(first, second);
    EXPECT_EQ(context.textureCount(), 1u);

    // A lexically different path that points at the same file is a separate cache key.
    const std::string alternatePath =
        (texturePath.parent_path() / "." / texturePath.filename()).string();
    auto* alternate = context.getTexture(alternatePath);
    ASSERT_NE(alternate, nullptr);
    EXPECT_EQ(context.textureCount(), 2u);

    context.clearTextureCache();
    EXPECT_EQ(context.textureCount(), 0u);

    auto* afterClear = context.getTexture(texturePath.string());
    ASSERT_NE(afterClear, nullptr);
    EXPECT_EQ(context.textureCount(), 1u);
}

TEST_F(RenderContextFixture, DrawTextureWithoutCameraDoesNothing) {
    RenderContextAccess context;
    context.registerRenderer(renderer);

    context.drawTexture(
        texturePath.string(),
        S2D::Vector2<float>(0.f, 0.f),
        S2D::Vector2<float>(1.f, 1.f),
        0.f);

    EXPECT_EQ(context.textureCount(), 0u);
}

TEST_F(RenderContextFixture, DrawTextureWithCameraLoadsTexture) {
    RenderContextAccess context;
    context.registerRenderer(renderer);
    auto camera = std::make_shared<S2D::Camera>();
    context.registerCamera(camera);

    context.drawTexture(
        texturePath.string(),
        S2D::Vector2<float>(10.f, 20.f),
        S2D::Vector2<float>(1.f, 1.f),
        0.f);

    EXPECT_EQ(context.textureCount(), 1u);
}

TEST(RenderContextTest, DrawTextureWithoutRendererDoesNothing) {
    S2D::RenderContext context;

    context.drawTexture(
        "missing.png",
        S2D::Vector2<float>(0.f, 0.f),
        S2D::Vector2<float>(1.f, 1.f),
        0.f);

    EXPECT_EQ(context.getRenderer(), nullptr);
}

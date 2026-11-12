//
// Tests for the UI system: Button, Text and Label.
//

#include "Engine/S2DButton.hpp"
#include "Engine/S2DLabel.hpp"
#include "Engine/S2DText.hpp"

#include "gtest/gtest.h"

#include <filesystem>
#include <string>

namespace {

constexpr ImGuiWindowFlags kDefaultWindowFlags =
    ImGuiWindowFlags_NoTitleBar |
    ImGuiWindowFlags_NoResize |
    ImGuiWindowFlags_NoMove |
    ImGuiWindowFlags_NoCollapse |
    ImGuiWindowFlags_NoBackground |
    ImGuiWindowFlags_NoScrollbar;

// Exposes protected state so the UI logic can be tested without a full ImGui frame.
class ButtonAccess : public S2D::Button {
public:
    using S2D::Button::Button;
    ButtonAccess() = default;

    const S2D::Label& label() const { return buttonLabel; }
    const S2D::Vector2<float>& position() const { return windowPos; }
    const S2D::Vector2<float>& size() const { return buttonSize; }
    const S2D::Vector4<float>& idleColor() const { return buttonColorIdle; }
    const S2D::Vector4<float>& hoveredColor() const { return buttonColorHovered; }
    const S2D::Vector4<float>& pressedColor() const { return buttonColorPressed; }
    ImGuiWindowFlags flags() const { return windowFlags; }

    bool hasCallback() const { return static_cast<bool>(onClickCallback); }
    void invokeCallback() {
        if (onClickCallback) {
            onClickCallback();
        }
    }
};

class TextAccess : public S2D::Text {
public:
    using S2D::Text::Text;
    TextAccess() = default;

    const S2D::Label& label() const { return textLabel; }
    const S2D::Vector2<float>& position() const { return windowPos; }
    ImFont* font() const { return loadedFont; }
    ImGuiWindowFlags flags() const { return windowFlags; }
};

std::filesystem::path assetPath(const std::string& fileName) {
    const std::filesystem::path sourceFile(__FILE__);
    return (sourceFile.parent_path() / "../../../examples/arcanoid/assets" / fileName)
        .lexically_normal();
}

void expectVector4Equal(const S2D::Vector4<float>& actual, const S2D::Vector4<float>& expected) {
    EXPECT_FLOAT_EQ(actual.x, expected.x);
    EXPECT_FLOAT_EQ(actual.y, expected.y);
    EXPECT_FLOAT_EQ(actual.z, expected.z);
    EXPECT_FLOAT_EQ(actual.w, expected.w);
}

class UITest : public ::testing::Test {
protected:
    void SetUp() override { ImGui::CreateContext(); }
    void TearDown() override { ImGui::DestroyContext(); }
};

} // namespace

TEST(LabelTest, DefaultValues) {
    S2D::Label label;

    EXPECT_FLOAT_EQ(label.textSize, 0.f);
    EXPECT_EQ(label.text, "text");
    EXPECT_TRUE(label.fontSource.empty());
    expectVector4Equal(label.textColor, S2D::Vector4<float>(0.f, 0.f, 0.f, 0.f));
}

TEST_F(UITest, ButtonDefaultState) {
    ButtonAccess button;

    EXPECT_EQ(button.label().text, "text");
    EXPECT_FLOAT_EQ(button.label().textSize, 0.f);
    EXPECT_TRUE(button.label().fontSource.empty());
    EXPECT_EQ(button.position(), S2D::Vector2<float>(0.f, 0.f));
    EXPECT_EQ(button.size(), S2D::Vector2<float>(0.f, 0.f));
    EXPECT_EQ(button.flags(), kDefaultWindowFlags);
    EXPECT_FALSE(button.hasCallback());
}

TEST_F(UITest, ButtonLabelAndFlagsConstructor) {
    ButtonAccess button("Quit", ImGuiWindowFlags_NoMove);

    EXPECT_EQ(button.label().text, "Quit");
    EXPECT_EQ(button.flags(), ImGuiWindowFlags_NoMove);
    EXPECT_EQ(button.position(), S2D::Vector2<float>(0.f, 0.f));
    EXPECT_EQ(button.size(), S2D::Vector2<float>(0.f, 0.f));
}

TEST_F(UITest, ButtonPositionAndSizeConstructor) {
    ButtonAccess button(
        "Play",
        S2D::Vector2<float>(10.f, 20.f),
        S2D::Vector2<float>(100.f, 50.f));

    EXPECT_EQ(button.label().text, "Play");
    EXPECT_EQ(button.position(), S2D::Vector2<float>(10.f, 20.f));
    EXPECT_EQ(button.size(), S2D::Vector2<float>(100.f, 50.f));
}

TEST_F(UITest, ButtonFullConstructor) {
    ButtonAccess button(
        "Settings",
        S2D::Vector2<float>(30.f, 40.f),
        S2D::Vector2<float>(200.f, 60.f),
        ImGuiWindowFlags_NoCollapse);

    EXPECT_EQ(button.label().text, "Settings");
    EXPECT_EQ(button.position(), S2D::Vector2<float>(30.f, 40.f));
    EXPECT_EQ(button.size(), S2D::Vector2<float>(200.f, 60.f));
    EXPECT_EQ(button.flags(), ImGuiWindowFlags_NoCollapse);
}

TEST_F(UITest, ButtonColorsCanBeChanged) {
    ButtonAccess button;

    const S2D::Vector4<float> idle(0.1f, 0.2f, 0.3f, 0.4f);
    const S2D::Vector4<float> hovered(0.5f, 0.6f, 0.7f, 0.8f);
    const S2D::Vector4<float> pressed(0.9f, 0.8f, 0.7f, 0.6f);

    button.setButtonColorIdle(idle);
    button.setButtonColorHovered(hovered);
    button.setButtonColorPressed(pressed);

    expectVector4Equal(button.idleColor(), idle);
    expectVector4Equal(button.hoveredColor(), hovered);
    expectVector4Equal(button.pressedColor(), pressed);
}

TEST_F(UITest, ButtonFontCanBeChanged) {
    ButtonAccess button;

    button.setButtonFont("some/font.ttf", 18.f);

    EXPECT_EQ(button.label().fontSource, "some/font.ttf");
    EXPECT_FLOAT_EQ(button.label().textSize, 18.f);
}

TEST_F(UITest, ButtonCallbackIsStoredAndInvoked) {
    ButtonAccess button;
    int calls = 0;

    button.setOnClickCallback([&calls] { ++calls; });

    EXPECT_TRUE(button.hasCallback());
    button.invokeCallback();
    EXPECT_EQ(calls, 1);
}

TEST_F(UITest, ButtonCallbackCanBeReplaced) {
    ButtonAccess button;
    int firstCalls = 0;
    int secondCalls = 0;

    button.setOnClickCallback([&firstCalls] { ++firstCalls; });
    button.setOnClickCallback([&secondCalls] { ++secondCalls; });
    button.invokeCallback();

    EXPECT_EQ(firstCalls, 0);
    EXPECT_EQ(secondCalls, 1);
}

TEST_F(UITest, TextDefaultState) {
    TextAccess text;

    EXPECT_EQ(text.label().text, "text");
    EXPECT_FLOAT_EQ(text.label().textSize, 0.f);
    EXPECT_TRUE(text.label().fontSource.empty());
    EXPECT_EQ(text.position(), S2D::Vector2<float>(0.f, 0.f));
    EXPECT_EQ(text.flags(), kDefaultWindowFlags);
    EXPECT_EQ(text.font(), nullptr);
}

TEST_F(UITest, TextLabelAndFlagsConstructor) {
    TextAccess text("Hello", ImGuiWindowFlags_NoResize);

    EXPECT_EQ(text.label().text, "Hello");
    EXPECT_EQ(text.flags(), ImGuiWindowFlags_NoResize);
    EXPECT_EQ(text.position(), S2D::Vector2<float>(0.f, 0.f));
    EXPECT_FLOAT_EQ(text.label().textSize, 0.f);
}

TEST_F(UITest, TextPositionAndSizeConstructor) {
    TextAccess text("Score", S2D::Vector2<float>(5.f, 15.f), 32.f);

    EXPECT_EQ(text.label().text, "Score");
    EXPECT_EQ(text.position(), S2D::Vector2<float>(5.f, 15.f));
    EXPECT_FLOAT_EQ(text.label().textSize, 32.f);
}

TEST_F(UITest, TextFullConstructor) {
    TextAccess text(
        "Lives",
        S2D::Vector2<float>(25.f, 35.f),
        48.f,
        ImGuiWindowFlags_NoBackground);

    EXPECT_EQ(text.label().text, "Lives");
    EXPECT_EQ(text.position(), S2D::Vector2<float>(25.f, 35.f));
    EXPECT_FLOAT_EQ(text.label().textSize, 48.f);
    EXPECT_EQ(text.flags(), ImGuiWindowFlags_NoBackground);
}

TEST_F(UITest, TextColorCanBeChanged) {
    TextAccess text;
    const S2D::Vector4<float> color(1.f, 0.5f, 0.25f, 1.f);

    text.setTextColor(color);

    expectVector4Equal(text.label().textColor, color);
}

TEST_F(UITest, TextFontWithEmptyPathUpdatesOnlyState) {
    TextAccess text;

    text.setTextFont("", 24.f);

    EXPECT_TRUE(text.label().fontSource.empty());
    EXPECT_FLOAT_EQ(text.label().textSize, 24.f);
    EXPECT_EQ(text.font(), nullptr);
}

TEST_F(UITest, TextFontLoadsFromFile) {
    const auto fontPath = assetPath("chintzy.ttf");
    if (!std::filesystem::exists(fontPath)) {
        GTEST_SKIP() << "Font asset not found: " << fontPath;
    }

    TextAccess text;
    text.setTextFont(fontPath.string(), 24.f);

    EXPECT_EQ(text.label().fontSource, fontPath.string());
    EXPECT_FLOAT_EQ(text.label().textSize, 24.f);
    EXPECT_NE(text.font(), nullptr);
}

//
// Created by ivan_miatselski on 2026-08-24.
//

#ifndef ENGINE_S2DSOUND_HPP
#define ENGINE_S2DSOUND_HPP

#include "Engine/S2DHelpers.hpp"
#include "Engine/S2DGameObject.hpp"

#include <string>

struct MIX_Mixer;
struct MIX_Audio;

S2DENGINE_NAMESPACE_BEGIN

class Sound: virtual public S2D::GameObject {
public:
    Sound(const std::string& soundSourcePath);
    void playSound();
    void registerSoundDeviceMixer(MIX_Mixer* newDeviceMixer);

protected:
    std::string sourcePath;
    MIX_Mixer* deviceMixer = nullptr;
    MIX_Audio* sound = nullptr;
};

S2DENGINE_NAMESPACE_END

#endif //ENGINE_S2DSOUND_HPP

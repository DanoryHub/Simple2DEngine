//
// Created by ivan_miatselski on 2026-08-24.
//

#ifndef ENGINE_S2DSOUND_HPP
#define ENGINE_S2DSOUND_HPP

#include "Engine/S2DGameObject.hpp"

#include <string>

struct MIX_Mixer;
struct MIX_Audio;

class S2DSound: virtual public S2DGameObject {
public:
    S2DSound(const std::string& soundSourcePath);
    void playSound();
    void registerSoundDeviceMixer(MIX_Mixer* newDeviceMixer);

protected:
    std::string sourcePath;
    MIX_Mixer* deviceMixer = nullptr;
    MIX_Audio* sound = nullptr;
};


#endif //ENGINE_S2DSOUND_HPP

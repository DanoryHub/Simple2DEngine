//
// Created by ivan_miatselski on 2026-08-24.
//

#include "Engine/S2DSound.hpp"

#include "SDL3_mixer/SDL_mixer.h"

S2DSound::S2DSound(const std::string& soundSourcePath){
    sourcePath = soundSourcePath;
}

void S2DSound::playSound() {
    if (sound == nullptr && deviceMixer != nullptr && !sourcePath.empty()){
        sound = MIX_LoadAudio(deviceMixer, sourcePath.c_str(), true);
    }

    MIX_PlayAudio(deviceMixer, sound);
}

void S2DSound::registerSoundDeviceMixer(MIX_Mixer *newDeviceMixer) {
    deviceMixer = newDeviceMixer;
}
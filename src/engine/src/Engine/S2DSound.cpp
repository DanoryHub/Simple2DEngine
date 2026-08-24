//
// Created by ivan_miatselski on 2026-08-24.
//

#include "Engine/S2DSound.hpp"

#include "SDL3_mixer/SDL_mixer.h"

S2DSound::S2DSound(const std::string& soundSourcePath){
    sourcePath = soundSourcePath;
}

void S2DSound::playSound() {
    if (sourcePath.empty()){
        SDL_LogError(SDL_LOG_CATEGORY_AUDIO, "Sound source path is empty");
        return;
    }

    if (deviceMixer == nullptr){
        SDL_LogError(SDL_LOG_CATEGORY_AUDIO, "Sound device mixer is not registered");
        return;
    }

    if (sound == nullptr){
        sound = MIX_LoadAudio(deviceMixer, sourcePath.c_str(), true);
    }

    MIX_PlayAudio(deviceMixer, sound);
}

void S2DSound::registerSoundDeviceMixer(MIX_Mixer *newDeviceMixer) {
    deviceMixer = newDeviceMixer;
}
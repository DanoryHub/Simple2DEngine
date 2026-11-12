//
// Created by ivan_miatselski on 2026-08-24.
//

#include "Engine/S2DSound.hpp"

#include "SDL3_mixer/SDL_mixer.h"

S2DENGINE_NAMESPACE_BEGIN

Sound::Sound(const std::string& soundSourcePath){
    sourcePath = soundSourcePath;
}

void Sound::playSound() {
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

void Sound::registerSoundDeviceMixer(MIX_Mixer *newDeviceMixer) {
    deviceMixer = newDeviceMixer;
}

S2DENGINE_NAMESPACE_END

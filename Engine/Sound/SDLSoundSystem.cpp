#include "SDLSoundSystem.h"
//#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3/SDL.h>


dae::SDLSoundSystem::SDLSoundSystem()
{
	SDL_InitSubSystem(SDL_INIT_AUDIO); //:(
}

void dae::SDLSoundSystem::LoadSound(const SoundId id, const std::string& path)
{
}

void dae::SDLSoundSystem::Play(const SoundId id, const float volume)
{
}

void dae::SDLSoundSystem::Stop(const SoundId id)
{
}

void dae::SDLSoundSystem::MuteAll()
{
}

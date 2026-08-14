#include "SDLSoundSystem.h"
#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <string>
#include <stdexcept>

namespace fs = std::filesystem;
dae::SDLSoundSystem::SDLSoundSystem()
{
	if (!MIX_Init()) {
		SDL_Log("MIX_Init failed: %s", SDL_GetError());
	}
	else {
		SDL_Log("SDL_mixer is ready!");
	}

	m_Mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);
	if (!m_Mixer)
	{
		SDL_Log("Unable to load m_Mixer! SDL_mixer error: %s\n", SDL_GetError());
	}

	m_EffectsTrack = MIX_CreateTrack(m_Mixer);
	if (!m_EffectsTrack)
	{
		SDL_Log("Unable to load m_EffectsTrack! SDL_mixer error: %s\n", SDL_GetError());
	}

}

dae::SDLSoundSystem::~SDLSoundSystem()
{
	for (auto& audio : m_Audios)
	{
		MIX_DestroyAudio(audio.second);
	}
	if (m_EffectsTrack) MIX_DestroyTrack(m_EffectsTrack);
	if (m_Mixer) MIX_DestroyMixer(m_Mixer);
}

void dae::SDLSoundSystem::LoadAudio(const SoundId id, const char* path)
{
	std::string audioPath{ "Data/Audio/" };
	MIX_Audio* audio = MIX_LoadAudio(m_Mixer, (audioPath + path).c_str(), false);

	if (!audio)
	{
		SDL_Log("Unable to load sound! SDL_mixer error: %s\n", SDL_GetError());
		return;
	}
	m_Audios[id] = audio;
}

void dae::SDLSoundSystem::PlayAudio(const SoundId id, const float volume)
{
	if (m_IsMuted)
		return;

	auto it = m_Audios.find(id);

	if (it != m_Audios.end())
	{
		if (!MIX_SetTrackAudio(m_EffectsTrack, it->second))
		{
			SDL_Log("Unable to load MIX_SetTrackAudio! SDL_mixer error: %s\n", SDL_GetError());
		}


		if (!MIX_SetTrackGain(m_EffectsTrack, volume))
		{
			SDL_Log("Unable to load MIX_SetTrackGain! SDL_mixer error: %s\n", SDL_GetError());
		}

		if (!MIX_PlayTrack(m_EffectsTrack, 0))
		{
			SDL_Log("Unable to load MIX_PlayTrack! SDL_mixer error: %s\n", SDL_GetError());
		}
	}

}

void dae::SDLSoundSystem::Stop(const SoundId id)
{
}

void dae::SDLSoundSystem::MuteAll()
{
	m_IsMuted = !m_IsMuted;
	if (m_IsMuted)
	{
		MIX_PauseTrack(m_EffectsTrack);
	}
	else
	{
		MIX_ResumeTrack(m_EffectsTrack);

	}
}

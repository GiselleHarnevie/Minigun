#pragma once
#include "SoundSystem.h"
#include <string>
#include <unordered_map>
#include <SDL3_mixer/SDL_mixer.h>
#include <memory>
#include <filesystem>


namespace dae
{
	class SDLSoundSystem : public SoundSystem
	{
	public:
		SDLSoundSystem();
		~SDLSoundSystem();

	private:
		// Inherited via SoundSystem
		void LoadAudio(const SoundId id, const char* path) override;
		//void CreateTrack();
		void PlayAudio(const SoundId id, const float volume) override;
		void Stop(const SoundId id) override;
		void MuteAll() override;

		std::unordered_map<SoundId, MIX_Audio*> m_Audios;

		MIX_Mixer* m_Mixer;
		MIX_Track* m_EffectsTrack;

		std::filesystem::path m_dataPath;

		bool m_IsMuted = false;
	};

}

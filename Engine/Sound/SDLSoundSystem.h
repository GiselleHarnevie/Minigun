#pragma once
#include "SoundSystem.h"
#include <string>
#include <unordered_map>


namespace dae
{
	struct Mix_Chunk;
	class SDLSoundSystem : public SoundSystem
	{
	public:
		SDLSoundSystem();
		~SDLSoundSystem() = default;

	private:
		// Inherited via SoundSystem
		void LoadSound(const SoundId id, const std::string& path) override;
		void Play(const SoundId id, const float volume) override;
		void Stop(const SoundId id) override;
		void MuteAll() override;

		bool m_IsMuted{ false };
		std::unordered_map<SoundId, Mix_Chunk*> m_Sounds;
	};

}
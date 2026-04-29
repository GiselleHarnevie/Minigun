#pragma once
#include "SoundSystem.h"

namespace dae
{
	class SDLSoundSystem : public SoundSystem
	{
	public:

	private:
		// Inherited via SoundSystem
		void Play(const SoundId id, const float volume) override;

		void Stop(const SoundId id) override;

		void Mute(const SoundId id) override;

	};

}
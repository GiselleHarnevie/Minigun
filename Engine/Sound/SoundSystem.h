#pragma once
#include <string>

namespace dae
{
	using SoundId = unsigned short;
	class SoundSystem
	{
	public:
		virtual ~SoundSystem() = default;
	
		virtual void LoadAudio(const SoundId id, const char* path) = 0;
		virtual void PlayAudio(const SoundId id, const float volume) = 0;
		virtual void Stop(const SoundId id) = 0;
		virtual void MuteAll() = 0;
	private:

	};

	class NullSoundSystem : public SoundSystem
	{
	public:

	private:
		// Inherited via SoundSystem
		void LoadAudio(const SoundId , const char*) override {};

		void PlayAudio(const SoundId , const float ) override {};

		void Stop(const SoundId ) override {};

		void MuteAll() override {};

	};
}
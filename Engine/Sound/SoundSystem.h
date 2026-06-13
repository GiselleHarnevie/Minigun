#pragma once
#include <string>

namespace dae
{
	using SoundId = unsigned short;
	class SoundSystem
	{
	public:
		virtual ~SoundSystem() = default;
	
		virtual void LoadSound(const SoundId id, const std::string& path) = 0;
		virtual void Play(const SoundId id, const float volume) = 0;
		virtual void Stop(const SoundId id) = 0;
		virtual void MuteAll() = 0;
	private:

	};

	class NullSoundSystem : public SoundSystem
	{
	public:

	private:
		// Inherited via SoundSystem
		void LoadSound(const SoundId , const std::string& ) override {};

		void Play(const SoundId , const float ) override {};

		void Stop(const SoundId ) override {};

		void MuteAll() override {};

	};
}
#pragma once

namespace dae
{
	using SoundId = unsigned short;
	class SoundSystem
	{
	public:
		virtual ~SoundSystem() = default;
	
		virtual void Play(const SoundId id, const float volume) = 0;
		virtual void Stop(const SoundId id) = 0;
		virtual void Mute(const SoundId id) = 0;
	private:

	};

	class NullSoundSystem : public SoundSystem
	{
	public:

	private:
		// Inherited via SoundSystem
		void Play(const SoundId id, const float volume) override;
		void Stop(const SoundId id) override;
		void Mute(const SoundId id) override;
	};
}
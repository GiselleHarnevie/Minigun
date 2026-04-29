#pragma once
#include <memory>
#include "SoundSystem.h"

namespace dae
{
	
	class ServiceLocator final
	{
	public:
		static SoundSystem& GetSoundSystem() { return *ssInstance; }
		static void RegisterSoundSystem(std::unique_ptr<SoundSystem>&& ss)
		{
			ssInstance = ss == nullptr ? std::make_unique<NullSoundSystem>() : std::move(ss);
		}

		ServiceLocator(const ServiceLocator& other) = delete;
		ServiceLocator(ServiceLocator&& other) = delete;
		ServiceLocator& operator=(const ServiceLocator& other) = delete;
		ServiceLocator& operator=(ServiceLocator&& other) = delete;

	private:
		static std::unique_ptr<SoundSystem> ssInstance;

	};
}


#include "ServiceLocator.h"
#include "SoundSystem.h"

std::unique_ptr<dae::SoundSystem> dae::ServiceLocator::ssInstance{ std::make_unique<dae::NullSoundSystem>() };
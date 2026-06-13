#include "MuteCommand.h"
#include "GameObject.h"
#include "Sound/ServiceLocator.h"

dae::MuteCommand::MuteCommand(GameObject* gameObject)
	: m_pGameObject{ gameObject }
{
}

void dae::MuteCommand::Execute(float )
{
	ServiceLocator::GetSoundSystem().MuteAll();
}

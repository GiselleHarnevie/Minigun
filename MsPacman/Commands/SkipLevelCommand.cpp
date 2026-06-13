#include "SkipLevelCommand.h"
#include "GameObject.h"
#include "../LevelManager.h"
#include <SDL3/SDL.h>

dae::SkipLevelCommand::SkipLevelCommand(GameObject* gameObject)
	: m_pGameObject{gameObject}
{
}

void dae::SkipLevelCommand::Execute(float )
{
	SDL_Log("Skip Level");
	LevelManager::GetInstance().SkipLevel();
}

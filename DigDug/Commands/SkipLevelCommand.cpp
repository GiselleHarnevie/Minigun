#include "SkipLevelCommand.h"
#include "GameObject.h"
#include <SDL3/SDL.h>
#include "DigDug.h"

dae::SkipLevelCommand::SkipLevelCommand(GameObject* gameObject)
	: m_pGameObject{gameObject}
{
}

void dae::SkipLevelCommand::Execute(float )
{
	auto& gameScene = *dae::SceneManager::GetInstance().GetScene("Gameplay");

	int nextLevel = dae::LevelManager::GetInstance().GetCurrentLevelIndex() + 1;

	if (nextLevel >= dae::LevelManager::GetInstance().GetTotalLevelCount())
	{
		dae::GameState::GetInstance().RequestGameOver();
		return;
	}

	dae::LevelManager::GetInstance().SetLevelIndex(nextLevel);
	LoadGameplayLevel(dae::GameState::GetInstance().GetGameMode(), nextLevel, gameScene);
}

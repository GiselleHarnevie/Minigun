#include "LevelManager.h"
#include <stdexcept>
#include <fstream>
#include <SDL3/SDL_log.h>
#include <iostream>
#include "Event.h"
#include "GameState.h"

void dae::LevelManager::ReadLevelJson(std::string filePath)
{
	std::ifstream file(filePath);
	if (!file.is_open()) { throw std::runtime_error(std::string("Didnt load" + filePath)); }

	json data = json::parse(file);

	for (const auto& level : data["playField"])
	{
		std::vector<int> levelData = level.get<std::vector<int>>();
		std::unique_ptr<Level> levelptr = std::make_unique<Level>(levelData);
		m_Levels.push_back(std::move(levelptr));
	}

}

dae::Level* dae::LevelManager::GetLevel(int levelIndex)
{
	if (levelIndex < 0 || levelIndex >= static_cast<int>(m_Levels.size()))
	{
		return m_Levels[0].get();
	}

	return m_Levels[levelIndex].get();
}

void dae::LevelManager::SetLevelIndex(int levelIndex)
{
	m_CurrentLevelIndex = levelIndex;
}

int dae::LevelManager::GetTotalLevelCount()
{
	return static_cast<int>(m_Levels.size());
}

int dae::LevelManager::GetCurrentLevelIndex() const
{
	return m_CurrentLevelIndex;
}

void dae::LevelManager::OnLevelAdvance(std::function<void()> callback)
{
	m_OnLevelAdvance = std::move(callback);
}

void dae::LevelManager::OnNotify(unsigned int event, GameObject*)
{
	if (event == EventsId::enemyKilled)
	{
		if (m_EnemyCount > 0)
		{
			m_EnemyCount--;
			std::cout << "Enemy Count: " << m_EnemyCount << std::endl;
		}

		if (m_EnemyCount <= 0)
		{
			int nextLevel = m_CurrentLevelIndex + 1;

			if (nextLevel >= GetTotalLevelCount())
			{
				
				return;
			}

			m_CurrentLevelIndex = nextLevel;

			dae::GameState::GetInstance().RequestSceneReload();
		}
	}
}

void dae::LevelManager::SetEnemyCount(int count)
{
	std::cout << "Enemy Count: " << count << std::endl;
	m_EnemyCount = count;
}

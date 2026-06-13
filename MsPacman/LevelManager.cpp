#include "LevelManager.h"
#include <stdexcept>
#include <fstream>
#include <SDL3/SDL_log.h>

void dae::LevelManager::ReadLevelJson(std::string filePath)
{
	std::ifstream file(filePath);
	if (!file.is_open()) { throw std::runtime_error(std::string("Didnt load" + filePath)); }

	json data = json::parse(file);

	for (const auto& level : data["levels"])
	{
		std::vector<int> levelData = level.get<std::vector<int>>();
		std::unique_ptr<Level> levelptr = std::make_unique<Level>(levelData);
		m_Levels.push_back(std::move(levelptr));
	}

}

dae::Level* dae::LevelManager::GetLevel(int levelIndex)
{
	if (levelIndex < 0 || levelIndex> static_cast<int>(m_Levels.size()))
	{
		return m_Levels[0].get();
	}

	return m_Levels[levelIndex].get();
}

int dae::LevelManager::GetTotalLevelCount()
{
	return static_cast<int>(m_Levels.size());
}

void dae::LevelManager::SkipLevel()
{
	m_CurrentLevelIndex = (m_CurrentLevelIndex + 1) % m_Levels.size();
	SDL_Log("Loaded level %d", m_CurrentLevelIndex);
}

//void dae::LevelManager::LoadLevel(int levelIndex)
//{
//	if (levelIndex < 0 || levelIndex> static_cast<int>(m_Levels.size()))
//	{
//		m_CurrentLevelIndex = levelIndex;
//	}
//}



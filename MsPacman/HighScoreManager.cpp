#include "HighScoreManager.h"
#include "nlohmann/json.hpp"
#include <fstream>
#include <algorithm>

using json = nlohmann::json;

void dae::HighScoreManager::Load()
{
	std::ifstream file("Data/Highscore.json");
	if (!file.is_open()) return;

	json data = json::parse(file);
	m_Entries.clear();

	for (const auto& entry : data)
	{
		HighscoreEntry e;
		e.name = entry["name"];
		e.score = entry["score"];
		m_Entries.push_back(e);
	}
}

void dae::HighScoreManager::Save()
{
	json data = json::array();

	for (const auto& entry : m_Entries)
	{
		data.push_back({ {"name", entry.name}, {"score", entry.score} });
	}

	std::ofstream file("Data/Highscore.json");
	file << data.dump(2);
}

void dae::HighScoreManager::AddEntry(const std::string& name, int score)
{
	m_Entries.push_back({ name, score });

	std::sort(m_Entries.begin(), m_Entries.end(), [](const HighscoreEntry& a, const HighscoreEntry& b)
		{
			return a.score > b.score;
		});

	if (static_cast<int>(m_Entries.size()) > MAX_ENTRIES)
		m_Entries.resize(MAX_ENTRIES);
}

int dae::HighScoreManager::GetHighestScore()
{
	int highestEntry{};
	for (auto& entry : m_Entries)
	{
		if (entry.score > highestEntry)
		{
			highestEntry = entry.score;
		}
	}
	
	return highestEntry;
}

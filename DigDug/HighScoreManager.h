#pragma once
#include "Singleton.h"
#include <string>
#include <vector>

namespace dae
{

	struct HighscoreEntry
	{
		std::string name{};
		int score{0};
	};
	class HighScoreManager :public Singleton<HighScoreManager>
	{
	public:

		void Load();
		void Save();

		void AddEntry(const std::string& name, int score);
		const std::vector<HighscoreEntry>& GetEntries() const { return m_Entries; };
		int GetHighestScore();

		//
		

	private:
		std::vector<HighscoreEntry> m_Entries;
		const int MAX_ENTRIES{5};

	};
}
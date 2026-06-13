#include <vector>
#include <memory>
#include <string>
#include "Singleton.h"
#include "nlohmann/json.hpp"
#include "Level.h"

using json = nlohmann::json;

namespace dae
{

	class LevelManager : public Singleton<LevelManager>
	{
	public:
		void ReadLevelJson(std::string filePath);

		//void LoadLevel(int index);
		Level* GetLevel(int levelIndex);
		int GetTotalLevelCount();

		void SkipLevel();

	private:
		std::vector<std::unique_ptr<Level>> m_Levels;
		int m_CurrentLevelIndex = 0;
	};
}
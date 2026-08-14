#include <vector>
#include <memory>
#include <string>
#include "Singleton.h"
#include "nlohmann/json.hpp"
#include "Level.h"
#include "../Engine/Observer/Observer.h"

using json = nlohmann::json;

namespace dae
{

	class LevelManager : public Singleton<LevelManager> , public Observer
	{
	public:
		void ReadLevelJson(std::string filePath);

		Level* GetLevel(int levelIndex);

		void SetLevelIndex(int levelIndex);

		void SetEnemyCount(int count);

		int GetTotalLevelCount();
		int GetCurrentLevelIndex() const;

		void OnLevelAdvance(std::function<void()> callback);
	private:
		std::vector<std::unique_ptr<Level>> m_Levels;
		int m_CurrentLevelIndex = 0;
		int m_EnemyCount= 0 ;

		std::function<void()> m_OnLevelAdvance;

		// Inherited via Observer
		void OnNotify(unsigned int event, GameObject* actor) override;

	};
}
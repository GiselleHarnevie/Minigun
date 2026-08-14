#pragma once
#include "Singleton.h"
#include <string>
#include <vector>
#include "GameSettings.h"
#include "Observer/Observer.h"

namespace dae
{

	class GameState final :public Singleton<GameState>, public Observer
	{
	public:
		int GetScore() const { return m_Score; }
		void SetScore(int score) { m_Score = score; }

		int GetLives() const { return m_Lives; }
		void SetLives(int lives) { m_Lives = lives; }

		void ResetForNewGame();

		dae::GameMode GetGameMode() const { return m_Mode; }
		void SetGameMode(dae::GameMode mode) { m_Mode = mode; }

		void RequestSceneReload() { m_SceneReloadRequested = true; }
		bool ConsumeSceneReloadRequest()
		{
			if (m_SceneReloadRequested)
			{
				m_SceneReloadRequested = false;
				return true;
			}
			return false;
		}

		void RequestGameOver() { m_GameOverRequested = true; }
		bool ConsumeGameOverRequest()
		{
			if (m_GameOverRequested)
			{
				m_GameOverRequested = false;
				return true;
			}
			return false;
		}

		void RequestGameStart() { m_GameStartRequested = true; }
		bool ConsumeGameStartRequest()
		{
			if (m_GameStartRequested)
			{
				m_GameStartRequested = false;
				return true;
			}
			return false;
		}

	private:
		int m_Score{ 0 };
		int m_Lives{ 3 };
		bool m_SceneReloadRequested{ false };
		bool m_GameOverRequested{ false };
		bool m_GameStartRequested{ false };

		dae::GameMode m_Mode{ dae::GameMode::SinglePlayer };

		// Inherited via Observer
		void OnNotify(unsigned int event, GameObject* actor) override;
	};
}
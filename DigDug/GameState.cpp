#include "GameState.h"
#include "Event.h"
#include "./Components/LivesComponent.h"
#include "./Components/ScoreComponent.h"
#include "GameObject.h"
#include <iostream>

void dae::GameState::ResetForNewGame()
{
	std::cout << "ResetForNewGame()" << std::endl;
	m_Score = 0;
	m_Lives = 3;

}

void dae::GameState::OnNotify(unsigned int event, GameObject* actor)
{
	if (event == EventsId::playerDied)
	{
		LivesComponent* livesComp = actor->GetComponent<dae::LivesComponent>();
		m_Lives = livesComp->GetLivesLeft();

		if (m_Lives <= 0)
		{
			RequestGameOver();
		}
		else
		{
			RequestSceneReload();
		}
	}
	else if (event == EventsId::scoreUpdate)
	{
		ScoreComponent* scoreComp = actor->GetComponent<dae::ScoreComponent>();
		m_Score = scoreComp->GetScore();
	}
}


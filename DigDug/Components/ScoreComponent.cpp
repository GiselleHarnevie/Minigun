#include "ScoreComponent.h"
#include "GameObject.h"
#include "Event.h"

dae::ScoreComponent::ScoreComponent(GameObject* owner, int currentScore)
	: Component(owner)
	,m_CurrentScore{ currentScore }
{

}

void dae::ScoreComponent::AddScore(int score)
{ 
	m_CurrentScore += score;
	m_Subject.NotifyObservers(EventsId::scoreUpdate, this->GetOwner());
}

int dae::ScoreComponent::GetScore() const
{
	return m_CurrentScore;
}


void dae::ScoreComponent::FixedUpdate(const float )
{
}

void dae::ScoreComponent::Update(float )
{
}

void dae::ScoreComponent::Render() const
{

}

void dae::ScoreComponent::OnNotify(unsigned int event, GameObject* )
{
	if (event == EventsId::scoreLayerOne) AddScore(200);
	else if (event == EventsId::scoreLayerTwo) AddScore(300);
	else if (event == EventsId::scoreLayerThree) AddScore(400);
	else if (event == EventsId::scoreLayerFour) AddScore(500);
}


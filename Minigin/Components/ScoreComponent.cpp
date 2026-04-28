#include "ScoreComponent.h"
#include "GameObject.h"
#include "Event.h"

dae::ScoreComponent::ScoreComponent(GameObject* owner)
	: Component(owner)
	,m_CurrentScore{}
{

}

void dae::ScoreComponent::AddScore(int score)
{ 
	m_CurrentScore += score;
	m_Subject.NotifyObservers(EventsId::pickUp, this->GetOwner());
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


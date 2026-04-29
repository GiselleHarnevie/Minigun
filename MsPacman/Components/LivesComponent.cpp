#include "LivesComponent.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "Observer/Event.h"
#include "Observer/Sdbm.h"

dae::LivesComponent::LivesComponent(GameObject* owner, int livesAmount)
	: Component(owner),
	m_CurrentLivesLeft{ livesAmount }
{
	
}

void dae::LivesComponent::TakeLife()
{
	if (m_CurrentLivesLeft)
		--m_CurrentLivesLeft;

	m_Subject.NotifyObservers(EventsId::playerDied, this->GetOwner());
}

int dae::LivesComponent::GetLivesLeft() const
{
	return m_CurrentLivesLeft;
}

void dae::LivesComponent::FixedUpdate(const float)
{

}

void dae::LivesComponent::Update(float)
{
}

void dae::LivesComponent::Render() const
{

}

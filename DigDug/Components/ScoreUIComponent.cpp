#include "ScoreUIComponent.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "Event.h"
#include "ScoreComponent.h"

dae::ScoreUIComponent::ScoreUIComponent(GameObject* owner)
	:Component(owner)
{
	m_pTextComponent = this->GetOwner()->GetComponent<TextComponent>();
}

void dae::ScoreUIComponent::InitScoreTextDisplay(int score)
{
	m_pTextComponent->SetText(std::to_string(score));
}

void dae::ScoreUIComponent::FixedUpdate(const float)
{
}

void dae::ScoreUIComponent::Update(float)
{
}

void dae::ScoreUIComponent::Render() const
{
}

void dae::ScoreUIComponent::OnNotify(unsigned int event, GameObject* actor)
{
	if (event == EventsId::scoreUpdate)
	{
		m_pTextComponent->SetText(std::to_string(actor->GetComponent<ScoreComponent>()->GetScore()));
	}
}

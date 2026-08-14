#include "RoundUIComponent.h"
#include "GameObject.h"
#include "Event.h"


dae::RoundUIComponent::RoundUIComponent(GameObject* owner, int roundNumber)
	: Component(owner)
{
	m_pTextComponent = this->GetOwner()->GetComponent<TextComponent>();

	m_pTextComponent->SetText(std::to_string(roundNumber));
}

void dae::RoundUIComponent::FixedUpdate(const float)
{
}

void dae::RoundUIComponent::Update(float)
{

}

void dae::RoundUIComponent::Render() const
{
}

void dae::RoundUIComponent::OnNotify(unsigned int , GameObject* )
{
}

#include "LivesUIComponent.h"
#include "GameObject.h"
#include "Event.h"
#include "LivesComponent.h"

dae::LivesUIComponent::LivesUIComponent(GameObject* owner)
	: Component(owner)
{
	m_pTextComponent = this->GetOwner()->GetComponent<TextComponent>();

}

void dae::LivesUIComponent::InitLivesTextDisplay(int currentLivesLeft)
{
	m_pTextComponent->SetText("Lives:" + std::to_string(currentLivesLeft));
}

void dae::LivesUIComponent::FixedUpdate(const float)
{
}

void dae::LivesUIComponent::Update(float)
{

}

void dae::LivesUIComponent::Render() const
{
}

void dae::LivesUIComponent::OnNotify(unsigned int event, GameObject* actor)
{
	if (event == EventsId::playerDied)
	{
		m_pTextComponent->SetText("Lives:"+ std::to_string(actor->GetComponent<LivesComponent>()->GetLivesLeft()));
	}
}

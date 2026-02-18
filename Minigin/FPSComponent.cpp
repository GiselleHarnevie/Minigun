#include "FPSComponent.h"
#include "GameObject.h"
#include "TextComponent.h"
#include <iostream>

dae::FPSComponent::FPSComponent(GameObject* gameObject)
	: Component(gameObject),
	m_FrameCount{},
	m_FPSTimer{},
	m_FPS{},
	textComponent{ GetOwner()->GetComponent<TextComponent>() }
{
}

void dae::FPSComponent::Update(float elapsedSec)
{
	m_FPSTimer += elapsedSec;
	m_FrameCount++;
	if (m_FPSTimer >= 1.0f)
	{
		m_FPS = m_FrameCount;
		m_FrameCount = 0;
		m_FPSTimer -= 1.f;
		if (textComponent)
		{
			textComponent->SetText("FPS: " + std::to_string(m_FPS));
		}
	}
}

int dae::FPSComponent::GetFPS() const
{
	return m_FPS;
}

void dae::FPSComponent::Render() const
{
}

void dae::FPSComponent::FixedUpdate(const float /*fixedTimeStep*/)
{
}
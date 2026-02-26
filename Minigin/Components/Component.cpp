#include "Component.h"
#include "GameObject.h"

dae::Component::Component(GameObject* pOwner)
	: m_pOwner(pOwner),
	m_IsDestroyed{}
{
}

dae::GameObject* dae::Component::GetOwner() const
{
	return m_pOwner;
}

void dae::Component::Destroy()
{
	m_IsDestroyed = true;
};

bool dae::Component::IsDestroyed() const
{
	return m_IsDestroyed;
};

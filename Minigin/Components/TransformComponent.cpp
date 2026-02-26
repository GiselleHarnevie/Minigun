#include "TransformComponent.h"

dae::TransformComponent::TransformComponent(GameObject* gameObject)
	:Component(gameObject)
	, m_position{}
{
}

void dae::TransformComponent::SetPosition(const float x, const float y, const float z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
}

void dae::TransformComponent::SetPosition(const glm::vec3& position) 
{ 
	m_position = position; 
}

void dae::TransformComponent::FixedUpdate(const float /*fixedTimeStep*/)
{
}

void dae::TransformComponent::Update(float /*elapsedSec*/)
{
}

void dae::TransformComponent::Render() const
{
}

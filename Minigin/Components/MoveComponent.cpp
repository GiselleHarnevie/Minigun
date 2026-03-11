#include "MoveComponent.h"
#include "GameObject.h"

dae::MoveComponent::MoveComponent(GameObject* owner, float speed)
	:Component(owner),
	m_pGameObject{ owner },
	m_Speed{ speed }
{

}

void dae::MoveComponent::Move(const glm::vec2& direction, float deltaTime)
{
	glm::vec3 currentPos{ m_pGameObject->GetLocalPosition() };

	m_pGameObject->SetLocalPosition(
		glm::vec3{ currentPos.x + (direction.x * m_Speed * deltaTime),
		currentPos.y + (direction.y * m_Speed * deltaTime),
		currentPos.z
		});

}


void dae::MoveComponent::FixedUpdate(const float)
{
}

void dae::MoveComponent::Update(float)
{
}

void dae::MoveComponent::Render() const
{
}

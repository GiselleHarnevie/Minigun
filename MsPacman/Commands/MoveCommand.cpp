#include "MoveCommand.h"
#include "GameObject.h"
#include "Components/PlayerComponent.h"



dae::MoveCommand::MoveCommand(GameObject* gameObject, const glm::vec2& direction)
	:m_pGameObject{gameObject},
	m_Direction{direction}
	//m_Speed{speed}
{

}

void dae::MoveCommand::Execute(float)
{
	m_pGameObject->GetComponent<PlayerComponent>()->SetDesiredDirection(m_Direction);

	//m_pGameObject->SetLocalPosition(
	//	glm::vec3{ currentPos.x + (m_Direction.x * m_Speed * deltaTime),
	//	currentPos.y + (m_Direction.y * m_Speed * deltaTime),
	//	currentPos.z
	//	});
}


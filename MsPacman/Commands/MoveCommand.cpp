#include "MoveCommand.h"
#include "GameObject.h"



dae::MoveCommand::MoveCommand(GameObject* gameObject, const glm::vec2& direction, float speed)
	:m_pGameObject{gameObject},
	m_Direction{direction},
	m_Speed{speed}
{

}

void dae::MoveCommand::Execute(float deltaTime)
{
	glm::vec3 currentPos{ m_pGameObject->GetLocalPosition() };

	m_pGameObject->SetLocalPosition(
		glm::vec3{ currentPos.x + (m_Direction.x * m_Speed * deltaTime),
		currentPos.y + (m_Direction.y * m_Speed * deltaTime),
		currentPos.z
		});

}


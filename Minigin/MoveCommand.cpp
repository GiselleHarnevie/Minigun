#include "MoveCommand.h"
#include "Components/MoveComponent.h"
#include "GameObject.h"



dae::MoveCommand::MoveCommand(GameObject* gameObject, const glm::vec2& direction)
	:m_pGameObject{gameObject},
	m_Direction{direction}
{

}

void dae::MoveCommand::Execute(float deltaTime)
{
	m_pGameObject->GetComponent<MoveComponent>()->Move(m_Direction, deltaTime);
}


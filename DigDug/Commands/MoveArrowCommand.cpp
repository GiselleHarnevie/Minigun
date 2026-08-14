#include "MoveArrowCommand.h"
#include "GameObject.h"
#include "../Components/SelectionComponent.h"


dae::MoveArrowCommand::MoveArrowCommand(GameObject* gameObject, const glm::vec2& direction)
	: m_pGameObject{gameObject},
	m_ArrowDirection{direction}
{
}

void dae::MoveArrowCommand::Execute(float )
{
	//Get arrow direction
	m_pGameObject->GetComponent<dae::SelectionComponent>()->GetArrowDirection(m_ArrowDirection);
}

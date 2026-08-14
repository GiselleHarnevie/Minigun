#include "StopCommand.h"
#include "GameObject.h"
#include "Components/PlayerComponent.h"
#include "GameSettings.h"



dae::StopCommand::StopCommand(GameObject* gameObject, const glm::vec2& direction)
	:m_pGameObject{ gameObject },
	m_Direction{ direction }
{

}

void dae::StopCommand::Execute(float )
{
	m_pGameObject->GetComponent<PlayerComponent>()->StopDesiredDirection(m_Direction);

}
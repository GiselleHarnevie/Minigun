#include "PickUpCommand.h"
#include "Components/ScoreComponent.h"

dae::PickUpCommand::PickUpCommand(GameObject* gameObject, int amount)
	:m_pGameObject{gameObject},
	m_Amount{amount}
{
}

void dae::PickUpCommand::Execute(float)
{
	m_pGameObject->GetComponent<ScoreComponent>()->AddScore(m_Amount);
}

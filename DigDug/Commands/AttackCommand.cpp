#include "AttackCommand.h"
#include "GameObject.h"
#include "../Components/PlayerComponent.h"

dae::AttackCommand::AttackCommand(GameObject* gameObject)
	: m_pGameObject{ gameObject }
{
}

void dae::AttackCommand::Execute(float )
{
	m_pGameObject->GetComponent<PlayerComponent>()->StarkAttack();
}

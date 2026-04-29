#include "KillCommand.h"
#include "Components/LivesComponent.h"
#include "GameObject.h"

dae::KillCommand::KillCommand(GameObject* gameObject)
	: m_pGameObject{gameObject}
{
}

void dae::KillCommand::Execute(float)
{
	//Take One life
	m_pGameObject->GetComponent<LivesComponent>()->TakeLife();
}

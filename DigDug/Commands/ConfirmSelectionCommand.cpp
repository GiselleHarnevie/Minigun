#include "ConfirmSelectionCommand.h"
#include "GameObject.h"
#include"../Components/SelectionComponent.h"
#include "DigDug.h"
#include "SceneManager.h"
#include "../../Engine/Input/InputManager.h"

dae::ConfirmSelectionCommand::ConfirmSelectionCommand(GameObject* gameObject)
	: m_pGameObject{ gameObject }
{
}

void dae::ConfirmSelectionCommand::Execute(float)
{

	//Get confirm selection
	auto mode = m_pGameObject->GetComponent<SelectionComponent>()->GetSelectedMode();

	dae::GameState::GetInstance().SetGameMode(mode);
	dae::GameState::GetInstance().RequestGameStart();
	
}

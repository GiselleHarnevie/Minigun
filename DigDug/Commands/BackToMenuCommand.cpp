#include "BackToMenuCommand.h"
#include "GameObject.h"

#include "DigDug.h"
#include "SceneManager.h"
#include "../../Engine/Input/InputManager.h"

dae::BackToMenuCommand::BackToMenuCommand(GameObject* )
{
}

void dae::BackToMenuCommand::Execute(float)
{

	MainMenuScene();
	dae::SceneManager::GetInstance().SetActiveScene("Menu");
	
}

#pragma once
#include "Input/Command.h"
#include <glm/glm.hpp>
#include <SDL3/SDL.h>

namespace dae
{
	class GameObject;
	class ConfirmSelectionCommand :public Command
	{
	public:
		ConfirmSelectionCommand(GameObject* gameObject);

		// Inherited via Command
		void Execute(float deltaTime) override;
	private:
		GameObject* m_pGameObject;
	};
}
#pragma once
#include "Input/Command.h"
#include <glm/glm.hpp>
#include <SDL3/SDL.h>

namespace dae
{
	class GameObject;
	class BackToMenuCommand :public Command
	{
	public:
		BackToMenuCommand(GameObject* gameObject);

		// Inherited via Command
		void Execute(float deltaTime) override;
	private:
	};
}
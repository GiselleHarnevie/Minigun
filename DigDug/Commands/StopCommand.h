#pragma once
#include "Input/Command.h"
#include <glm/glm.hpp>
#include <SDL3/SDL.h>

namespace dae
{
	class StopCommand :public Command
	{
	public:
		StopCommand(GameObject* gameObject, const glm::vec2& direction);
		virtual ~StopCommand() = default;


		// Inherited via Command
		void Execute(float deltaTime) override;
	private:

		GameObject* m_pGameObject;
		glm::vec2 m_Direction;
	};
}
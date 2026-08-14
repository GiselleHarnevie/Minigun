#pragma once
#include "Input/Command.h"
#include <glm/glm.hpp>
#include <SDL3/SDL.h>


namespace dae
{
	class GameObject;
	class MoveArrowCommand :public Command
	{
	public:
		MoveArrowCommand(GameObject* gameObject, const glm::vec2& arrowDirection);

		// Inherited via Command
		void Execute(float deltaTime) override;
	private:
		GameObject* m_pGameObject;
		glm::vec2 m_ArrowDirection;
	};
}
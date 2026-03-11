#pragma once
#include "Command.h"
#include <glm/glm.hpp>

namespace dae
{
	class MoveComponent;
	class MoveCommand :public Command
	{
	public:
		MoveCommand(GameObject* gameObject, const glm::vec2& direction);
		virtual ~MoveCommand() =default;


		// Inherited via Command
		void Execute(float deltaTime) override;
	private:

		GameObject* m_pGameObject;
		glm::vec2 m_Direction;
	};
}
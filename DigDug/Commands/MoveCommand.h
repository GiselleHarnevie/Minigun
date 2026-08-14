#pragma once
#include "Input/Command.h"
#include <glm/glm.hpp>
#include <SDL3/SDL.h>

namespace dae
{
	class MoveComponent;
	class MoveCommand :public Command
	{
	public:
		MoveCommand(GameObject* gameObject, const glm::vec2& direction, SDL_FlipMode flipMode, double spriteRotation);
		virtual ~MoveCommand() = default;


		// Inherited via Command
		void Execute(float deltaTime) override;
	private:

		GameObject* m_pGameObject;
		glm::vec2 m_Direction;
		//float m_Speed;

		SDL_FlipMode m_FlipMode;
		double m_SpriteRotation;
	};
}
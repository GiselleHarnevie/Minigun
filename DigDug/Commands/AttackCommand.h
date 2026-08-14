#pragma once
#include "Input/Command.h"

namespace dae
{
	class GameObject;
	class AttackCommand :public Command
	{
	public:
		AttackCommand(GameObject* gameObject);


	private:
		// Inherited via Command
		void Execute(float deltaTime) override;

		GameObject* m_pGameObject;

	};
}
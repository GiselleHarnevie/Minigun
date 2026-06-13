#pragma once
#include "Input/Command.h"

namespace dae
{
	class GameObject;
	class MuteCommand :public Command
	{
	public:
		MuteCommand(GameObject* gameObject);

		// Inherited via Command
		void Execute(float deltaTime) override;
	private:
		GameObject* m_pGameObject;
	};
}
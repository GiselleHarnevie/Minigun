#pragma once
#include "Command.h"

namespace dae
{
	class GameObject;
	class KillCommand :public Command
	{
	public:
		KillCommand(GameObject* gameObject);

		// Inherited via Command
		void Execute(float deltaTime) override;
	private:
		GameObject* m_pGameObject;
	};
}
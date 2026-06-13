#pragma once
#include "Input/Command.h"

namespace dae
{
	class GameObject;
	class SkipLevelCommand :public Command
	{
	public:
		SkipLevelCommand(GameObject* gameObject);

		// Inherited via Command
		void Execute(float deltaTime) override;
	private:
		GameObject* m_pGameObject;
	};
}
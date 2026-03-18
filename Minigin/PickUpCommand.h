#pragma once
#include "Command.h"

namespace dae
{
	class LivesComponent;
	class PickUpCommand :public Command
	{
	public:
		PickUpCommand(GameObject* gameObject, int amount);

	private:
		GameObject* m_pGameObject;
		int m_Amount;

		// Inherited via Command
		void Execute(float deltaTime) override;

	};

}
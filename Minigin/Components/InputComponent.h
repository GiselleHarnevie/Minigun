#pragma once
#include "Component.h"
#include "MoveCommand.h"

namespace dae
{

	class InputComponent : public Component
	{
	public:
		InputComponent(GameObject* owner);
		~InputComponent();

		void HandleBinds();

	private:
		// Inherited via Component
		void FixedUpdate(const float fixedTimeStep) override;
		void Update(float elapsedSec) override;
		void Render() const override;

		MoveCommand* m_pMoveUp;
		MoveCommand* m_pMoveDown;
		MoveCommand* m_pMoveRight;
		MoveCommand* m_pMoveLeft;
	};

}

#pragma once
#include "Component.h"
#include <memory>
#include "Input/InputManager.h"


namespace dae
{
	class MoveCommand;
	class KillCommand;
	class PickUpCommand;
	class InputComponent : public Component
	{
	public:
		InputComponent(GameObject* owner);
		~InputComponent();

		void UsingKeyboard();


		void UsingGamepad(int gamepadIndex);

	private:
		// Inherited via Component
		void FixedUpdate(const float fixedTimeStep) override;
		void Update(float elapsedSec) override;
		void Render() const override;

		dae::InputManager& m_Input = InputManager::GetInstance();

		MoveCommand* m_pMoveUp;
		MoveCommand* m_pMoveDown;
		MoveCommand* m_pMoveRight;
		MoveCommand* m_pMoveLeft;

		KillCommand* m_pKillPlayer;

		PickUpCommand* m_pPickUpSmall;
		PickUpCommand* m_pPickUpBig;
	};

}

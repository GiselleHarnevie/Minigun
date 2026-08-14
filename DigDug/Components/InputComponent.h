#pragma once
#include "Component.h"
#include <memory>
#include "Input/InputManager.h"


namespace dae
{
	class MoveCommand;
	class KillCommand;
	class PickUpCommand;
	class StopCommand;

	class SkipLevelCommand;
	class MuteCommand;

	class AttackCommand;

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

		StopCommand* m_pStopUp;
		StopCommand* m_pStopDown;
		StopCommand* m_pStopRight;
		StopCommand* m_pStopLeft;

		SkipLevelCommand* m_pSkipLevel;
		MuteCommand* m_Mute;

		AttackCommand* m_pAttack;
		/*KillCommand* m_pKillPlayer;

		PickUpCommand* m_pPickUpSmall;
		PickUpCommand* m_pPickUpBig;*/

	};

}

#include "InputComponent.h"
#include "Input/InputManager.h"
#include "Commands/MoveCommand.h"
#include "Commands/KillCommand.h"
#include "Commands/PickUpCommand.h"
#include "Commands/StopCommand.h"
#include "Commands/SkipLevelCommand.h"
#include "Commands/MuteCommand.h"
#include "Commands/AttackCommand.h"

dae::InputComponent::InputComponent(GameObject* owner)
	:Component(owner)
{
	m_pMoveLeft = m_Input.AddCommand<MoveCommand>(owner, glm::vec2{ -1.f,0.f }, SDL_FLIP_NONE, 0);
	m_pMoveRight = m_Input.AddCommand<MoveCommand>(owner, glm::vec2{ 1.f,0.f }, SDL_FLIP_HORIZONTAL, 0);
	m_pMoveUp = m_Input.AddCommand<MoveCommand>(owner, glm::vec2{ 0.f,-1.f }, SDL_FLIP_NONE, 90.0);
	m_pMoveDown = m_Input.AddCommand<MoveCommand>(owner, glm::vec2{ 0.f,1.f }, SDL_FLIP_NONE, -90.0);

	m_pStopLeft = m_Input.AddCommand<StopCommand>(owner, glm::vec2{ 0.f,0.f });
	m_pStopRight = m_Input.AddCommand<StopCommand>(owner, glm::vec2{ 0.f,0.f });
	m_pStopUp = m_Input.AddCommand<StopCommand>(owner, glm::vec2{ 0.f,0.f });
	m_pStopDown = m_Input.AddCommand<StopCommand>(owner, glm::vec2{ 0.f,0.f });

	m_pSkipLevel = m_Input.AddCommand<SkipLevelCommand>(nullptr);
	m_Mute = m_Input.AddCommand<MuteCommand>(nullptr);

	m_pAttack = m_Input.AddCommand<AttackCommand>(owner);

	//m_pKillPlayer = m_Input.AddCommand<KillCommand>(owner);
	//m_pPickUpSmall = m_Input.AddCommand<PickUpCommand>(owner, 10);
	//m_pPickUpBig = m_Input.AddCommand<PickUpCommand>(owner, 100);
}


dae::InputComponent::~InputComponent()
{
}

void dae::InputComponent::UsingKeyboard()
{
	m_Input.BindCommand(SDL_SCANCODE_W, InputState::Held, m_pMoveUp);
	m_Input.BindCommand(SDL_SCANCODE_S, InputState::Held, m_pMoveDown);
	m_Input.BindCommand(SDL_SCANCODE_A, InputState::Held, m_pMoveLeft);
	m_Input.BindCommand(SDL_SCANCODE_D, InputState::Held, m_pMoveRight);

	m_Input.BindCommand(SDL_SCANCODE_W, InputState::Released, m_pStopUp);
	m_Input.BindCommand(SDL_SCANCODE_S, InputState::Released, m_pStopDown);
	m_Input.BindCommand(SDL_SCANCODE_A, InputState::Released, m_pStopLeft);
	m_Input.BindCommand(SDL_SCANCODE_D, InputState::Released, m_pStopRight);

	m_Input.BindCommand(SDL_SCANCODE_F1, dae::InputState::Pressed, m_pSkipLevel);
	m_Input.BindCommand(SDL_SCANCODE_F2, dae::InputState::Pressed, m_Mute);

	m_Input.BindCommand(SDL_SCANCODE_SPACE, dae::InputState::Pressed, m_pAttack);


	//m_Input.BindCommand(SDL_SCANCODE_C, InputState::Pressed, m_pKillPlayer);
	//m_Input.BindCommand(SDL_SCANCODE_Z, InputState::Pressed, m_pPickUpSmall);
	//m_Input.BindCommand(SDL_SCANCODE_X, InputState::Pressed, m_pPickUpBig);

}

void dae::InputComponent::UsingGamepad(int index)
{
	m_Input.AddGamepad(index);

	m_Input.BindCommand(index, static_cast<unsigned int>(GamepadButton::DPAD_UP), InputState::Held, m_pMoveUp);
	m_Input.BindCommand(index, static_cast<unsigned int>(GamepadButton::DPAD_DOWN), InputState::Held, m_pMoveDown);
	m_Input.BindCommand(index, static_cast<unsigned int>(GamepadButton::DPAD_LEFT), InputState::Held, m_pMoveLeft);
	m_Input.BindCommand(index, static_cast<unsigned int>(GamepadButton::DPAD_RIGHT), InputState::Held, m_pMoveRight);

	m_Input.BindCommand(index,  static_cast<unsigned int>(GamepadButton::DPAD_UP)  , InputState::Released, m_pStopUp);
	m_Input.BindCommand(index, static_cast<unsigned int>(GamepadButton::DPAD_DOWN) , InputState::Released, m_pStopDown);
	m_Input.BindCommand(index, static_cast<unsigned int>(GamepadButton::DPAD_LEFT) , InputState::Released, m_pStopLeft);
	m_Input.BindCommand(index, static_cast<unsigned int>(GamepadButton::DPAD_RIGHT), InputState::Released, m_pStopRight);

	m_Input.BindCommand(index, static_cast<unsigned int>(GamepadButton::A), InputState::Held, m_pAttack);

	//m_Input.BindCommand(index, static_cast<unsigned int>(GamepadButton::X), InputState::Pressed, m_pKillPlayer);
	//m_Input.BindCommand(index, static_cast<unsigned int>(GamepadButton::A), InputState::Pressed, m_pPickUpSmall);
	//m_Input.BindCommand(index, static_cast<unsigned int>(GamepadButton::B), InputState::Pressed, m_pPickUpBig);


}

void dae::InputComponent::FixedUpdate(const float)
{
}

void dae::InputComponent::Update(float)
{
}

void dae::InputComponent::Render() const
{
}

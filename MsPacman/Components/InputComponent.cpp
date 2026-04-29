#include "InputComponent.h"
#include "Input/InputManager.h"
#include "Commands/MoveCommand.h"
#include "Commands/KillCommand.h"
#include "Commands/PickUpCommand.h"
#include <windows.h>
#include <Xinput.h>

dae::InputComponent::InputComponent(GameObject* owner)
	:Component(owner)
{
	m_pMoveUp = m_Input.AddCommand<MoveCommand>(owner, glm::vec2{ 0.f,-1.f }, 200.f);
	m_pMoveDown = m_Input.AddCommand<MoveCommand>(owner, glm::vec2{ 0.f,1.f }, 200.f);
	m_pMoveLeft = m_Input.AddCommand<MoveCommand>(owner, glm::vec2{ -1.f,0.f }, 200.f);
	m_pMoveRight = m_Input.AddCommand<MoveCommand>(owner, glm::vec2{ 1.f,0.f }, 200.f);

	m_pKillPlayer = m_Input.AddCommand<KillCommand>(owner);

	m_pPickUpSmall = m_Input.AddCommand<PickUpCommand>(owner, 10);
	m_pPickUpBig = m_Input.AddCommand<PickUpCommand>(owner, 100);

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

	m_Input.BindCommand(SDL_SCANCODE_C, InputState::Pressed, m_pKillPlayer);
	m_Input.BindCommand(SDL_SCANCODE_Z, InputState::Pressed, m_pPickUpSmall);
	m_Input.BindCommand(SDL_SCANCODE_X, InputState::Pressed, m_pPickUpBig);

}

void dae::InputComponent::UsingGamepad(int index)
{
	m_Input.AddGamepad(index);

	m_Input.BindCommand(index, XINPUT_GAMEPAD_DPAD_UP, InputState::Held, m_pMoveUp);
	m_Input.BindCommand(index, XINPUT_GAMEPAD_DPAD_DOWN, InputState::Held, m_pMoveDown);
	m_Input.BindCommand(index, XINPUT_GAMEPAD_DPAD_LEFT, InputState::Held, m_pMoveLeft);
	m_Input.BindCommand(index, XINPUT_GAMEPAD_DPAD_RIGHT, InputState::Held, m_pMoveRight);
	m_Input.BindCommand(index, XINPUT_GAMEPAD_X, InputState::Pressed, m_pKillPlayer);
	m_Input.BindCommand(index, XINPUT_GAMEPAD_A, InputState::Pressed, m_pPickUpSmall);
	m_Input.BindCommand(index, XINPUT_GAMEPAD_B, InputState::Pressed, m_pPickUpBig);


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

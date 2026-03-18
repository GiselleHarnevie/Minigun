#include "InputComponent.h"
#include "InputManager.h"
#include "MoveCommand.h"
#include "KillCommand.h"
#include "PickUpCommand.h"


dae::InputComponent::InputComponent(GameObject* owner)
	:Component(owner)
{
	auto& input = InputManager::GetInstance();
	m_pMoveUp = input.AddCommand<MoveCommand>(owner, glm::vec2{ 0.f,-1.f },200.f);
	m_pMoveDown = input.AddCommand<MoveCommand>(owner, glm::vec2{ 0.f,1.f },200.f);
	m_pMoveLeft = input.AddCommand<MoveCommand>(owner, glm::vec2{ -1.f,0.f }, 200.f);
	m_pMoveRight = input.AddCommand<MoveCommand>(owner, glm::vec2{ 1.f,0.f },200.f);

	m_pKillPlayer = input.AddCommand<KillCommand>(owner);

	m_pPickUpSmall = input.AddCommand<PickUpCommand>(owner,10);
	m_pPickUpBig = input.AddCommand<PickUpCommand>(owner,100);

	HandleBinds();
}


dae::InputComponent::~InputComponent()
{
}

void dae::InputComponent::HandleBinds()
{
	auto& input = InputManager::GetInstance();

	input.BindCommand(SDL_SCANCODE_W, InputState::Pressed, m_pMoveUp);
	input.BindCommand(SDL_SCANCODE_S, InputState::Pressed, m_pMoveDown);
	input.BindCommand(SDL_SCANCODE_A, InputState::Pressed, m_pMoveLeft);
	input.BindCommand(SDL_SCANCODE_D, InputState::Pressed, m_pMoveRight);
	input.BindCommand(SDL_SCANCODE_C, InputState::Pressed, m_pKillPlayer);
	input.BindCommand(SDL_SCANCODE_Z, InputState::Pressed, m_pPickUpSmall);
	input.BindCommand(SDL_SCANCODE_X, InputState::Pressed, m_pPickUpBig);
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

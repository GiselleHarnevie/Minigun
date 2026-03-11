#include "InputComponent.h"
#include "InputManager.h"
#include "MoveCommand.h"


dae::InputComponent::InputComponent(GameObject* owner)
	:Component(owner)
{
	m_pMoveUp = InputManager::GetInstance().AddCommand<MoveCommand>(owner, glm::vec2{ 0.f,-1.f });
	m_pMoveDown = InputManager::GetInstance().AddCommand<MoveCommand>(owner, glm::vec2{ 0.f,1.f });
	m_pMoveLeft = InputManager::GetInstance().AddCommand<MoveCommand>(owner, glm::vec2{ -1.f,0.f });
	m_pMoveRight = InputManager::GetInstance().AddCommand<MoveCommand>(owner, glm::vec2{ 1.f,0.f });

	HandleBinds();
}


dae::InputComponent::~InputComponent()
{
}

void dae::InputComponent::HandleBinds()
{
	auto& input = InputManager::GetInstance();

	input.BindCommand(SDL_SCANCODE_W, InputState::Held, m_pMoveUp);
	input.BindCommand(SDL_SCANCODE_S, InputState::Held, m_pMoveDown);
	input.BindCommand(SDL_SCANCODE_A, InputState::Held, m_pMoveLeft);
	input.BindCommand(SDL_SCANCODE_D, InputState::Held, m_pMoveRight);
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

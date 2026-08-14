#include "GameObject.h"
#include "SelectionComponent.h"
#include "TextureComponent.h"

#include "../../Engine/Input/InputManager.h"
#include "Commands/ConfirmSelectionCommand.h"
#include "Commands/MoveArrowCommand.h"

dae::SelectionComponent::SelectionComponent(GameObject* owner)
	:Component(owner),
	m_TextureComponent{ owner->GetComponent<TextureComponent>() },
	m_Direction{},
	m_SelectedIndex{},
	m_OffsetArrow{30.f}
{
	m_ArrowPositions = {
		glm::vec2{ dae::ONE_PLAYER_TEXT_POS.x - m_OffsetArrow,dae::ONE_PLAYER_TEXT_POS.y },
		glm::vec2{ dae::TWO_PLAYER_TEXT_POS.x - m_OffsetArrow,dae::TWO_PLAYER_TEXT_POS.y } };
	GetOwner()->SetLocalPosition(glm::vec2{ dae::ONE_PLAYER_TEXT_POS.x - m_OffsetArrow,dae::ONE_PLAYER_TEXT_POS.y });

	//-Menu Selectino Input bindings
	auto& input = InputManager::GetInstance();
	m_pMoveArrowUp = input.AddCommand<MoveArrowCommand>(owner, glm::vec2{ 0.f,-1.f });
	m_pMoveArrowDown = input.AddCommand<MoveArrowCommand>(owner, glm::vec2{ 0.f,1.f });
	m_pConfirmSelection = input.AddCommand<ConfirmSelectionCommand>(owner);

	input.BindCommand(SDL_SCANCODE_W, InputState::Pressed, m_pMoveArrowUp);
	input.BindCommand(SDL_SCANCODE_S, InputState::Pressed, m_pMoveArrowDown);
	input.BindCommand(SDL_SCANCODE_SPACE, InputState::Pressed, m_pConfirmSelection);

	input.AddGamepad(0);
	input.BindCommand(0, static_cast<unsigned int>(GamepadButton::DPAD_UP), InputState::Pressed, m_pMoveArrowUp);
	input.BindCommand(0, static_cast<unsigned int>(GamepadButton::DPAD_DOWN), InputState::Pressed, m_pMoveArrowDown);
	input.BindCommand(0, static_cast<unsigned int>(GamepadButton::A), InputState::Pressed, m_pConfirmSelection);
}

void dae::SelectionComponent::GetArrowDirection(const glm::vec2& direction)
{
	m_Direction = direction;

	int count = static_cast<int>(m_ArrowPositions.size());
	m_SelectedIndex = (m_SelectedIndex + static_cast<int>(direction.y) + count) % count;

	GetOwner()->SetLocalPosition(m_ArrowPositions[m_SelectedIndex]);
}

dae::GameMode dae::SelectionComponent::GetSelectedMode() const
{
	return static_cast<dae::GameMode>(m_SelectedIndex);
}

void dae::SelectionComponent::FixedUpdate(const float)
{
}

void dae::SelectionComponent::Update(float)
{
}

void dae::SelectionComponent::Render() const
{
}
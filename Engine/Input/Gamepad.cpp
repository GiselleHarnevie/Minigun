#include "Gamepad.h"
#include <windows.h>
#include <Xinput.h>
#include <optional>

dae::Gamepad::Gamepad(int gamepadIndex)
	:m_ControllerIndex{ gamepadIndex },
	m_CurrentState{},
	m_PreviousState{},
	m_ButtonsPressedThisFrame{},
	m_ButtonsReleasedThisFrame{}
{
	CheckGamepadConnected();
}

dae::Gamepad::~Gamepad()
{
}

bool dae::Gamepad::CheckGamepadConnected() const
{
	XINPUT_STATE state;
	ZeroMemory(&state, sizeof(XINPUT_STATE));

	if (XInputGetState(m_ControllerIndex, &state) == ERROR_SUCCESS)
	{
		return true;
	}

	return false;
}

void dae::Gamepad::ProcessGamepadInput()
{
	CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(m_ControllerIndex, &m_CurrentState);

	auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
	m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
	m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);

}

int dae::Gamepad::GetGamepadIndex() const
{
	return m_ControllerIndex;
}

bool dae::Gamepad::IsDownThisFrame(unsigned int button) const
{
	return m_ButtonsPressedThisFrame & button;
}

bool dae::Gamepad::IsUpThisFrame(unsigned int button) const
{
	return m_ButtonsReleasedThisFrame & button;
}

bool dae::Gamepad::IsPressed(unsigned int button) const
{
	return (m_CurrentState.Gamepad.wButtons & button) != 0;
}
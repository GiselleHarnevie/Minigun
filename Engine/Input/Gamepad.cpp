#include "Gamepad.h"
#include <optional>

#ifdef _WIN32
#include <windows.h>
#include <Xinput.h>

/// <summary>
/// Pimpl
/// </summary>
class dae::Gamepad::Impl final
{
public:
	explicit Impl(int gamepadIndex);

	bool CheckGamepadConnected() const;
	void ProcessGamepadInput();
	int GetGamepadIndex() const;

	bool IsDownThisFrame(unsigned int button) const;
	bool IsUpThisFrame(unsigned int button) const;
	bool IsPressed(unsigned int button) const;

private:
	int m_ControllerIndex;
	XINPUT_STATE m_CurrentState;
	XINPUT_STATE m_PreviousState;
	int m_ButtonsPressedThisFrame;
	int m_ButtonsReleasedThisFrame;
};

dae::Gamepad::Impl::Impl(int gamepadIndex)
	:m_ControllerIndex{ gamepadIndex },
	m_CurrentState{},
	m_PreviousState{},
	m_ButtonsPressedThisFrame{},
	m_ButtonsReleasedThisFrame{}
{
	CheckGamepadConnected();
}

bool dae::Gamepad::Impl::CheckGamepadConnected() const
{
	XINPUT_STATE state;
	ZeroMemory(&state, sizeof(XINPUT_STATE));

	if (XInputGetState(m_ControllerIndex, &state) == ERROR_SUCCESS)
	{
		return true;
	}

	return false;
}

void dae::Gamepad::Impl::ProcessGamepadInput()
{
	CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(m_ControllerIndex, &m_CurrentState);

	auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
	m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
	m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);
}

int dae::Gamepad::Impl::GetGamepadIndex() const
{
	return m_ControllerIndex;
}

bool dae::Gamepad::Impl::IsDownThisFrame(unsigned int button) const
{
	return m_ButtonsPressedThisFrame & button;
}

bool dae::Gamepad::Impl::IsUpThisFrame(unsigned int button) const
{
	return m_ButtonsReleasedThisFrame & button;

}

bool dae::Gamepad::Impl::IsPressed(unsigned int button) const
{
	return (m_CurrentState.Gamepad.wButtons & button) != 0;
}

#else
//using Sdl later

class dae::Gamepad::Impl final
{
public:
	explicit Impl(int gamepadIndex) :m_ControllerIndex{ gamepadIndex } {};

	bool CheckGamepadConnected() const { return false; };
	void ProcessGamepadInput() {};
	int GetGamepadIndex() const { return m_ControllerIndex; };

	bool IsDownThisFrame(unsigned int button) const { return false; };
	bool IsUpThisFrame(unsigned int button) const { return false; };
	bool IsPressed(unsigned int button) const { return false; };

private:
	int m_ControllerIndex;
};

#endif // _WIN32

/// <summary>
/// Gamepad
/// </summary>
dae::Gamepad::Gamepad(int gamepadIndex)
	:m_pImpl{ std::make_unique<Impl>(gamepadIndex) }
{
}

dae::Gamepad::~Gamepad() = default;

bool dae::Gamepad::CheckGamepadConnected() const
{
	return m_pImpl->CheckGamepadConnected();
}

void dae::Gamepad::ProcessGamepadInput()
{
	m_pImpl->ProcessGamepadInput();

}

int dae::Gamepad::GetGamepadIndex() const
{
	return m_pImpl->GetGamepadIndex();
}

bool dae::Gamepad::IsDownThisFrame(unsigned int button) const
{
	return m_pImpl->IsDownThisFrame(button);
}

bool dae::Gamepad::IsUpThisFrame(unsigned int button) const
{
	return m_pImpl->IsUpThisFrame(button);
}

bool dae::Gamepad::IsPressed(unsigned int button) const
{
	return m_pImpl->IsPressed(button);
}

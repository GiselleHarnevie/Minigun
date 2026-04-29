#pragma once
#include <windows.h>
#include <Xinput.h>

namespace dae
{
	
	class Gamepad
	{
	public:
		Gamepad(int gamepadIndex);
		~Gamepad();

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

}
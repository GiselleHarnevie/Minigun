#pragma once
#include <memory>

namespace dae
{

	class Gamepad
	{
	public:
		Gamepad(int gamepadIndex);
		~Gamepad();

		Gamepad(const Gamepad& other) = delete;
		Gamepad(Gamepad&& other) = default;
		Gamepad& operator=(const Gamepad& other) = delete;
		Gamepad& operator=(Gamepad&& other) = default;

		bool CheckGamepadConnected() const;
		void ProcessGamepadInput();
		int GetGamepadIndex() const;

		bool IsDownThisFrame(unsigned int button) const;
		bool IsUpThisFrame(unsigned int button) const;
		bool IsPressed(unsigned int button) const;
	private:
		//pimpl
		class Impl;
		std::unique_ptr<Impl> m_pImpl;
	};



}
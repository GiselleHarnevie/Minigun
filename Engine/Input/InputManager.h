#pragma once
#include "../Singleton.h"
#include <vector>
#include <unordered_map>
#include <SDL3/SDL.h>
#include <memory>
#include "Command.h"
#include "Gamepad.h"
#include <array>

namespace dae
{
	enum class InputState
	{
		Pressed = 0,
		Released = 1,
		Held = 2
	};

	enum class GamepadButton :unsigned int {
		DPAD_UP =			0x0001,
		DPAD_DOWN =			0x0002,
		DPAD_LEFT =			0x0004,
		DPAD_RIGHT =		0x0008,

		START =				0x0010,
		BACK =				0x0020,

		LEFT_THUMBSTICK =	0x0040,
		RIGHT_THUMBSTICK =	0x0080,
		LEFT_SHOULDER =		0x0100,
		RIGHT_SHOULDER =	0x0200,

		A =					0x1000,
		B =					0x2001,
		X =					0x4001,
		Y =					0x8001
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		template<typename T, typename ...Args>
			requires std::is_base_of_v<Command, T>
		T* AddCommand(GameObject* gameObject, Args&&... args)
		{
			auto command = std::make_unique<T>(gameObject, std::forward<Args>(args)...);
			T* ptr = command.get();
			m_Commands.emplace_back(std::move(command));
			return ptr;
		}

	

		bool ProcessInput(float deltaTime);
		void BindCommand(SDL_Scancode key, InputState state, Command* command);

		//BIND XINPUT
		void BindCommand(int gamepadIndex, unsigned int button, InputState state, Command* command);

		//UNBIND COMMAND
		void UnbindCommand();

		void AddGamepad(int index);

		dae::Gamepad* GetGamepad(int index);

	private:
		std::vector<std::unique_ptr<Command>> m_Commands;

		std::unordered_map<SDL_Scancode, std::unordered_map<InputState, Command*>> m_KeyboardBindings;

		using StateMap = std::unordered_map<InputState, Command*>;
		using ButtonMap = std::unordered_map<unsigned int, StateMap>;

		std::array<ButtonMap, 4> m_GamepadBindings;
		std::array<std::unique_ptr<Gamepad>, 4> m_Gamepads;
	};

}

#pragma once
#include "Singleton.h"
#include <vector>
#include <unordered_map>
#include <SDL3/SDL.h>
#include <memory>
#include "Command.h"

namespace dae
{
	enum class InputState
	{
		Pressed = 0,
		Released = 1,
		Held = 2
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

	private:
		std::vector<std::unique_ptr<Command>> m_Commands;

		std::unordered_map<SDL_Scancode, std::unordered_map<InputState, Command*>> m_KeyboardBindings;
		std::unordered_map<unsigned int, std::unordered_map<InputState, Command*>> m_GamepadBindings;
	};

}

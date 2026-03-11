#include <SDL3/SDL.h>
#include "InputManager.h"
#include <backends/imgui_impl_sdl3.h>
#include "Command.h"
#include "MoveCommand.h"

bool dae::InputManager::ProcessInput(float deltaTime)
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_EVENT_QUIT)
		{
			return false;
		}

		if (e.type == SDL_EVENT_KEY_DOWN) //pressed
		{

			auto key = e.key.scancode;
			auto it = m_KeyboardBindings.find(key);
			if (it != m_KeyboardBindings.end())
			{
				auto commandIt = it->second.find(InputState::Pressed);
				if (commandIt != it->second.end())
				{
					commandIt->second->Execute(deltaTime);
				}
			}
		}
		if (e.type == SDL_EVENT_KEY_UP) //released
		{
			auto key = e.key.scancode;
			auto it = m_KeyboardBindings.find(key);
			if (it != m_KeyboardBindings.end())
			{
				auto commandIt = it->second.find(InputState::Released);
				if (commandIt != it->second.end())
				{
					commandIt->second->Execute(deltaTime);
				}
			}
		}


		const bool* keyboard{ SDL_GetKeyboardState(nullptr) };
		for (auto& [key, states] : m_KeyboardBindings)
		{
			if (keyboard[key])
			{
				auto it = states.find(InputState::Held);
				if (it != states.end())
				{
					it->second->Execute(deltaTime);
				}
			}
		}

		//ImGui_ImplSDL3_ProcessEvent(&e);
	}

	return true;
}


void dae::InputManager::BindCommand(SDL_Scancode key, InputState state, Command* command)
{
	m_KeyboardBindings[key][state] = command;
}


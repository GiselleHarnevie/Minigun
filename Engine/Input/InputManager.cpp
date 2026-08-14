#include "InputManager.h"
#include <SDL3/SDL.h>
#include <backends/imgui_impl_sdl3.h>
#include "Command.h"
#include "Gamepad.h"
#include <optional>

bool dae::InputManager::ProcessInput(float deltaTime)
{
	SDL_PumpEvents();
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
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

		//ImGui_ImplSDL3_ProcessEvent(&e);
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

	//Process gamepad input
	for (auto& gamepad : m_Gamepads)
	{
		if (!gamepad) continue;
		if (!gamepad->CheckGamepadConnected()) continue;

		gamepad->ProcessGamepadInput();

		ButtonMap& buttonMap = m_GamepadBindings[gamepad.get()->GetGamepadIndex()];

		for (auto& [key, states] : buttonMap)
		{
			//if button pushed
			if (gamepad->IsDownThisFrame(key))
			{
				auto it = states.find(InputState::Pressed);
				if (it != states.end())
				{
					it->second->Execute(deltaTime);
				}
			}

			//if button released
			if (gamepad->IsUpThisFrame(key))
			{
				auto it = states.find(InputState::Released);
				if (it != states.end())
				{
					it->second->Execute(deltaTime);
				}
			}

			//if button held
			if (gamepad->IsPressed(key))
			{
				auto it = states.find(InputState::Held);
				if (it != states.end())
				{
					it->second->Execute(deltaTime);
				}
			}
		}

	}

	return true;
}


void dae::InputManager::BindCommand(SDL_Scancode key, InputState state, Command* command)
{
	m_KeyboardBindings[key][state] = command;
}

void dae::InputManager::BindCommand(int gamepadIndex, unsigned int button, InputState state, Command* command)
{
	if (gamepadIndex < 0 || gamepadIndex > 3) return;

	m_GamepadBindings[gamepadIndex][button][state] = command;
}


void dae::InputManager::UnbindAllCommands()
{
	m_KeyboardBindings.clear();
	
	for (auto& buttonMap : m_GamepadBindings)
	{
		buttonMap.clear();
	}
}

void dae::InputManager::AddGamepad(int index)
{
	if (index < 0 || index > 3) return;

	if (!m_Gamepads[index])
	{
		std::unique_ptr<Gamepad> gamepad = std::make_unique<Gamepad>(index);
		m_Gamepads[index] = std::move(gamepad);
	}

}

dae::Gamepad* dae::InputManager::GetGamepad(int index)
{
	return m_Gamepads[index].get();
}
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#if _DEBUG && __has_include(<vld.h>)
#include <vld.h>
#endif

#ifdef _WIN32
#include <windows.h>
#include <Xinput.h>
#include <consoleapi.h>
#endif // _WIN32

#include "DigDug.h"

#include <string>
#include <filesystem>
#include <iostream>
namespace fs = std::filesystem;

static void load()
{
	DigDugSetup();
	MainMenuScene();
	dae::SceneManager::GetInstance().SetActiveScene("Menu");
}

int main(int, char* []) {
#if __EMSCRIPTEN__
	fs::path data_location = "";
#else
	fs::path data_location = "./Data/";
	if (!fs::exists(data_location))
		data_location = "../Data/";
#endif
	dae::Minigin engine(data_location, dae::WINDOW_WIDTH, dae::WINDOW_HEIGHT);
	engine.Run(load);
	return 0;
}
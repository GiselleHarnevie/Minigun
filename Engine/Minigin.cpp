#include <stdexcept>
#include <sstream>
#include <iostream>
#include <chrono>
#include <thread>

#if WIN32
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#endif

#include <SDL3/SDL.h>
//#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_mixer/SDL_mixer.h>
#include "Minigin.h"
#include "Input/InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"

using namespace std::chrono;

SDL_Window* g_window{};
const int MS_PER_FRAME = 16;
const float FIXED_TIME_STEP = 1.0f / 60.0f;

void LogSDLVersion(const std::string& message, int major, int minor, int patch)
{
#if WIN32
	std::stringstream ss;
	ss << message << major << "." << minor << "." << patch << "\n";
	OutputDebugString(ss.str().c_str());
#else
	std::cout << message << major << "." << minor << "." << patch << "\n";
#endif
}

#ifdef __EMSCRIPTEN__
#include "emscripten.h"

void LoopCallback(void* arg)
{
	static_cast<dae::Minigin*>(arg)->RunOneFrame();
}
#endif

// Why bother with this? Because sometimes students have a different SDL version installed on their pc.
// That is not a problem unless for some reason the dll's from this project are not copied next to the exe.
// These entries in the debug output help to identify that issue.
void PrintSDLVersion()
{
	LogSDLVersion("Compiled with SDL", SDL_MAJOR_VERSION, SDL_MINOR_VERSION, SDL_MICRO_VERSION);
	int version = SDL_GetVersion();
	LogSDLVersion("Linked with SDL ", SDL_VERSIONNUM_MAJOR(version), SDL_VERSIONNUM_MINOR(version), SDL_VERSIONNUM_MICRO(version));
	// LogSDLVersion("Compiled with SDL_image ",SDL_IMAGE_MAJOR_VERSION, SDL_IMAGE_MINOR_VERSION, SDL_IMAGE_MICRO_VERSION);
	// version = IMG_Version();
	// LogSDLVersion("Linked with SDL_image ", SDL_VERSIONNUM_MAJOR(version), SDL_VERSIONNUM_MINOR(version), SDL_VERSIONNUM_MICRO(version));
	LogSDLVersion("Compiled with SDL_ttf ", SDL_TTF_MAJOR_VERSION, SDL_TTF_MINOR_VERSION, SDL_TTF_MICRO_VERSION);
	version = TTF_Version();
	LogSDLVersion("Linked with SDL_ttf ", SDL_VERSIONNUM_MAJOR(version), SDL_VERSIONNUM_MINOR(version), SDL_VERSIONNUM_MICRO(version));
}

dae::Minigin::Minigin(const std::filesystem::path& dataPath, int windowWidth, int windowHeight)
{
	PrintSDLVersion();

	if (!SDL_InitSubSystem(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
	{
		SDL_Log("Renderer error: %s", SDL_GetError());
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}


#if _DEBUG
	AllocConsole();
	auto err = freopen("CONOUT$", "wt", stdout);
	if (!err)
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}
	SetConsoleTitle("Debug Console");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);

#endif

	g_window = SDL_CreateWindow(
		"Programming 4 assignment",
		windowWidth,
		windowHeight,
		SDL_WINDOW_OPENGL
	);
	if (g_window == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}


	Renderer::GetInstance().Init(g_window);
	ResourceManager::GetInstance().Init(dataPath);
}

dae::Minigin::~Minigin()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(g_window);
	g_window = nullptr;


	MIX_Quit();
	TTF_Quit();
	SDL_Quit();
}

//TODO : [Week1] Implement game loop and Update
void dae::Minigin::Run(const std::function<void()>& load)
{
	load();
#ifndef __EMSCRIPTEN__
	while (!m_quit)
	{
		RunOneFrame();
	}
#else
	emscripten_set_main_loop_arg(&LoopCallback, this, 0, true);
#endif
}


auto lastTime = std::chrono::high_resolution_clock::now();
float lag = 0.0f;
void dae::Minigin::RunOneFrame()
{
	const auto currentTime = std::chrono::high_resolution_clock::now();
	const float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
	lastTime = currentTime;
	lag += deltaTime;

	m_quit = !InputManager::GetInstance().ProcessInput(deltaTime);

	while (lag >= FIXED_TIME_STEP)
	{
		SceneManager::GetInstance().FixedUpdate(FIXED_TIME_STEP);
		lag -= FIXED_TIME_STEP;
	}
	SceneManager::GetInstance().Update(deltaTime);
	Renderer::GetInstance().Render();

	const auto sleepTime = currentTime + milliseconds(MS_PER_FRAME) - high_resolution_clock::now();

	std::this_thread::sleep_for(sleepTime);
}
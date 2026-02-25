#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#if _DEBUG && __has_include(<vld.h>)
#include <vld.h>
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
//#include "TextObject.h"
#include "Scene.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "TextureComponent.h"
#include "RotatorComponent.h"

#include <filesystem>
namespace fs = std::filesystem;

static void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	auto go = std::make_unique<dae::GameObject>();
	go->AddComponent<dae::TextureComponent>("background.png");
	scene.Add(std::move(go));

	go = std::make_unique<dae::GameObject>();
	go->AddComponent<dae::TextureComponent>("logo.png");
	go->SetLocalPosition(glm::vec3{ 358, 180 ,0});
	scene.Add(std::move(go));

	auto to = std::make_unique<dae::GameObject>();
	to->AddComponent<dae::TextComponent>("Programming 4 Assignment", font, SDL_Color{ 255, 255, 0, 255 });
	to->SetLocalPosition(glm::vec3{ 292, 20 ,0});
	scene.Add(std::move(to));

	//w1
	go = std::make_unique<dae::GameObject>();
	go->AddComponent<dae::TextComponent>("FPS", font, SDL_Color{ 255, 255, 0, 255 });
	go->AddComponent<dae::FPSComponent>();
	go->SetLocalPosition(glm::vec3{ 10,10,0 });
	scene.Add(std::move(go));

	//w2
	auto pivot = std::make_unique<dae::GameObject>();
	pivot->SetLocalPosition(glm::vec3{ 700,350,0 });
	auto* pivotPtr = pivot.get();
	scene.Add(std::move(pivot));

	auto msPacman = std::make_unique<dae::GameObject>();
	msPacman->SetParent(pivotPtr, false);
	msPacman->AddComponent<dae::TextureComponent>("MsPacman.png");
	msPacman->AddComponent<dae::RotatorComponent>(-10.f, 15.f);
	auto* msPacmanPtr = msPacman.get();
	scene.Add(std::move(msPacman));

	auto child = std::make_unique<dae::GameObject>();
	child->AddComponent<dae::TextureComponent>("MsPacman.png");
	child->AddComponent<dae::RotatorComponent>(5.f, 50.f);
	child->SetParent(msPacmanPtr, false);
	scene.Add(std::move(child));
}

int main(int, char* []) {
#if __EMSCRIPTEN__
	fs::path data_location = "";
#else
	fs::path data_location = "./Data/";
	if (!fs::exists(data_location))
		data_location = "../Data/";
#endif
	dae::Minigin engine(data_location);
	engine.Run(load);
	return 0;
}

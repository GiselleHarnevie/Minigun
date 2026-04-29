#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#if _DEBUG && __has_include(<vld.h>)
#include <vld.h>
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "Components/FPSComponent.h"
#include "TextureComponent.h"
#include "Components/RotatorComponent.h"
#include "Components/ThrashTheCacheComponent.h"
#include "Components/InputComponent.h"
#include "Input/InputManager.h"
#include "Input/Command.h"
#include "Components/PlayerComponent.h"
#include "Components/LivesComponent.h"
#include "Components/LivesUIComponent.h"
#include "Components/ScoreComponent.h"
#include "Components/ScoreUIComponent.h"
#include "../Engine/Sound/ServiceLocator.h"
#include "../Engine/Sound/SDLSoundSystem.h"

#include <windows.h>
#include <Xinput.h>
#include <string>

#include <filesystem>
namespace fs = std::filesystem;

static void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto smallFont = dae::ResourceManager::GetInstance().LoadFont("Newyear Coffee.otf", 15);

	dae::ServiceLocator::RegisterSoundSystem(std::make_unique<dae::SDLSoundSystem>());
	auto& ss = dae::ServiceLocator::GetSoundSystem();
	ss.Play(1, 100);

	auto go = std::make_unique<dae::GameObject>();
	go->AddComponent<dae::TextureComponent>("background.png");
	scene.Add(std::move(go));

	go = std::make_unique<dae::GameObject>();
	go->AddComponent<dae::TextureComponent>("logo.png");
	go->SetLocalPosition(glm::vec3{ 358, 180 ,0 });
	scene.Add(std::move(go));

	auto to = std::make_unique<dae::GameObject>();
	to->AddComponent<dae::TextComponent>("Programming 4 Assignment", font, SDL_Color{ 255, 255, 0, 255 });
	to->SetLocalPosition(glm::vec3{ 292, 20 ,0 });
	scene.Add(std::move(to));

	//w1
	go = std::make_unique<dae::GameObject>();
	go->AddComponent<dae::TextComponent>("F", font, SDL_Color{ 255, 255, 0, 255 });
	go->AddComponent<dae::FPSComponent>();
	go->SetLocalPosition(glm::vec3{ 10,10,0 });
	scene.Add(std::move(go));

	//w2
	/*auto pivot = std::make_unique<dae::GameObject>();
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
	scene.Add(std::move(child));*/

	//w3
	/*auto imguiPlot = std::make_unique<dae::GameObject>();
	imguiPlot->AddComponent<dae::ThrashTheCacheComponent>();
	scene.Add(std::move(imguiPlot));*/

	//w4
	auto text = std::make_unique<dae::GameObject>();
	text->AddComponent<dae::TextComponent>("D-pad to move, X to Kill Self, A and B to pick pellets", smallFont, SDL_Color{ 255, 255, 255, 255 });
	text->SetLocalPosition(glm::vec3{ 10, 60 ,0 });
	scene.Add(std::move(text));

	auto text2 = std::make_unique<dae::GameObject>();
	text2->AddComponent<dae::TextComponent>("WASD to move, C to Kill Self, Z and X to pick pellets", smallFont, SDL_Color{ 255, 255, 255, 255 });
	text2->SetLocalPosition(glm::vec3{ 10, 85 ,0 });
	scene.Add(std::move(text2));

	//w5
	///Player One
	auto livesDisplay = std::make_unique<dae::GameObject>();
	livesDisplay->AddComponent<dae::TextComponent>("Lives", smallFont, SDL_Color{ 255,255,255,255 });
	auto& livesDisplayComp = livesDisplay->AddComponent<dae::LivesUIComponent>();
	livesDisplay->SetLocalPosition(glm::vec3{ 10,110,0 });
	scene.Add(std::move(livesDisplay));

	auto scoreDisplay = std::make_unique<dae::GameObject>();
	scoreDisplay->AddComponent<dae::TextComponent>("S", smallFont, SDL_Color{ 255,255,255,255 });
	auto& scoreDisplayComp = scoreDisplay->AddComponent<dae::ScoreUIComponent>();
	scoreDisplay->SetLocalPosition(glm::vec3{ 10,130,0 });
	scene.Add(std::move(scoreDisplay));

	auto player = std::make_unique<dae::GameObject>();
	player->AddComponent<dae::TextureComponent>("MsPacman.png");
	auto& livesComp = player->AddComponent<dae::LivesComponent>(5);
	auto& scoreComp = player->AddComponent<dae::ScoreComponent>();
	auto& inputP1 = player->AddComponent<dae::InputComponent>();
	inputP1.UsingKeyboard();
	player->SetLocalPosition(glm::vec3{ 400, 150 ,0 });
	scene.Add(std::move(player));

	//Observer
	livesDisplayComp.InitLivesTextDisplay(livesComp.GetLivesLeft());
	livesComp.m_Subject.AddObserver(&livesDisplayComp);
	scoreComp.m_Subject.AddObserver(&scoreDisplayComp);

	//
	auto livesDisplayTwo = std::make_unique<dae::GameObject>();
	livesDisplayTwo->AddComponent<dae::TextComponent>("Lives", smallFont, SDL_Color{ 255,255,255,255 });
	auto& livesDisplayCompTwo = livesDisplayTwo->AddComponent<dae::LivesUIComponent>();
	livesDisplayTwo->SetLocalPosition(glm::vec3{ 10,160,0 });
	scene.Add(std::move(livesDisplayTwo));

	auto scoreDisplayTwo = std::make_unique<dae::GameObject>();
	scoreDisplayTwo->AddComponent<dae::TextComponent>("S", smallFont, SDL_Color{ 255,255,255,255 });
	auto& scoreDisplayCompTwo = scoreDisplayTwo->AddComponent<dae::ScoreUIComponent>();
	scoreDisplayTwo->SetLocalPosition(glm::vec3{ 10,180,0 });
	scene.Add(std::move(scoreDisplayTwo));

	auto playerTwo = std::make_unique<dae::GameObject>();
	playerTwo->AddComponent<dae::TextureComponent>("MsPacman.png");
	auto& livesCompTwo = playerTwo->AddComponent<dae::LivesComponent>(5);
	auto& scoreCompTwo = playerTwo->AddComponent<dae::ScoreComponent>();
	auto& inputP2 = playerTwo->AddComponent<dae::InputComponent>();
	inputP2.UsingGamepad(0);
	playerTwo->SetLocalPosition(glm::vec3{ 600, 150 ,0 });
	scene.Add(std::move(playerTwo));

	livesDisplayCompTwo.InitLivesTextDisplay(livesCompTwo.GetLivesLeft());
	livesCompTwo.m_Subject.AddObserver(&livesDisplayCompTwo);
	scoreCompTwo.m_Subject.AddObserver(&scoreDisplayCompTwo);

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

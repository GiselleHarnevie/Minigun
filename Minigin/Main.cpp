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
#include "Components/TextComponent.h"
#include "Components/FPSComponent.h"
#include "Components/TextureComponent.h"
#include "Components/RotatorComponent.h"
#include "Components/ThrashTheCacheComponent.h"
//#include "Components/MoveComponent.h"
#include "Components/InputComponent.h"
#include "InputManager.h"
#include "Command.h"
#include "Components/PlayerComponent.h"
#include "Components/LivesComponent.h"
#include "Components/LivesUIComponent.h"
#include "Components/ScoreComponent.h"
#include "Components/ScoreUIComponent.h"

#include <filesystem>
namespace fs = std::filesystem;

static void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto smallFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 15);

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
	text->AddComponent<dae::TextComponent>("WASD to move, C to Kill Self, Z and X to pick pellets", smallFont, SDL_Color{ 255, 255, 255, 255 });
	text->SetLocalPosition(glm::vec3{ 10, 60 ,0 });
	scene.Add(std::move(text));

	//w5
	///Player One
	auto livesDisplay = std::make_unique<dae::GameObject>();
	livesDisplay->AddComponent<dae::TextComponent>("Lives", smallFont, SDL_Color{ 255,255,255,255 });
	auto& livesDisplayComp = livesDisplay->AddComponent<dae::LivesUIComponent>(); //O
	livesDisplay->SetLocalPosition(glm::vec3{ 10,110,0 });
	//auto* livesDisplayPtr = livesDisplay.get();
	scene.Add(std::move(livesDisplay));

	auto scoreDisplay = std::make_unique<dae::GameObject>();
	scoreDisplay->AddComponent<dae::TextComponent>("S", smallFont, SDL_Color{ 255,255,255,255 });
	auto& scoreDisplayComp = scoreDisplay->AddComponent<dae::ScoreUIComponent>(); //O
	scoreDisplay->SetLocalPosition(glm::vec3{ 10,130,0 });
	scene.Add(std::move(scoreDisplay));

	auto player = std::make_unique<dae::GameObject>();
	player->AddComponent<dae::TextureComponent>("MsPacman.png");
	auto& livesComp = player->AddComponent<dae::LivesComponent>(3); //S
	auto& scoreComp = player->AddComponent<dae::ScoreComponent>(); //S
	player->AddComponent<dae::InputComponent>();
	player->SetLocalPosition(glm::vec3{ 300, 100 ,0 });
	//auto* playerPtr = player.get();
	scene.Add(std::move(player));

	//Observer
	//auto* observer = livesDisplayPtr->GetComponent<dae::LivesUIComponent>();
	//auto* subject = playerPtr->GetComponent<dae::LivesComponent>();
	//observer->InitLivesTextDisplay(subject->GetLivesLeft());
	//subject->m_Subject.AddObserver(observer);
	livesDisplayComp.InitLivesTextDisplay(livesComp.GetLivesLeft());
	livesComp.m_Subject.AddObserver(&livesDisplayComp);

	scoreComp.m_Subject.AddObserver(&scoreDisplayComp);

	///Player Two
	//mannn..


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

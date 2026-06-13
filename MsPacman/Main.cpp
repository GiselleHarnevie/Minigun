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
#include "LevelManager.h"
#include "Components/MazeRendererComponent.h"
#include "GameSettings.h"
#include "Components/GhostComponent.h"
#include "Commands/SkipLevelCommand.h"
#include "Commands/MuteCommand.h"
#include "HighScoreManager.h"

#ifdef _WIN32
#include <windows.h>
#include <Xinput.h>
#endif // _WIN32


#include <string>

#include <filesystem>
#include <iostream>
namespace fs = std::filesystem;

static void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene();
	auto title = dae::ResourceManager::GetInstance().LoadFont("PressStart2p.ttf", 40);
	auto text = dae::ResourceManager::GetInstance().LoadFont("PressStart2p.ttf", 12);
	auto highlight = dae::ResourceManager::GetInstance().LoadFont("PressStart2p.ttf", 8);
	dae::LevelManager::GetInstance().ReadLevelJson("Data/LevelData.json");
	dae::HighScoreManager::GetInstance().Load();

	auto* muteCmd = dae::InputManager::GetInstance().AddCommand<dae::MuteCommand>(nullptr);
	dae::InputManager::GetInstance().BindCommand(SDL_SCANCODE_F2, dae::InputState::Pressed, muteCmd);

	auto* skipCmd = dae::InputManager::GetInstance().AddCommand<dae::SkipLevelCommand>(nullptr);
	dae::InputManager::GetInstance().BindCommand(SDL_SCANCODE_F1, dae::InputState::Pressed, skipCmd);

	dae::ServiceLocator::RegisterSoundSystem(std::make_unique<dae::SDLSoundSystem>());
	auto& ss = dae::ServiceLocator::GetSoundSystem();
	ss.Play(1, 100);

	//FPS
	auto go = std::make_unique<dae::GameObject>();
	go->AddComponent<dae::TextComponent>("F", highlight, SDL_Color{ 255, 255, 0, 255 });
	go->AddComponent<dae::FPSComponent>();
	go->SetLocalPosition(glm::vec3{ dae::WINDOW_WIDTH/2 - dae::TILE_SIZE,dae::WINDOW_HEIGHT - dae::TILE_SIZE,0 });
	scene.Add(std::move(go));

	//GAMEPLAY SECTION
	auto level = std::make_unique<dae::GameObject>();
	level->AddComponent<dae::TextureComponent>("Level1.png");
	level->AddComponent<dae::MazeRendererComponent>(dae::LevelManager::GetInstance().GetLevel(0));
	level->SetLocalPosition(glm::vec3{ 0,dae::TOP_HUD_HEIGHT * dae::TILE_SIZE,0 });
	scene.Add(std::move(level));

	//lives
	auto livesDisplay = std::make_unique<dae::GameObject>();
	livesDisplay->AddComponent<dae::TextComponent>("Lives", text, SDL_Color{ 255,255,255,255 });
	auto& livesDisplayComp = livesDisplay->AddComponent<dae::LivesUIComponent>();
	livesDisplay->SetLocalPosition(dae::GeneralTileToWorldPosition(dae::livesDisplayPos));
	scene.Add(std::move(livesDisplay));

	//Highscore title text (mid)
	auto scoreText = std::make_unique<dae::GameObject>();
	scoreText->AddComponent<dae::TextComponent>("HIGH SCORE", text, SDL_Color{ 255,255,255,255 });
	scoreText->SetLocalPosition(dae::GeneralTileToWorldPosition(dae::HighscoreText));
	scene.Add(std::move(scoreText));

	//1Up text (left)
	auto OneUpText = std::make_unique<dae::GameObject>();
	OneUpText->AddComponent<dae::TextComponent>("1UP", text, SDL_Color{ 255,255,255,255 });
	OneUpText->SetLocalPosition(dae::GeneralTileToWorldPosition(dae::OneUpText));
	scene.Add(std::move(OneUpText));

	//1Up text (right)
	auto TwoUpText = std::make_unique<dae::GameObject>();
	TwoUpText->AddComponent<dae::TextComponent>("2UP", text, SDL_Color{ 255,255,255,255 });
	TwoUpText->SetLocalPosition(dae::GeneralTileToWorldPosition(dae::TwoUpText));
	scene.Add(std::move(TwoUpText));

	//curr score number (left)
	auto scoreDisplay = std::make_unique<dae::GameObject>();
	scoreDisplay->AddComponent<dae::TextComponent>("S", text, SDL_Color{ 255,255,255,255 });
	auto& scoreDisplayComp = scoreDisplay->AddComponent<dae::ScoreUIComponent>();
	scoreDisplay->SetLocalPosition(dae::GeneralTileToWorldPosition(dae::CurrentHighscoreNrPOne));
	scene.Add(std::move(scoreDisplay));

	auto* currentLevel = dae::LevelManager::GetInstance().GetLevel(0);
	///Player One
	auto player = std::make_unique<dae::GameObject>();
	player->AddComponent<dae::TextureComponent>("MsPacman.png");
	auto& livesComp = player->AddComponent<dae::LivesComponent>(4);
	auto& scoreComp = player->AddComponent<dae::ScoreComponent>();
	player->AddComponent<dae::PlayerComponent>(currentLevel);
	auto* playerComp = player->GetComponent<dae::PlayerComponent>();
	auto& inputP1 = player->AddComponent<dae::InputComponent>();
	inputP1.UsingKeyboard();
	scene.Add(std::move(player));

	//Observer
	livesDisplayComp.InitLivesTextDisplay(livesComp.GetLivesLeft());
	livesComp.m_Subject.AddObserver(&livesDisplayComp);
	scoreComp.m_Subject.AddObserver(&scoreDisplayComp);

	auto blinky = std::make_unique<dae::GameObject>();
	blinky->AddComponent<dae::TextureComponent>("JustBlinkyTest.png");
	blinky->AddComponent<dae::GhostComponent>(currentLevel, playerComp, dae::GhostType::Blinky, dae::BLINKY_START_WORLD);
	scene.Add(std::move(blinky));

	auto pinky = std::make_unique<dae::GameObject>();
	pinky->AddComponent<dae::TextureComponent>("JustBlinkyTest.png");
	pinky->AddComponent<dae::GhostComponent>(currentLevel, playerComp, dae::GhostType::Pinky, dae::PINKY_START_WORLD);
	scene.Add(std::move(pinky));

	auto inky = std::make_unique<dae::GameObject>();
	inky->AddComponent<dae::TextureComponent>("JustBlinkyTest.png");
	inky->AddComponent<dae::GhostComponent>(currentLevel, playerComp, dae::GhostType::Inky, dae::INKY_START_WORLD);
	scene.Add(std::move(inky));

	auto sue = std::make_unique<dae::GameObject>();
	sue->AddComponent<dae::TextureComponent>("JustBlinkyTest.png");
	sue->AddComponent<dae::GhostComponent>(currentLevel, playerComp, dae::GhostType::Sue, dae::SUE_START_WORLD);
	scene.Add(std::move(sue));
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

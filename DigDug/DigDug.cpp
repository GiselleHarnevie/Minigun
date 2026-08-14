#include "GameSettings.h"
#include "DigDug.h"
#include <iostream>

void DigDugSetup()
{
	dae::ServiceLocator::RegisterSoundSystem(std::make_unique<dae::SDLSoundSystem>());
	//auto& ss = dae::ServiceLocator::GetSoundSystem();


	dae::LevelManager::GetInstance().ReadLevelJson("Data/LevelData.json");
	dae::HighScoreManager::GetInstance().Load();

	auto* muteCmd = dae::InputManager::GetInstance().AddCommand<dae::MuteCommand>(nullptr);
	dae::InputManager::GetInstance().BindCommand(SDL_SCANCODE_F2, dae::InputState::Pressed, muteCmd);

	//-Scene-
	dae::SceneManager::GetInstance().CreateScene("Menu");
	dae::SceneManager::GetInstance().CreateScene("Gameplay");
	dae::SceneManager::GetInstance().CreateScene("HighScore");

	auto* menuScene = dae::SceneManager::GetInstance().GetScene("Menu");
	auto* gameplayScene = dae::SceneManager::GetInstance().GetScene("Gameplay");

	menuScene->SetPostUpdateCallback([]()
		{
			if (dae::GameState::GetInstance().ConsumeGameStartRequest())
			{
				GameplayScene(dae::GameState::GetInstance().GetGameMode());
				dae::SceneManager::GetInstance().SetActiveScene("Gameplay");
			}
		});

	gameplayScene->SetPostUpdateCallback([]()
		{
			if (dae::GameState::GetInstance().ConsumeGameOverRequest())
			{
				HighScoreScene();
				dae::SceneManager::GetInstance().SetActiveScene("HighScore");
				return;
			}
			if (dae::GameState::GetInstance().ConsumeSceneReloadRequest())
			{

				auto* scene = dae::SceneManager::GetInstance().GetScene("Gameplay");
				int currentLevel = dae::LevelManager::GetInstance().GetCurrentLevelIndex();
				LoadGameplayLevel(dae::GameState::GetInstance().GetGameMode(), currentLevel, *scene);
			}
		});
}

void MainMenuScene()
{
	//-Scene-
	auto& sceneMenu = *dae::SceneManager::GetInstance().GetScene("Menu");
	sceneMenu.RemoveAll();

	//-Fonts-
	SDL_Color white = { 255,255,255,255 };
	auto menuText = dae::ResourceManager::GetInstance().LoadFont("PressStart2p.ttf", 18);

	//-Menu Scene Objects-
	auto menuBackgroundGO = std::make_unique<dae::GameObject>();
	menuBackgroundGO->AddComponent<dae::TextureComponent>("Sprites/MenuBackground.png", dae::SIZE_MULTIPLIER);
	sceneMenu.Add(std::move(menuBackgroundGO));

	auto gameModeTextGO = std::make_unique<dae::GameObject>();
	gameModeTextGO->AddComponent<dae::TextComponent>("1 PLAYER", menuText, white);
	gameModeTextGO->SetLocalPosition(dae::ONE_PLAYER_TEXT_POS);
	sceneMenu.Add(std::move(gameModeTextGO));

	gameModeTextGO = std::make_unique<dae::GameObject>();
	gameModeTextGO->AddComponent<dae::TextComponent>("2 PLAYERS", menuText, white);
	gameModeTextGO->SetLocalPosition(dae::TWO_PLAYER_TEXT_POS);
	sceneMenu.Add(std::move(gameModeTextGO));

	//gameModeTextGO = std::make_unique<dae::GameObject>();
	//gameModeTextGO->AddComponent<dae::TextComponent>("VERSUS", menuText, white);
	//gameModeTextGO->SetLocalPosition(dae::VERSUS_TEXT_POS);
	//sceneMenu.Add(std::move(gameModeTextGO));

	auto menuSelectorGO = std::make_unique<dae::GameObject>();
	menuSelectorGO->AddComponent<dae::TextureComponent>("Sprites/MenuArrow.png", dae::SIZE_MULTIPLIER);
	menuSelectorGO->AddComponent<dae::SelectionComponent>();
	sceneMenu.Add(std::move(menuSelectorGO));
}

void GameplayScene(dae::GameMode gameMode)
{
	//-Scene-
	auto& gameScene = *dae::SceneManager::GetInstance().GetScene("Gameplay");

	dae::GameState::GetInstance().ResetForNewGame();
	dae::GameState::GetInstance().SetGameMode(gameMode);
	dae::LevelManager::GetInstance().SetLevelIndex(0);

	LoadGameplayLevel(gameMode, dae::LevelManager::GetInstance().GetCurrentLevelIndex(), gameScene);
}

void LoadGameplayLevel(dae::GameMode gameMode, int levelIndex, dae::Scene& gameScene)
{
	// top of LoadGameplayLevel
	dae::InputManager::GetInstance().UnbindAllCommands();
	gameScene.RemoveAll();
	auto& ss = dae::ServiceLocator::GetSoundSystem();

	ss.LoadAudio(1, "DigDugDisappearing.mp3");
	ss.LoadAudio(2, "DigDugWalking.mp3");
	ss.LoadAudio(4, "MonstertouchedDigDug.mp3");
	ss.LoadAudio(5, "Pumping.mp3");
	ss.LoadAudio(6, "RoundClearMusic.mp3");
	ss.LoadAudio(0, "ButtonClick.wav");

	if (levelIndex != 0)
		ss.PlayAudio(6, 1.0f);


	dae::GameState::GetInstance().SetGameMode(gameMode);

	//-Fonts-
	SDL_Color white = { 255,255,255,255 };
	SDL_Color red = { 255,0,0,255 };
	auto hudFont = dae::ResourceManager::GetInstance().LoadFont("PressStart2p.ttf", 15);

	//-Sounds-


	//-Playfield Render-
	auto levelBg = std::make_unique<dae::GameObject>();
	levelBg->AddComponent<dae::TextureComponent>("Sprites/LevelBg.png", dae::SIZE_MULTIPLIER);
	levelBg->SetLocalPosition(glm::vec3{ 0.f,0.f,0.f });
	gameScene.Add(std::move(levelBg));

	auto playfield = std::make_unique<dae::GameObject>();
	//playfield->SetLocalPosition(dae::PLAYFIELD_SPAWN);
	playfield->AddComponent<dae::MazeRendererComponent>(dae::LevelManager::GetInstance().GetLevel(levelIndex));
	//auto* playfieldptr = playfield.get();
	gameScene.Add(std::move(playfield));

	auto* currentLevel = dae::LevelManager::GetInstance().GetLevel(levelIndex);

	//-Gameplay HUDs-
	//-Score UI-
	auto hiScoreTextDisplay = std::make_unique<dae::GameObject>();
	hiScoreTextDisplay->AddComponent<dae::TextComponent>("HI-", hudFont, red);
	hiScoreTextDisplay->SetLocalPosition(dae::HI_TEXT_SPAWN);
	gameScene.Add(std::move(hiScoreTextDisplay));

	hiScoreTextDisplay = std::make_unique<dae::GameObject>();
	hiScoreTextDisplay->AddComponent<dae::TextComponent>("SCORE", hudFont, red);
	hiScoreTextDisplay->SetLocalPosition(dae::SCORE_TEXT_SPAWN);
	gameScene.Add(std::move(hiScoreTextDisplay));

	//
	auto oneUpTextDisplay = std::make_unique<dae::GameObject>();
	oneUpTextDisplay->AddComponent<dae::TextComponent>("1UP", hudFont, red);
	oneUpTextDisplay->SetLocalPosition(dae::ONE_UP_TEXT_SPAWN);
	gameScene.Add(std::move(oneUpTextDisplay));

	if (gameMode != dae::GameMode::SinglePlayer)
	{
		auto twoUpTextDisplay = std::make_unique<dae::GameObject>();
		twoUpTextDisplay->AddComponent<dae::TextComponent>("2UP", hudFont, red);
		twoUpTextDisplay->SetLocalPosition(dae::TWO_UP_TEXT_SPAWN);
		gameScene.Add(std::move(twoUpTextDisplay));
	}

	auto scoreDisplay = std::make_unique<dae::GameObject>();
	scoreDisplay->AddComponent<dae::TextComponent>("S", hudFont, white);
	auto& scoreDisplayComp = scoreDisplay->AddComponent<dae::ScoreUIComponent>();
	scoreDisplay->SetLocalPosition(dae::ONE_UP_SCORE_SPAWN);
	gameScene.Add(std::move(scoreDisplay));

	//-Round UI-
	auto roundTextDisplay = std::make_unique<dae::GameObject>();
	roundTextDisplay->AddComponent<dae::TextComponent>("ROUND", hudFont, white);
	roundTextDisplay->SetLocalPosition(dae::ROUND_TEXT_SPAWN);
	gameScene.Add(std::move(roundTextDisplay));

	auto roundNumberDisplay = std::make_unique<dae::GameObject>();
	roundNumberDisplay->AddComponent<dae::TextComponent>("", hudFont, white);
	roundNumberDisplay->AddComponent<dae::RoundUIComponent>(dae::LevelManager::GetInstance().GetCurrentLevelIndex() + 1);
	roundNumberDisplay->SetLocalPosition(dae::ROUND_NUMBER_SPAWN);
	gameScene.Add(std::move(roundNumberDisplay));

	//-Lives UI-
	auto livesDisplay = std::make_unique<dae::GameObject>();
	livesDisplay->AddComponent<dae::TextComponent>("Lives", hudFont, white);
	auto& livesDisplayComp = livesDisplay->AddComponent<dae::LivesUIComponent>();
	livesDisplay->SetLocalPosition(dae::LIVES_DISPLAY_SPAWN);
	gameScene.Add(std::move(livesDisplay));


	//--Players--
	//-Player One-
	auto player = std::make_unique<dae::GameObject>();
	player->AddComponent<dae::SpriteAnimationComponent>("Sprites/PlayerWalking.png", 2, 5.f);

	auto& livesCompPlayerOne = player->AddComponent<dae::LivesComponent>(dae::GameState::GetInstance().GetLives());
	auto& scoreCompPlayerOne = player->AddComponent<dae::ScoreComponent>(dae::GameState::GetInstance().GetScore()); //shared

	auto& inputP1 = player->AddComponent<dae::InputComponent>();
	player->AddComponent<dae::PlayerComponent>(currentLevel, dae::TAIZO_TILE_SPAWN);
	inputP1.UsingKeyboard();

	if (gameMode == dae::GameMode::Multiplayer)
		inputP1.UsingGamepad(1);
	else
		inputP1.UsingGamepad(0);

	//auto playerPtr = player.get();
	auto playerCompptr = player->GetComponent<dae::PlayerComponent>();
	gameScene.Add(std::move(player));


	//-Player 2-
	dae::LivesComponent* livesCompPlayerTwo = nullptr;
	dae::PlayerComponent* playerCompPlayerTwo = nullptr;

	if (gameMode == dae::GameMode::Multiplayer)
	{
		auto playerTwo = std::make_unique<dae::GameObject>();
		//auto playerTwoPtr = playerTwo.get();
		playerCompptr->RestartPlayer(dae::TAIZO_SPAWN_COOP);

		playerTwo->AddComponent<dae::SpriteAnimationComponent>("Sprites/PlayerWalking.png", 2, 5.f);
		auto& livesComp = playerTwo->AddComponent<dae::LivesComponent>(dae::GameState::GetInstance().GetLives());
		livesCompPlayerTwo = &livesComp;

		playerTwo->AddComponent<dae::ScoreComponent>(dae::GameState::GetInstance().GetScore());
		auto& inputP2 = playerTwo->AddComponent<dae::InputComponent>();

		playerCompPlayerTwo = &playerTwo->AddComponent<dae::PlayerComponent>(currentLevel, dae::TAIZO_SPAWN_COOP_TWO);

		inputP2.UsingGamepad(0);
		gameScene.Add(std::move(playerTwo));

	}

	//-Pooka-
	auto pookaSpawns = dae::GetPookaSpawnsForLevel(levelIndex);
	int enemyCount = 0;
	for (const auto& pookaSpawnPos : pookaSpawns)
	{
		auto pooka = std::make_unique<dae::GameObject>();
		pooka->AddComponent<dae::SpriteAnimationComponent>("Sprites/PookaWalking.png", 2, 3.f);

		dae::PookaComponent* pookaCompPtr = nullptr;
		if (gameMode == dae::GameMode::Multiplayer)
		{
			pookaCompPtr = &pooka->AddComponent<dae::PookaComponent>(
				currentLevel,
				playerCompptr,
				playerCompPlayerTwo,
				pookaSpawnPos
			);
		}
		else
		{
			pookaCompPtr = &pooka->AddComponent<dae::PookaComponent>(
				currentLevel,
				playerCompptr,
				pookaSpawnPos
			);
		}

		//events

		if (pookaCompPtr)pookaCompPtr->m_Subject.AddObserver(&dae::LevelManager::GetInstance());
		if (pookaCompPtr)pookaCompPtr->m_Subject.AddObserver(playerCompptr);

		if (playerCompPlayerTwo && pookaCompPtr)
			pookaCompPtr->m_Subject.AddObserver(playerCompPlayerTwo);

		if (pookaCompPtr)pookaCompPtr->m_Subject.AddObserver(&scoreCompPlayerOne);

		gameScene.Add(std::move(pooka));
		enemyCount++;
	}
	dae::LevelManager::GetInstance().SetEnemyCount(enemyCount);


	//--Handle Events--

	//Lives Observers
	livesCompPlayerOne.m_Subject.AddObserver(&livesDisplayComp);
	livesCompPlayerOne.m_Subject.AddObserver(&dae::GameState::GetInstance());

	//Score Observers
	scoreCompPlayerOne.m_Subject.AddObserver(&scoreDisplayComp);
	scoreCompPlayerOne.m_Subject.AddObserver(&dae::GameState::GetInstance());

	if (livesCompPlayerTwo)
	{
		livesCompPlayerTwo->m_Subject.AddObserver(&livesDisplayComp);
		livesCompPlayerTwo->m_Subject.AddObserver(&dae::GameState::GetInstance());
	}


	livesDisplayComp.InitLivesTextDisplay(livesCompPlayerOne.GetLivesLeft());
	scoreDisplayComp.InitScoreTextDisplay(scoreCompPlayerOne.GetScore());

}

void HighScoreScene()
{
	auto& highScoreScene = *dae::SceneManager::GetInstance().GetScene("HighScore");
	highScoreScene.RemoveAll();

	auto& ss = dae::ServiceLocator::GetSoundSystem();


	ss.LoadAudio(3, "GameOverMusic.mp3");
	ss.PlayAudio(3, 1.0f);

	//-Fonts-
	SDL_Color white = { 255,255,255,255 };
	SDL_Color yellow = { 255,255,0 ,255 };
	auto titles = dae::ResourceManager::GetInstance().LoadFont("PressStart2p.ttf", 18);
	auto normalFont = dae::ResourceManager::GetInstance().LoadFont("PressStart2p.ttf", 17);

	auto scoreText = std::make_unique<dae::GameObject>();
	scoreText->AddComponent<dae::TextComponent>("SCORE", titles, yellow);
	scoreText->SetLocalPosition(dae::HS_SCORE_TEXT);
	highScoreScene.Add(std::move(scoreText));

	auto nameText = std::make_unique<dae::GameObject>();
	nameText->AddComponent<dae::TextComponent>("NAME", titles, yellow);
	nameText->SetLocalPosition(dae::HS_NAME_TEXT);
	highScoreScene.Add(std::move(nameText));

	dae::HighScoreManager::GetInstance().AddEntry("ABC", dae::GameState::GetInstance().GetScore());
	dae::HighScoreManager::GetInstance().Save();

	auto yourEntryName = "ABC";
	auto yourEntryScore = dae::GameState::GetInstance().GetScore();

	auto yourEntryGO = std::make_unique<dae::GameObject>();
	std::string yourEntryText = std::to_string(yourEntryScore) + "      " + yourEntryName;
	yourEntryGO->AddComponent<dae::TextComponent>(yourEntryText, normalFont, white);
	yourEntryGO->SetLocalPosition(dae::HS_YOUR_ENTRY_TEXT);
	highScoreScene.Add(std::move(yourEntryGO));


	float yOffset = 0.f;
	for (const auto& entry : dae::HighScoreManager::GetInstance().GetEntries())
	{
		auto entryGO = std::make_unique<dae::GameObject>();
		std::string entryText = std::to_string(entry.score) + "     " + entry.name;
		entryGO->AddComponent<dae::TextComponent>(entryText, normalFont, white);
		entryGO->SetLocalPosition(glm::vec2{ dae::HS_ENTRY_TEXT.x,dae::HS_ENTRY_TEXT.y + yOffset });
		highScoreScene.Add(std::move(entryGO));
		yOffset += dae::TILE_SIZE;
	}

	auto* backToMenuCmd = dae::InputManager::GetInstance().AddCommand<dae::BackToMenuCommand>(nullptr);
	dae::InputManager::GetInstance().BindCommand(SDL_SCANCODE_BACKSPACE, dae::InputState::Pressed, backToMenuCmd);

}
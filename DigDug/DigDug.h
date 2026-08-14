#pragma once

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
#include "Components/RoundUIComponent.h"
#include "Components/ScoreComponent.h"
#include "Components/ScoreUIComponent.h"
#include "../Engine/Sound/ServiceLocator.h"
#include "../Engine/Sound/SDLSoundSystem.h"
#include "LevelManager.h"
#include "Components/MazeRendererComponent.h"
#include "GameSettings.h"
#include "Components/PookaComponent.h"
#include "Commands/SkipLevelCommand.h"
#include "Commands/MuteCommand.h"
#include "Commands/BackToMenuCommand.h"
#include "HighScoreManager.h"
#include "../Engine/SpriteAnimationComponent.h"
#include "Components/SelectionComponent.h"
#include "GameState.h"

void DigDugSetup();
void MainMenuScene();
void GameplayScene(dae::GameMode gameMode);
void LoadGameplayLevel(dae::GameMode gameMode, int levelIndex, dae::Scene& gameScene);
void HighScoreScene();
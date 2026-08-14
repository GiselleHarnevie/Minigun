#pragma once
#include <glm/glm.hpp>
#include <SDL3/SDL.h>

namespace dae
{
	enum GameMode
	{
		SinglePlayer,
		Multiplayer,
		Versus
	};

	constexpr float SIZE_MULTIPLIER = 2.f;

	constexpr int BORDER_TILES = 2;
	constexpr int PLAYFIELD_TILE_NR_HOR = 12 + BORDER_TILES;
	constexpr int PLAYFIELD_TILE_NR_VER = 13 + BORDER_TILES;

	constexpr int FULL_RES_WIDTH = 256 + 10;
	constexpr int FULL_RES_HEIGHT = 224 + 10;

	constexpr int TILE_SIZE = 16 * static_cast<int>(SIZE_MULTIPLIER);
	constexpr int WINDOW_WIDTH = FULL_RES_WIDTH * static_cast<int>(SIZE_MULTIPLIER);
	constexpr int WINDOW_HEIGHT = FULL_RES_HEIGHT * static_cast<int>(SIZE_MULTIPLIER);

	//--Menu scene--
	constexpr glm::vec2 ONE_PLAYER_TEXT_POS{ 96.f * SIZE_MULTIPLIER, 96.f * SIZE_MULTIPLIER };
	constexpr glm::vec2 TWO_PLAYER_TEXT_POS{ 96.f * SIZE_MULTIPLIER, 112.f * SIZE_MULTIPLIER };
	constexpr glm::vec2 VERSUS_TEXT_POS{ 96.f * SIZE_MULTIPLIER, 128.f * SIZE_MULTIPLIER };

	//-- Gameplay scene--
	//Dig Dug Taizo
	constexpr glm::vec2 TAIZO_TILE_SPAWN{ 104.f * SIZE_MULTIPLIER,120.f * SIZE_MULTIPLIER };

	constexpr glm::vec2 TAIZO_SPAWN_COOP{ 92.f * SIZE_MULTIPLIER,120.f * SIZE_MULTIPLIER };
	constexpr glm::vec2 TAIZO_SPAWN_COOP_TWO{ 120.f * SIZE_MULTIPLIER,120.f * SIZE_MULTIPLIER };

	constexpr float PLAYER_SPEED{ 70.f };
	constexpr float PLAYER_TO_TILE_DISTANCE = 15.f;

	//Pooka & Fygar & Rock 
	constexpr float POOKA_SPEED{ 45.f };
	constexpr float POOKA_CHASE_SPEED{ 55.f };
	constexpr float POOKA_GHOST_SPEED{ POOKA_SPEED * 0.65f };
	constexpr float FYGAR_SPEED{ 30.f };
	constexpr float POOKA_CHASE_DISTANCE{ 4.f };

	//Pooka & Fygar & Rock Spawn & Fruit Points
	constexpr glm::vec2 LV_ONE_POOKA_ONE{ 40.f * SIZE_MULTIPLIER, 72.f * SIZE_MULTIPLIER };
	constexpr glm::vec2 LV_ONE_POOKA_TWO{ 152.f * SIZE_MULTIPLIER, 56.f * SIZE_MULTIPLIER };
	constexpr glm::vec2 LV_ONE_POOKA_THREE{ 72.f * SIZE_MULTIPLIER, 152.f * SIZE_MULTIPLIER };
	constexpr glm::vec2 LV_ONE_POOKA_FOUR{ 152.f * SIZE_MULTIPLIER, 152.f * SIZE_MULTIPLIER };

	constexpr glm::vec2 LV_TWO_POOKA_ONE{ 160.f * SIZE_MULTIPLIER, 72.f * SIZE_MULTIPLIER };
	constexpr glm::vec2 LV_TWO_POOKA_TWO{ 64.f * SIZE_MULTIPLIER, 104.f * SIZE_MULTIPLIER };
	constexpr glm::vec2 LV_TWO_POOKA_THREE{ 40.f * SIZE_MULTIPLIER, 144.f * SIZE_MULTIPLIER };
	constexpr glm::vec2 LV_TWO_POOKA_FOUR{ 112.f * SIZE_MULTIPLIER, 152.f * SIZE_MULTIPLIER };
	constexpr glm::vec2 LV_TWO_POOKA_FIVE{ 160.f * SIZE_MULTIPLIER, 184.f * SIZE_MULTIPLIER };

	constexpr glm::vec2 LV_THREE_POOKA_ONE{ 56.f * SIZE_MULTIPLIER, 88.f * SIZE_MULTIPLIER };
	constexpr glm::vec2 LV_THREE_POOKA_TWO{ 136.f * SIZE_MULTIPLIER, 88.f * SIZE_MULTIPLIER };
	constexpr glm::vec2 LV_THREE_POOKA_THREE{ 168.f * SIZE_MULTIPLIER, 56.f * SIZE_MULTIPLIER };
	constexpr glm::vec2 LV_THREE_POOKA_FOUR{ 88.f * SIZE_MULTIPLIER, 176.f * SIZE_MULTIPLIER };
	constexpr glm::vec2 LV_THREE_POOKA_FIVE{ 152.f * SIZE_MULTIPLIER, 184.f * SIZE_MULTIPLIER };

	//constexpr glm::vec2 FYGAR_ONE_SPAWN{ 48.f,152.f };

	//constexpr glm::vec2 ROCK_ONE_SPAWN{ 64.f,72.f };
	//constexpr glm::vec2 ROCK_TWO_SPAWN{ 160.f,152.f };
	//constexpr glm::vec2 ROCK_THREE_SPAWN{ 48.f,184.f };

	//constexpr glm::vec2 FRUIT_SPAWN{ 96.f,120.f };

	inline std::vector<glm::vec2> GetPookaSpawnsForLevel(int levelIndex)
	{
		switch (levelIndex)
		{
		case 0:
			return
			{
				{LV_ONE_POOKA_ONE}, {LV_ONE_POOKA_TWO}, {LV_ONE_POOKA_THREE}, {LV_ONE_POOKA_FOUR}
			};
		case 1:
			return
			{
				{LV_TWO_POOKA_ONE}, {LV_TWO_POOKA_TWO}, {LV_TWO_POOKA_THREE}, {LV_TWO_POOKA_FOUR}, {LV_TWO_POOKA_FIVE}
			};
		case 2:
			return
			{
				{LV_THREE_POOKA_ONE}, {LV_THREE_POOKA_TWO}, {LV_THREE_POOKA_THREE}, {LV_THREE_POOKA_FOUR}, {LV_THREE_POOKA_FIVE}
			};
		default:
			return {};
		}
	}


	//Playfield
	constexpr glm::vec2 PLAYFIELD_SPAWN{ -dae::TILE_SIZE / 2,0.f };
	constexpr glm::vec2 PLAYFIELD_HEIGHT_SURFACE{ 16.f * SIZE_MULTIPLIER,32.f * SIZE_MULTIPLIER };
	constexpr glm::vec2 PLAYFIELD_HEIGHT_ONE{ 32.f * SIZE_MULTIPLIER,80.f * SIZE_MULTIPLIER };
	constexpr glm::vec2 PLAYFIELD_HEIGHT_TWO{ 80.f * SIZE_MULTIPLIER,128.f * SIZE_MULTIPLIER };
	constexpr glm::vec2 PLAYFIELD_HEIGHT_THREE{ 128.f * SIZE_MULTIPLIER,176.f * SIZE_MULTIPLIER };
	constexpr glm::vec2 PLAYFIELD_HEIGHT_FOUR{ 176.f * SIZE_MULTIPLIER,224.f * SIZE_MULTIPLIER };


	//White Flower (how many rounds completed)			   
	constexpr glm::vec2 WHITE_FLOWER_SPAWN{ 192.f * SIZE_MULTIPLIER,16.f * SIZE_MULTIPLIER };

	//Hi-Score text										   
	constexpr glm::vec2 HI_TEXT_SPAWN{ 208.f * SIZE_MULTIPLIER,16.f * SIZE_MULTIPLIER };
	constexpr glm::vec2 SCORE_TEXT_SPAWN{ 216.f * SIZE_MULTIPLIER,24.f * SIZE_MULTIPLIER };

	//Hi-Score number text								   
	constexpr glm::vec2 HI_SCORE_NUMBER_SPAWN{ 216.f * SIZE_MULTIPLIER,32.f * SIZE_MULTIPLIER };

	//1UP text											   
	constexpr glm::vec2 ONE_UP_TEXT_SPAWN{ 208.f * SIZE_MULTIPLIER,56.f * SIZE_MULTIPLIER };

	//1UP score number text								   
	constexpr glm::vec2 ONE_UP_SCORE_SPAWN{ 224.f * SIZE_MULTIPLIER,64.f * SIZE_MULTIPLIER };

	//2UP text											   
	constexpr glm::vec2 TWO_UP_TEXT_SPAWN{ 208.f * SIZE_MULTIPLIER,80.f * SIZE_MULTIPLIER };

	//2UP score text									   
	constexpr glm::vec2 TWO_UP_SCORE_SPAWN{ 240.f * SIZE_MULTIPLIER,96.f * SIZE_MULTIPLIER };

	//Lives Display
	constexpr glm::vec2 LIVES_DISPLAY_SPAWN{ 209.f * SIZE_MULTIPLIER,144.f * SIZE_MULTIPLIER };

	//Player 1/2 Ready text								   
	constexpr glm::vec2 PLAYER_READY_TEXT_SPAWN{ 64.f * SIZE_MULTIPLIER,104.f * SIZE_MULTIPLIER };

	//Game Over text									   
	constexpr glm::vec2 GAME_OVER_TEXT_SPAWN{ 64.f * SIZE_MULTIPLIER ,104.f * SIZE_MULTIPLIER };

	//Round text										   
	constexpr glm::vec2 ROUND_TEXT_SPAWN{ 209.f * SIZE_MULTIPLIER,200.f * SIZE_MULTIPLIER };

	//Round number										   
	constexpr glm::vec2 ROUND_NUMBER_SPAWN{ 248.f * SIZE_MULTIPLIER,208.f * SIZE_MULTIPLIER };

	//HighScoreScene
	//Score
	constexpr glm::vec2 HS_SCORE_TEXT{ 64.f * SIZE_MULTIPLIER,48.f * SIZE_MULTIPLIER };
	//Round
	//constexpr glm::vec2 HS_ROUND_TEXT{ 112.f * SIZE_MULTIPLIER,48.f * SIZE_MULTIPLIER };
	//Name
	constexpr glm::vec2 HS_NAME_TEXT{ 136.f * SIZE_MULTIPLIER,48.f * SIZE_MULTIPLIER };
	//Entry Start Pos
	constexpr glm::vec2 HS_YOUR_ENTRY_TEXT{ 72.f * SIZE_MULTIPLIER,72.f * SIZE_MULTIPLIER };
	constexpr glm::vec2 HS_ENTRY_TEXT{ 72.f * SIZE_MULTIPLIER,122.f * SIZE_MULTIPLIER };

	inline bool IsInBounds(const glm::ivec2& tile, SDL_Rect bounds)
	{
		int min_x = bounds.x;
		int max_x = bounds.x + bounds.w;
		int min_y = bounds.y;
		int max_y = bounds.y + bounds.h;

		return tile.x >= min_x &&
			tile.x <= max_x &&
			tile.y >= min_y &&
			tile.y <= max_y;
	}


	inline bool AABB(const SDL_FRect& a, const SDL_FRect& b)
	{

		return a.x < b.x + b.w &&
			a.x + a.w > b.x &&
			a.y < b.y + b.h &&
			a.y + a.h > b.y;
	}

	inline glm::vec2 PlayfieldTileToWorldPosition(int x, int y) //playfield -> pos
	{
		float posX = static_cast<float>(x) * TILE_SIZE + TILE_SIZE / 2.f;
		float posY = static_cast<float>(y) * TILE_SIZE + TILE_SIZE / 2.f;
		return glm::vec2{ posX ,posY };
	}

	inline glm::ivec2 WorldPositionToPlayfieldTile(float worldX, float worldY) //pos -> playfield tile
	{
		int x = static_cast<int>((worldX - TILE_SIZE / 2.f) / TILE_SIZE);
		int y = static_cast<int>((worldY - TILE_SIZE / 2.f) / TILE_SIZE);
		return glm::ivec2{ x,y };
	}

	inline bool CheckIfArrivedAtTargetTile(const glm::vec2& currPos, const glm::vec2& targetPos)
	{
		glm::vec2 diff = targetPos - currPos;
		return (diff.x * diff.x + diff.y * diff.y) < (0.5f * 0.5f);
	}

	inline float CheckSquaredDist(const glm::vec2& currPos, const glm::vec2& targetPos)
	{
		glm::vec2 diff = targetPos - currPos;
		return (diff.x * diff.x + diff.y * diff.y);
	}

	inline glm::vec2 GetOppositeDirection(const glm::vec2& direction)
	{
		return glm::vec2(-direction.x, -direction.y);
	}
}
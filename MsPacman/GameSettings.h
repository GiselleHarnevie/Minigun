#pragma once
#include <glm/glm.hpp>
#include <SDL3/SDL.h>

namespace dae
{
	constexpr float SIZE_MULTIPLIER = 2.f;

	constexpr int TILE_SIZE = 8 * static_cast<int>(SIZE_MULTIPLIER);
	constexpr int MAZE_WIDTH = 28; // maze tile nr horizontal
	constexpr int MAZE_HEIGHT = 31; // maze tile number vertical //
	constexpr int GAME_SCREEN_WIDTH = 28;
	constexpr int GAME_SCREEN_HEIGHT = 36; //+5 UI ROWS
	constexpr int TOP_HUD_HEIGHT = 3; // 3 tiles / 60px
	constexpr int BOTTOM_HUD_HEIGHT = 2; // 2 tiles / 40px

	constexpr int WINDOW_WIDTH = GAME_SCREEN_WIDTH * TILE_SIZE;
	constexpr int WINDOW_HEIGHT = GAME_SCREEN_HEIGHT * TILE_SIZE;

	//ghost house
	constexpr SDL_Rect GHOST_HOUSE = { 10, 12, 7, 5 };

	//Spawn points
	constexpr glm::ivec2 MSPACMAN_START_POS{ 14,23 }; //13.5
	constexpr glm::ivec2 PACMAN_START_POS{ 13,23 };

	// ghost pixel positions
	inline const glm::vec2 BLINKY_START_WORLD{ 13.5f * TILE_SIZE, (11.f + TOP_HUD_HEIGHT) * TILE_SIZE };
	inline const glm::vec2 PINKY_START_WORLD{ 13.5f * TILE_SIZE, (14.f + TOP_HUD_HEIGHT) * TILE_SIZE };
	inline const glm::vec2 INKY_START_WORLD{ 12.5f * TILE_SIZE, (14.f + TOP_HUD_HEIGHT) * TILE_SIZE };
	inline const glm::vec2 SUE_START_WORLD{ 14.5f * TILE_SIZE, (14.f + TOP_HUD_HEIGHT) * TILE_SIZE };
	constexpr glm::ivec2 GHOST_HOUSE_DOOR{ 13,11 };

	//scatter targets

	//UI positions
	constexpr glm::ivec3 OneUpText{ 3,0,0 };
	constexpr glm::ivec3 TwoUpText{ 22,0,0 };
	constexpr glm::ivec3 HighscoreText{ 9,0,0 };

	constexpr glm::ivec3 HighscoreNrToBeatText{ 12,1,0 };
	constexpr glm::ivec3 CurrentHighscoreNrPOne{ 3,1,0 };
	constexpr glm::ivec3 CurrentHighscoreNrPTwo{ 22,1,0 };

	constexpr glm::ivec3 livesDisplayPos{ 2,34,0 };

	//Scoring
	constexpr int PELLET_SCORE{ 10 };
	constexpr int POWER_PELLET_SCORE{ 50 };

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


	inline glm::vec2 MazeTileToWorldPosition(int tilePosX, int tilePosY)
	{
		float posX = (tilePosX * TILE_SIZE) + static_cast<float>(TILE_SIZE / 2);
		float posY = (tilePosY * TILE_SIZE) + static_cast<float>(TILE_SIZE / 2) + (TOP_HUD_HEIGHT * TILE_SIZE);

		return glm::vec2{ posX,posY };
	}

	inline glm::ivec2 WorldToMazeTilePosition(float x, float y)
	{
		int tileX = static_cast<int>(x / TILE_SIZE);
		int tileY = static_cast<int>(y / TILE_SIZE) - TOP_HUD_HEIGHT;

		return glm::ivec2{ tileX,tileY };
	}

	inline glm::vec3 GeneralTileToWorldPosition(const glm::ivec3 tilePos)
	{
		float posX = (tilePos.x * TILE_SIZE) + static_cast<float>(TILE_SIZE / 2);
		float posY = (tilePos.y * TILE_SIZE) + static_cast<float>(TILE_SIZE / 2);

		return glm::vec3{ posX,posY,0 };
	}

	inline bool CheckIfArrivedAtTargetTile(const glm::vec2& currPos, const glm::vec2& targetPos)
	{
		glm::vec2 diff = targetPos - currPos;
		return (diff.x * diff.x + diff.y * diff.y) < (0.5f * 0.5f);
	}
}

//Scoring
//Pac-Dot		10
//Power-Pellet	50
//1st Ghost		200
//2nd Ghost		400
//3rd Ghost		800
//4th Ghost		1600
//Bonus item	300
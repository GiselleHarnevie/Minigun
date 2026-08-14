#include "Level.h"
#include <SDL3/SDL.h>
#include "GameSettings.h"
#include "Renderer.h"

dae::Level::Level(const std::vector<int>& tileData, int)
	:m_Tiles(tileData)
{

}



dae::TileType dae::Level::GetTileAtPos(int x, int y) const
{
	if (IsOutOfGrid(x, y))
		return TileType::Border;

	switch (m_Tiles[((y)*MazeWidth() + (x))])
	{
	case 0:
		return TileType::Surface;
	case 1:
		return TileType::LayerOne;
	case 2:
		return TileType::LayerTwo;
	case 3:
		return TileType::LayerThree;
	case 4:
		return TileType::LayerFour;
	case 5:
		return TileType::DugTileVer;
	case 6:
		return TileType::DugTileHor;
	case 7:
		return TileType::Border;
	case 8:
		return TileType::Rock;
	default:
		return TileType::Border;
	}

}

bool dae::Level::IsWall(int x, int y)
{
	if (IsOutOfGrid(x, y))
		return false;


	if (m_Tiles[y * MazeWidth() + x] == static_cast<int>(TileType::Border))
	{
		return true;
	}

	return false;
}

bool dae::Level::IsRock(int x, int y)
{
	if (IsOutOfGrid(x, y))
		return false;


	if (m_Tiles[y * MazeWidth() + x] == static_cast<int>(TileType::Rock))
	{
		return true;
	}

	return false;
}

bool dae::Level::IsSpecificTile(int x, int y, TileType tile)
{
	if (IsOutOfGrid(x, y))
		return false;

	return m_Tiles[y * MazeWidth() + x] == static_cast<int>(tile);
}

void dae::Level::SetTileAtPos(int x, int y, TileType newTile)
{
	if (IsOutOfGrid(x, y))
		return;

	m_Tiles[(y * MazeWidth() + x)] = static_cast<int>(newTile);
}

std::vector<int> dae::Level::GetAllTilesData()
{
	for (auto& tile : m_Tiles)
	{
		SDL_Log("%d", (int)tile);
	}
	return std::vector<int>();
}

bool dae::Level::IsOutOfGrid(int x, int y) const
{

	if (x < 0 || x >= MazeWidth() || y < 0 || y >= MazeHeight())
	{
		return true;
	}


	return false;
}

bool dae::Level::CanMove(const glm::ivec2& nextTile)
{
	return !IsWall(nextTile.x, nextTile.y) && !IsOutOfGrid(nextTile.x, nextTile.y) && !IsRock(nextTile.x, nextTile.y);
}

int dae::Level::MazeWidth() const
{

	return dae::PLAYFIELD_TILE_NR_HOR;
}

int dae::Level::MazeHeight() const
{
	return dae::PLAYFIELD_TILE_NR_VER;
}

bool dae::Level::IsAnyTypeOfLayer(const glm::ivec2& nextTile)
{
	auto layerOne = IsSpecificTile(nextTile.x, nextTile.y, dae::TileType::LayerOne);
	auto layerTwo = IsSpecificTile(nextTile.x, nextTile.y, dae::TileType::LayerTwo);
	auto layerThree = IsSpecificTile(nextTile.x, nextTile.y, dae::TileType::LayerThree);
	auto layerFour = IsSpecificTile(nextTile.x, nextTile.y, dae::TileType::LayerFour);
	return layerOne || layerTwo || layerThree || layerFour;
}


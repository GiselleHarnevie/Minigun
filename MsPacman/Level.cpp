#include "Level.h"
#include <SDL3/SDL.h>

dae::Level::Level(const std::vector<int>& tileData, int )
	:m_Tiles(tileData)
{
}



dae::TileType dae::Level::GetTileAtPos(int x, int y)
{
	if (IsOutOfGrid(x, y))
		return TileType::Empty;

	switch (m_Tiles[((y) * m_GRID_WIDTH + (x)) ])
	{
	case 0:
		return TileType::Empty;
	case 1:
		return TileType::Wall;
	case 2:
		return TileType::Pellet;
	case 3:
		return TileType::PowerPellet;
	default:
		return TileType::Empty;
	}

}

bool dae::Level::IsWall(int x, int y)
{
	if (IsOutOfGrid(x, y))
		return false;

	if (m_Tiles[y * m_GRID_WIDTH + x] == static_cast<int>(TileType::Wall))
	{
		return true;
	}

	return false;
}

bool dae::Level::IsSpecificTile(int x, int y, TileType tile)
{
	if (IsOutOfGrid(x, y))
		return false;

	return m_Tiles[y * m_GRID_WIDTH + x] == static_cast<int>(tile);
}

void dae::Level::SetTileAtPos(int x, int y, TileType newTile)
{
	if (IsOutOfGrid(x, y))
		return;

	m_Tiles[(y * m_GRID_WIDTH + x)] = static_cast<int>(newTile);
}

int dae::Level::CountPellets()
{
	int pelletNumber{};
	for (auto& tile : m_Tiles)
	{
		if (tile == static_cast<int>(TileType::Pellet))
		{
			pelletNumber++;
		}
	}
	return pelletNumber;
}

std::vector<int> dae::Level::GetAllTilesData()
{
	for (auto& tile : m_Tiles)
	{
		SDL_Log("%d", (int)tile);
	}
	return std::vector<int>();
}

bool dae::Level::IsOutOfGrid(int x, int y)
{
	if (x < 0 || x >= m_GRID_WIDTH || y < 0 || y >= m_GRID_HEIGHT)
	{
		return true;
	}
	return false;
}

int dae::Level::MazeWidth() const
{
	return m_GRID_WIDTH;
}

int dae::Level::MazeHeight() const
{
	return m_GRID_HEIGHT;
}



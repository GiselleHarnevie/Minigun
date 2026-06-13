#include <glm/glm.hpp>
#include <vector>
#include <memory>
#include <string>

namespace dae
{
	enum class TileType
	{
		Empty = 0,
		Wall = 1,
		Pellet = 2,
		PowerPellet = 3
	};

	class Level
	{
	public:
		Level(const std::vector<int>& tileData, int tileSize = 16);
		~Level() = default;

		TileType GetTileAtPos(int x, int y);
		void SetTileAtPos(int x, int y, TileType newTile);
		int CountPellets();

		std::vector<int> GetAllTilesData();

		//checks
		bool IsWall(int x, int y);
		bool IsSpecificTile(int x, int y, TileType tile);
		bool IsOutOfGrid(int x, int y);

		int MazeWidth()const;
		int MazeHeight()const;

	private:
		std::vector<int> m_Tiles;
		static constexpr int m_GRID_WIDTH = 28;
		static constexpr int m_GRID_HEIGHT = 31;

	};
}
#include <glm/glm.hpp>
#include <vector>
#include <memory>
#include <string>

namespace dae
{
	//Tiles 16x16
	enum class TileType
	{
		Surface = 0,
		LayerOne = 1, //200
		LayerTwo = 2, //300
		LayerThree = 3, //400
		LayerFour = 4, //500
		DugTileVer = 5,
		DugTileHor = 6,
		Border = 7,
		Rock=8
	};

	class Level
	{
	public:
		Level(const std::vector<int>& tileData, int tileSize = 16);
		~Level() = default;

		TileType GetTileAtPos(int x, int y) const;
		void SetTileAtPos(int x, int y, TileType newTile);
		//int CountPellets();

		std::vector<int> GetAllTilesData();

		//checks
		bool IsWall(int x, int y);
		bool IsRock(int x, int y);
		bool IsSpecificTile(int x, int y, TileType tile);
		bool IsOutOfGrid(int x, int y) const;

		bool CanMove(const glm::ivec2& nextTile);

		bool IsAnyTypeOfLayer(const glm::ivec2& nextTile);

		int MazeWidth()const;
		int MazeHeight()const;

	private:
		std::vector<int> m_Tiles;
		/*static constexpr int m_GRID_WIDTH = 28;
		static constexpr int m_GRID_HEIGHT = 31;*/

	};
}
#include "MazeRendererComponent.h"
#include "../Level.h"
#include "Renderer.h"
#include "GameObject.h"
#include "../GameSettings.h"


dae::MazeRendererComponent::MazeRendererComponent(GameObject* owner, Level* currentLevel)
	: Component(owner),
	m_CurrentLevel(currentLevel)

{
}

void dae::MazeRendererComponent::FixedUpdate(const float)
{
}

void dae::MazeRendererComponent::Update(float)
{
}

void dae::MazeRendererComponent::Render() const
{
	auto pos = GetOwner()->GetWorldPosition();
	SDL_Renderer* r = Renderer::GetInstance().GetSDLRenderer();

	for (int x = 0; x < m_CurrentLevel->MazeWidth(); x++)
	{
		for (int y = 0; y < m_CurrentLevel->MazeHeight(); y++)
		{
			TileType tile = m_CurrentLevel->GetTileAtPos(x, y);
			float px = pos.x + x * TILE_SIZE;
			float py = pos.y + y * TILE_SIZE;
			SDL_FRect powerPelletVertical{ px + TILE_SIZE / 2 - 4, py + TILE_SIZE / 2 - 3, 8,6 };
			SDL_FRect powerPelletHorizontal{ px + TILE_SIZE / 2 - 3, py + TILE_SIZE / 2 - 4, 6,8 };
			SDL_FRect pellet{ px + TILE_SIZE / 2 - 2, py + TILE_SIZE / 2 - 2, 4, 4 };

			switch (tile)
			{
			case dae::TileType::Empty:
				break;
			case dae::TileType::Wall:
				
				break;

			case dae::TileType::Pellet:
				SDL_SetRenderDrawColor(r, 255, 255, 255, 0);
				SDL_RenderFillRect(r, &pellet);
				break;

			case dae::TileType::PowerPellet:
				SDL_SetRenderDrawColor(r, 255, 255, 0, 0);
				SDL_RenderFillRect(r, &powerPelletVertical);
				SDL_RenderFillRect(r, &powerPelletHorizontal);				
				break;

			default:
				break;
			}
		}
	}

}

void dae::MazeRendererComponent::DrawPellet()
{

}

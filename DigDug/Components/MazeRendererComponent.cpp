#include "MazeRendererComponent.h"
#include "../Level.h"
#include "Renderer.h"
#include "GameObject.h"
#include "../GameSettings.h"
#include <iostream>
#include "../../Engine/TextureComponent.h"
#include "ResourceManager.h"


dae::MazeRendererComponent::MazeRendererComponent(GameObject* owner, Level* currentLevel)
	: Component(owner),
	m_CurrentLevel(currentLevel)
	//m_TextureComponent{ GetOwner()->GetComponent<TextureComponent>() }
{
	auto& resourceManager = dae::ResourceManager::GetInstance();
	m_PlayfieldTextures[static_cast<int>(dae::TileType::LayerOne)] = resourceManager.LoadTexture("Sprites/TileLayer1.png");
	m_PlayfieldTextures[static_cast<int>(dae::TileType::LayerTwo)] = resourceManager.LoadTexture("Sprites/TileLayer2.png");
	m_PlayfieldTextures[static_cast<int>(dae::TileType::LayerThree)] = resourceManager.LoadTexture("Sprites/TileLayer3.png");
	m_PlayfieldTextures[static_cast<int>(dae::TileType::LayerFour)] = resourceManager.LoadTexture("Sprites/TileLayer4.png");
	m_PlayfieldTextures[static_cast<int>(dae::TileType::DugTileVer)] = resourceManager.LoadTexture("Sprites/MaybeTempDugTile.png");
	m_PlayfieldTextures[static_cast<int>(dae::TileType::DugTileHor)] = resourceManager.LoadTexture("Sprites/MaybeTempDugTile.png");
	m_PlayfieldTextures[static_cast<int>(dae::TileType::Rock)] = resourceManager.LoadTexture("Sprites/Rock.png");
}

void dae::MazeRendererComponent::Render() const
{
	//Debug playfield
	SDL_Renderer* r = Renderer::GetInstance().GetSDLRenderer();
	SDL_SetRenderDrawBlendMode(r, SDL_BLENDMODE_BLEND);

	auto pos = GetOwner()->GetWorldPosition();

	for (int x = 0; x < m_CurrentLevel->MazeWidth(); x++)
	{
		for (int y = 0; y < m_CurrentLevel->MazeHeight(); y++)
		{
			TileType tile = m_CurrentLevel->GetTileAtPos(x, y);
			float px = pos.x + x * TILE_SIZE;
			float py = pos.y + y * TILE_SIZE;
			SDL_FRect debugTile{ px, py, 3, 3 };

			switch (tile)
			{
			case dae::TileType::Surface:

				break;
			case dae::TileType::LayerOne:

				Renderer::GetInstance().RenderTexture(*m_PlayfieldTextures[static_cast<int>(dae::TileType::LayerOne)], px, py, TILE_SIZE,TILE_SIZE);
				SDL_SetRenderDrawColor(r, 255, 0, 0, 50);
				SDL_RenderFillRect(r, &debugTile);
				break;
			case dae::TileType::LayerTwo:

				Renderer::GetInstance().RenderTexture(*m_PlayfieldTextures[static_cast<int>(dae::TileType::LayerTwo)], px, py, TILE_SIZE,TILE_SIZE);
				SDL_SetRenderDrawColor(r, 255, 0, 0, 50);
				SDL_RenderFillRect(r, &debugTile);
				break;
			case dae::TileType::LayerThree:

				Renderer::GetInstance().RenderTexture(*m_PlayfieldTextures[static_cast<int>(dae::TileType::LayerThree)], px, py, TILE_SIZE,TILE_SIZE);
				SDL_SetRenderDrawColor(r, 255, 0, 0, 50);
				SDL_RenderFillRect(r, &debugTile);
				break;
			case dae::TileType::LayerFour:

				Renderer::GetInstance().RenderTexture(*m_PlayfieldTextures[static_cast<int>(dae::TileType::LayerFour)], px, py, TILE_SIZE,TILE_SIZE);
				SDL_SetRenderDrawColor(r, 255, 0, 0, 50);
				SDL_RenderFillRect(r, &debugTile);
				break;
			case dae::TileType::DugTileVer:
				/*SDL_SetRenderDrawColor(r, 255, 0, 0, 30);
				SDL_RenderFillRect(r, &debugTile);*/

				Renderer::GetInstance().RenderTexture(*m_PlayfieldTextures[static_cast<int>(dae::TileType::DugTileVer)], px, py, TILE_SIZE,TILE_SIZE,90);
				break;
			case dae::TileType::DugTileHor:
				/*SDL_SetRenderDrawColor(r, 255, 0, 0, 30);
				SDL_RenderFillRect(r, &debugTile);*/

				Renderer::GetInstance().RenderTexture(*m_PlayfieldTextures[static_cast<int>(dae::TileType::DugTileHor)], px, py, TILE_SIZE, TILE_SIZE);
				break;
			case dae::TileType::Border:
				/*SDL_SetRenderDrawColor(r, 60, 60, 60, 50);
				SDL_RenderFillRect(r, &debugTile);*/

				break;
			case dae::TileType::Rock:

				Renderer::GetInstance().RenderTexture(*m_PlayfieldTextures[static_cast<int>(dae::TileType::Rock)], px, py, TILE_SIZE, TILE_SIZE);

				break;
			default:
				/*SDL_SetRenderDrawColor(r, 60, 60, 60, 50);
				SDL_RenderFillRect(r, &debugTile);*/
				break;
			}

		}
	}

}

void dae::MazeRendererComponent::FixedUpdate(const float)
{
}

void dae::MazeRendererComponent::Update(float)
{
}
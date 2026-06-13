#include "PlayerComponent.h"
#include "GameObject.h"
#include "../Level.h"
#include "GameSettings.h"
#include <SDL3/SDL.h>
#include "ScoreComponent.h"


dae::PlayerComponent::PlayerComponent(GameObject* owner, Level* level)
	:Component(owner),
	m_pLevel{ level },
	m_TargetTile{ MSPACMAN_START_POS },
	m_CurrentDirection{ 1,0 },
	m_DesiredDirection{},
	m_Speed{ 130.f }
{
	GetOwner()->SetLocalPosition({ MazeTileToWorldPosition(m_TargetTile.x,m_TargetTile.y).x,
								   MazeTileToWorldPosition(m_TargetTile.x,m_TargetTile.y).y,
								   0 });
}

void dae::PlayerComponent::SetDesiredDirection(const glm::vec2& direction)
{
	m_DesiredDirection = direction;
}


void dae::PlayerComponent::CheckTilePickUp()
{
	TileType tile = m_pLevel->GetTileAtPos(m_TargetTile.x, m_TargetTile.y);

	if (tile == TileType::Pellet)
	{
		m_pLevel->SetTileAtPos(m_TargetTile.x, m_TargetTile.y, TileType::Empty);
		GetOwner()->GetComponent<dae::ScoreComponent>()->AddScore(dae::PELLET_SCORE);
	}
	else if (tile == TileType::PowerPellet)
	{
		m_pLevel->SetTileAtPos(m_TargetTile.x, m_TargetTile.y, TileType::Empty);
		GetOwner()->GetComponent<dae::ScoreComponent>()->AddScore(dae::POWER_PELLET_SCORE);
		//and ghost state dizzy
	}

	if (m_pLevel->CountPellets() == 0)
	{
		SDL_Log("Next Level");
	}
}

glm::ivec2 dae::PlayerComponent::GetCurrentTile()
{
	return m_TargetTile;
}

void dae::PlayerComponent::FixedUpdate(const float)
{

}

void dae::PlayerComponent::MoveTowardTargetTile(const glm::vec2& currPos, const glm::vec2& targetPos, float deltaTime)
{
	glm::vec2 directionVec = targetPos - currPos;

	float distFromTarget = glm::length(directionVec);
	float moveDistance = m_Speed * deltaTime;

	if (distFromTarget <= moveDistance)
	{
		GetOwner()->SetLocalPosition({ targetPos.x, targetPos.y, 0 });
	}
	else
	{
		glm::vec2 newPos = currPos + glm::normalize(directionVec) * moveDistance;
		GetOwner()->SetLocalPosition({ newPos.x, newPos.y, 0 });
	}
}

void dae::PlayerComponent::Update(float deltaTime)
{
	glm::vec3 posVec3{ GetOwner()->GetLocalPosition() };
	glm::vec2 currentPos = { posVec3.x, posVec3.y };

	glm::vec2 targetPos = MazeTileToWorldPosition(m_TargetTile.x, m_TargetTile.y);

	MoveTowardTargetTile(currentPos, targetPos, deltaTime);

	if (dae::CheckIfArrivedAtTargetTile(currentPos, targetPos))
	{
		GetOwner()->SetLocalPosition({ targetPos.x,targetPos.y,0 });
		CheckTilePickUp();


		glm::ivec2 nextDesiredTile = m_TargetTile + glm::ivec2(m_DesiredDirection);
		glm::ivec2 nextCurrentTile = m_TargetTile + glm::ivec2(m_CurrentDirection);

		if (!m_pLevel->IsWall(nextDesiredTile.x, nextDesiredTile.y))
		{
			m_CurrentDirection = m_DesiredDirection;
			m_TargetTile = nextDesiredTile;
		}
		else if (!m_pLevel->IsWall(nextCurrentTile.x, nextCurrentTile.y))
		{
			m_TargetTile = nextCurrentTile;
		}
	}
}

void dae::PlayerComponent::Render() const
{
}
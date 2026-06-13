#include "GhostComponent.h"
#include "../GameSettings.h"
#include "../Level.h"
#include "PlayerComponent.h"
#include <glm/glm.hpp>
#include "../../Engine/GameObject.h"
#include "../States/GhostStates.h"
#include <array>
#include <SDL3/SDL.h>

dae::GhostComponent::GhostComponent(GameObject* owner, Level* level, PlayerComponent* player, GhostType type, glm::vec2 startWorldPos)
	: Component(owner),
	m_pLevel{ level },
	m_pPlayer{ player },
	m_Type{ type },
	m_CurrentTile{},
	m_ChaseTargetTile{},
	m_CurrentDirection{ 0,1 },
	m_Speed{ 75.f },
	m_StateMachine{ *this }
{
	m_HasExitedHouse = { !IsInBounds(WorldToMazeTilePosition(startWorldPos.x, startWorldPos.y), dae::GHOST_HOUSE) };
	GetOwner()->SetLocalPosition({ startWorldPos.x, startWorldPos.y, 0 });
	m_CurrentTile = WorldToMazeTilePosition(startWorldPos.x, startWorldPos.y);
	m_ChaseTargetTile = m_CurrentTile;


	m_StateMachine.ChangeState(std::make_unique<GhostChaseState>());
}

void dae::GhostComponent::FixedUpdate(const float fixedTimeStep)
{
	m_StateMachine.FixedUpdate(fixedTimeStep);
}

void dae::GhostComponent::Update(float deltaTime)
{
	m_StateMachine.Update(deltaTime);
}

void dae::GhostComponent::Render() const
{

}


void dae::GhostComponent::MoveTowardTargetTile(float deltaTime)
{
	glm::vec3 posVec3 = GetOwner()->GetLocalPosition();
	glm::vec2 currPos = { posVec3.x,posVec3.y };

	glm::vec2 targetPos = MazeTileToWorldPosition(m_CurrentTile.x, m_CurrentTile.y);

	glm::vec2 diff = targetPos - currPos;
	float dist = glm::length(diff);
	float moveDistance = m_Speed * deltaTime;

	if (dist <= moveDistance)
	{
		GetOwner()->SetLocalPosition({ targetPos.x,targetPos.y,0 });
	}
	else
	{
		glm::vec2 newPos = currPos + glm::normalize(diff) * moveDistance;
		GetOwner()->SetLocalPosition({ newPos.x,newPos.y,0 });
	}

	if (dae::CheckIfArrivedAtTargetTile(currPos, targetPos))
	{

		GetOwner()->SetLocalPosition({ targetPos.x,targetPos.y,0 });

		if (!m_HasExitedHouse && !IsInBounds(m_CurrentTile,dae::GHOST_HOUSE))
			m_HasExitedHouse = true;
		m_CurrentTile = PickBestDirection();
	}

}

glm::ivec2 dae::GhostComponent::PickBestDirection()
{
	const std::array<glm::ivec2, 4> directions = {
		glm::ivec2{1,0}, //right
		glm::ivec2{-1,0}, //left
		glm::ivec2{0,1}, //down
		glm::ivec2{0,-1} //up
	};

	glm::ivec2 oppositeDirection = -m_CurrentDirection;

	float bestDist = std::numeric_limits<float>::max();

	glm::ivec2 bestNextTile = m_CurrentTile;
	bool foundMove = false;

	for (const auto& direction : directions)
	{
		//skip direction behind
		if (direction == oppositeDirection)
			continue;

		glm::ivec2 nextTile = m_CurrentTile + direction;

		if (m_pLevel->IsWall(nextTile.x, nextTile.y))
			continue;

		if (m_HasExitedHouse && IsInBounds(nextTile, dae::GHOST_HOUSE))
			continue;

		glm::ivec2 diff = nextTile - m_ChaseTargetTile;
		float dist = static_cast<float>(diff.x * diff.x + diff.y * diff.y);

		if (dist < bestDist)
		{
			bestDist = dist;
			bestNextTile = nextTile;
			m_CurrentDirection = direction;
			foundMove = true;
		}
	}

	if (!foundMove)
	{
		glm::ivec2 reverseNext = m_CurrentTile + oppositeDirection;
		if (!m_pLevel->IsWall(reverseNext.x, reverseNext.y))
		{
			bestNextTile = reverseNext;
			m_CurrentDirection = oppositeDirection;
		}
	}


	return bestNextTile;
}

void dae::GhostComponent::SetChaseTarget(glm::ivec2 tile)
{
	m_ChaseTargetTile = tile;

}



//
glm::ivec2 dae::GhostComponent::GetCurrentTile() const
{
	return m_CurrentTile;
}

glm::ivec2 dae::GhostComponent::GetCurrentDirection() const
{
	return m_CurrentDirection;
}

dae::Level* dae::GhostComponent::GetLevel() const
{
	return m_pLevel;
}

dae::PlayerComponent* dae::GhostComponent::GetPlayerComp() const
{
	return m_pPlayer;
}

dae::GhostType dae::GhostComponent::GetGhostType() const
{
	return m_Type;
}

bool dae::GhostComponent::HasExitedHouse() const
{
	return m_HasExitedHouse;
}


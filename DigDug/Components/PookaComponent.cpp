#include "PookaComponent.h"
#include "../GameSettings.h"
#include "../Level.h"
#include "PlayerComponent.h"
#include <glm/glm.hpp>
#include "../../Engine/GameObject.h"
#include "../States/PookaStates.h"
#include <array>
#include <SDL3/SDL.h>
#include "SpriteAnimationComponent.h"
#include "../../Engine/State/StateMachine.h"
#include "Event.h"


dae::PookaComponent::PookaComponent(GameObject* owner, Level* level, PlayerComponent* player, glm::vec2 startWorldPos)
	: Component(owner),
	m_pLevel{ level },
	m_AnimationComponent{ owner->GetComponent<dae::SpriteAnimationComponent>() },
	m_pPlayer{ player },
	m_pPlayerTwo(nullptr),
	m_CurrentTile{},
	m_TargetTile{},
	m_CurrentDirection{ 1,0 },
	m_Speed{ dae::POOKA_SPEED },
	m_StateMachine{ *this },
	m_CurrentWorldPos{},
	m_pGameObject{ owner },
	m_SavedSpawnPoint{ startWorldPos }
{
	m_CurrentTile = dae::WorldPositionToPlayfieldTile(startWorldPos.x, startWorldPos.y);
	m_TargetTile = m_CurrentTile;

	auto currentStartTile = dae::PlayfieldTileToWorldPosition(m_CurrentTile.x, m_CurrentTile.y);
	GetOwner()->SetLocalPosition(currentStartTile);

	m_StateMachine.ChangeState(std::make_unique<dae::PookaNormalState>());
}

dae::PookaComponent::PookaComponent(GameObject* owner, Level* level, PlayerComponent* playerOne, PlayerComponent* playerTwo, glm::vec2 startWorldPos)
	: Component(owner),
	m_pLevel{ level },
	m_AnimationComponent{ owner->GetComponent<dae::SpriteAnimationComponent>() },
	m_pPlayer{ playerOne },
	m_pPlayerTwo(playerTwo),
	m_CurrentTile{},
	m_TargetTile{},
	m_CurrentDirection{ 1,0 },
	m_Speed{ dae::POOKA_SPEED },
	m_StateMachine{ *this },
	m_CurrentWorldPos{},
	m_pGameObject{ owner },
	m_SavedSpawnPoint{ startWorldPos }
{
	m_CurrentTile = dae::WorldPositionToPlayfieldTile(startWorldPos.x, startWorldPos.y);
	m_TargetTile = m_CurrentTile;

	auto currentStartTile = dae::PlayfieldTileToWorldPosition(m_CurrentTile.x, m_CurrentTile.y);
	GetOwner()->SetLocalPosition(currentStartTile);

	m_StateMachine.ChangeState(std::make_unique<dae::PookaNormalState>());
}



void dae::PookaComponent::PookaNotifyEnemyDied()
{

	float height = GetOwner()->GetLocalPosition().y;



	if (height >= dae::PLAYFIELD_HEIGHT_SURFACE.x && height < dae::PLAYFIELD_HEIGHT_SURFACE.y)
	{
		m_Subject.NotifyObservers(EventsId::scoreLayerOne, GetOwner());
	}
	else if (height >= dae::PLAYFIELD_HEIGHT_ONE.x && height < dae::PLAYFIELD_HEIGHT_ONE.y)
	{
		m_Subject.NotifyObservers(EventsId::scoreLayerOne, GetOwner());
	}
	else if (height >= dae::PLAYFIELD_HEIGHT_TWO.x && height < dae::PLAYFIELD_HEIGHT_TWO.y)
	{
		m_Subject.NotifyObservers(EventsId::scoreLayerTwo, GetOwner());
	}
	else if (height >= dae::PLAYFIELD_HEIGHT_THREE.x && height < dae::PLAYFIELD_HEIGHT_THREE.y)
	{
		m_Subject.NotifyObservers(EventsId::scoreLayerThree, GetOwner());
	}
	else if (height >= dae::PLAYFIELD_HEIGHT_FOUR.x && height < dae::PLAYFIELD_HEIGHT_FOUR.y)
	{
		m_Subject.NotifyObservers(EventsId::scoreLayerFour, GetOwner());
	}
	else
	{

		m_Subject.NotifyObservers(EventsId::scoreLayerOne, GetOwner());
	}


	m_Subject.NotifyObservers(EventsId::enemyKilled, this->GetOwner());

	GetOwner()->MarkForDelete();
}

void dae::PookaComponent::PookaNotifyPlayerDied()
{
	m_Subject.NotifyObservers(EventsId::playerDied, this->GetOwner());
}

void dae::PookaComponent::RestartSpawnPoint()
{
	GetOwner()->SetLocalPosition(m_SavedSpawnPoint);
	m_StateMachine.ChangeState(std::make_unique<dae::PookaGhostState>());
}

void dae::PookaComponent::FixedUpdate(const float fixedTimeStep)
{
	m_StateMachine.FixedUpdate(fixedTimeStep);
}

void dae::PookaComponent::Update(float deltaTime)
{

	m_CurrentWorldPos = { GetOwner()->GetLocalPosition() };
	m_StateMachine.Update(deltaTime);
}

bool dae::PookaComponent::IsBeingHit() const
{
	auto pookaRect = m_AnimationComponent->GetDstRect();
	pookaRect.w = pookaRect.w * 0.75f;
	pookaRect.h = pookaRect.h * 0.75f;

	if (m_pPlayer &&
		m_pPlayer->IsAttacking() &&
		dae::AABB(m_pPlayer->GetAttackHitbox(), pookaRect))
	{
		return true;
	}

	if (m_pPlayerTwo &&
		m_pPlayerTwo->IsAttacking() &&
		dae::AABB(m_pPlayerTwo->GetAttackHitbox(), pookaRect))
	{
		return true;
	}

	return false;
}

bool dae::PookaComponent::IsPookaHittingPlayer() const
{

	auto pookaRect = m_AnimationComponent->GetDstRect();
	pookaRect.w *= 0.75f;
	pookaRect.h *= 0.75f;

	if (m_pPlayer)
	{
		auto playerRect = m_pPlayer->GetPlayerRect();
		playerRect.w *= 0.75f;
		playerRect.h *= 0.75f;

		if (dae::AABB(playerRect, pookaRect))
			return true;
	}

	if (m_pPlayerTwo)
	{
		auto playerTwoRect = m_pPlayerTwo->GetPlayerRect();
		playerTwoRect.w *= 0.75f;
		playerTwoRect.h *= 0.75f;

		if (dae::AABB(playerTwoRect, pookaRect))
			return true;
	}

	return false;
}


void dae::PookaComponent::Render() const
{
}

void dae::PookaComponent::MoveTowardTargetTile(float deltaTime)
{
	glm::vec3 posVec3 = GetOwner()->GetLocalPosition();
	glm::vec2 currPos = { posVec3.x,posVec3.y };

	glm::vec2 targetPos = PlayfieldTileToWorldPosition(m_CurrentTile.x, m_CurrentTile.y);

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

		m_CurrentTile = PickBestDirection();
	}

}

void dae::PookaComponent::SetSpeed(float speed)
{
	m_Speed = speed;
}

glm::ivec2 dae::PookaComponent::PickBestDirection()
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
		if (direction == oppositeDirection)
			continue;

		glm::ivec2 nextTile = m_CurrentTile + direction;

		if (m_pLevel->IsAnyTypeOfLayer(nextTile))
			continue;

		if (!m_pLevel->CanMove(nextTile))
			continue;

		glm::ivec2 diff = nextTile - m_TargetTile;
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

void dae::PookaComponent::SnapToNearestDugTile(const glm::vec2& worldPos)
{
	m_CurrentTile = dae::WorldPositionToPlayfieldTile(worldPos.x, worldPos.y);
	m_TargetTile = m_CurrentTile;

	glm::vec2 snapPos = dae::PlayfieldTileToWorldPosition(m_CurrentTile.x, m_CurrentTile.y);
	GetOwner()->SetLocalPosition(snapPos);
}

void dae::PookaComponent::SetChaseTarget(glm::ivec2 tile)
{
	m_TargetTile = tile;
}

glm::ivec2 dae::PookaComponent::GetCurrentTile() const
{
	return m_CurrentTile;
}

glm::ivec2 dae::PookaComponent::GetCurrentDirection() const
{
	return m_CurrentDirection;
}

dae::Level* dae::PookaComponent::GetLevel() const
{
	return m_pLevel;
}

dae::PlayerComponent* dae::PookaComponent::GetPlayerComp() const
{
	return m_pPlayer;
}

dae::PlayerComponent* dae::PookaComponent::GetPlayerTwoComp() const
{
	return m_pPlayerTwo;
}

dae::SpriteAnimationComponent* dae::PookaComponent::GetAnimationComp() const
{
	return m_AnimationComponent;
}

dae::GameObject* dae::PookaComponent::GetGameObject() const
{
	return m_pGameObject;
}


#include "PookaStates.h"
#include "../Components/PookaComponent.h"
#include "../Components/PlayerComponent.h"
#include "GameSettings.h"
#include "SpriteAnimationComponent.h"
#include "../../Engine/State/StateMachine.h"
#include <iostream>
#include <glm/gtc/random.hpp>
#include "../../Engine/GameObject.h"
#include "../../Engine/Component.h"
#include "../Level.h"


/// <summary>
/// PookaNormalState
/// </summary>
dae::PookaNormalState::PookaNormalState()
{

}

dae::PookaNormalState::~PookaNormalState()
{

}

void dae::PookaNormalState::OnEnter(PookaComponent& owner)
{
	m_NormalStateTimer = 0.f;
	m_MaxNormalTimer = glm::linearRand(6.0f, 20.0f);
	owner.SetSpeed(dae::POOKA_SPEED);

	std::cout << "PookaNormalState" << std::endl;
	owner.GetAnimationComp()->SetAnimation("Sprites/PookaWalking.png", 2, 3.f);

	auto currDirection = owner.GetCurrentDirection();
	glm::ivec2 farOffTile = owner.GetCurrentTile() + currDirection * 100;

	owner.SetChaseTarget(farOffTile);
}

void dae::PookaNormalState::OnExit(PookaComponent&)
{

}

void dae::PookaNormalState::Update(PookaComponent& owner, float deltaTime)
{
	if (owner.IsBeingHit())
	{
		owner.GetStateMachine().ChangeState(std::make_unique<PookaInflatingState>());
		return;
	}

	if (owner.IsPookaHittingPlayer())
	{
		std::cout << "Pooka Hit Player";
		owner.PookaNotifyPlayerDied();
		owner.RestartSpawnPoint();
		return;
	}

	m_NormalStateTimer += deltaTime;

	owner.MoveTowardTargetTile(deltaTime);

	auto vec = static_cast<glm::vec2>(owner.GetPlayerComp()->GetCurrentTile() - owner.GetCurrentTile());

	float distanceToPlayer = glm::length(vec);
	if (distanceToPlayer < dae::POOKA_CHASE_DISTANCE)
	{
		owner.GetStateMachine().ChangeState(std::make_unique<dae::PookaChaseState>());
	}

	if (m_NormalStateTimer > m_MaxNormalTimer)
	{
		owner.GetStateMachine().ChangeState(std::make_unique<dae::PookaGhostState>());
	}
}

void dae::PookaNormalState::FixedUpdate(PookaComponent&, float)
{

}

/// <summary>
/// PookaChaseState
/// </summary>
dae::PookaChaseState::PookaChaseState()
{

}

dae::PookaChaseState::~PookaChaseState()
{

}

void dae::PookaChaseState::OnEnter(PookaComponent& owner)
{
	std::cout << "PookaChaseState" << std::endl;
	m_ChaseStateTimer = 0.f;
	m_MaxChaseTimer = glm::linearRand(10.0f, 30.0f);
	owner.SetSpeed(dae::POOKA_CHASE_SPEED);


	owner.GetAnimationComp()->SetAnimation("Sprites/PookaWalking.png", 2, 6.f);
}

void dae::PookaChaseState::OnExit(PookaComponent&)
{

}

void dae::PookaChaseState::Update(PookaComponent& owner, float deltaTime)
{
	if (owner.IsBeingHit())
	{
		owner.GetStateMachine().ChangeState(std::make_unique<PookaInflatingState>());
		return;
	}

	if (owner.IsPookaHittingPlayer())
	{
		std::cout << "Pooka Hit Player";
		owner.PookaNotifyPlayerDied();
		owner.RestartSpawnPoint();
		return;
	}

	m_ChaseStateTimer += deltaTime;


	owner.SetChaseTarget(owner.GetPlayerComp()->GetCurrentTile());
	owner.MoveTowardTargetTile(deltaTime);

	auto vec = static_cast<glm::vec2>(owner.GetPlayerComp()->GetCurrentTile() - owner.GetCurrentTile());
	float distanceToPlayer = glm::length(vec);
	if (distanceToPlayer > dae::POOKA_CHASE_DISTANCE * 1.5f)
	{
		owner.GetStateMachine().ChangeState(std::make_unique<dae::PookaNormalState>());
	}

	if (m_ChaseStateTimer > m_MaxChaseTimer)
	{
		owner.GetStateMachine().ChangeState(std::make_unique<dae::PookaGhostState>());
	}
}

void dae::PookaChaseState::FixedUpdate(PookaComponent&, float)
{

}

/// <summary>
/// PookaGhostState
/// </summary>
dae::PookaGhostState::PookaGhostState()
{

}

dae::PookaGhostState::~PookaGhostState()
{

}

void dae::PookaGhostState::OnEnter(PookaComponent& owner)
{
	std::cout << "PookaGhostState" << std::endl;
	owner.GetAnimationComp()->SetAnimation("Sprites/PookaGhost.png", 2, 2.f);

	m_GhostTimer = 0.f;
	m_MinimumGhostnvulnerability = glm::linearRand(3.0f, 6.0f);
}

void dae::PookaGhostState::OnExit(PookaComponent&)
{

}

void dae::PookaGhostState::Update(PookaComponent& owner, float deltaTime)
{
	if (owner.IsBeingHit())
	{
		owner.GetStateMachine().ChangeState(std::make_unique<PookaInflatingState>());
		return;
	}

	m_GhostTimer += deltaTime;
	glm::vec2 currPookaPos = owner.GetGameObject()->GetLocalPosition();


	glm::ivec2 playerTilePos = owner.GetPlayerComp()->GetCurrentTile();
	glm::vec2 playerWorldPos = dae::PlayfieldTileToWorldPosition(playerTilePos.x, playerTilePos.y);

	glm::vec2 vec = playerWorldPos - currPookaPos;
	//float distToTarget = glm::length(vec);

	if (CheckSquaredDist(currPookaPos, playerWorldPos) > 0.01f * 0.01f)
	{
		glm::vec2 moveDirection = glm::normalize(vec);
		glm::vec2 newPos = currPookaPos + moveDirection * dae::POOKA_GHOST_SPEED * deltaTime;
		owner.GetGameObject()->SetLocalPosition({ newPos.x,newPos.y });
	}

	if (m_GhostTimer > m_MinimumGhostnvulnerability)
	{

		glm::ivec2 currentGhostTilePos = WorldPositionToPlayfieldTile(currPookaPos.x, currPookaPos.y);
		dae::TileType tile = owner.GetLevel()->GetTileAtPos(currentGhostTilePos.x, currentGhostTilePos.y);
		if (tile == TileType::Surface || tile == TileType::DugTileVer || tile == TileType::DugTileHor)
		{
			owner.SnapToNearestDugTile(currPookaPos);
			owner.GetStateMachine().ChangeState(std::make_unique<dae::PookaNormalState>());
		}
	}


}

void dae::PookaGhostState::FixedUpdate(PookaComponent&, float)
{

}

/// <summary>
/// PookaInflatingState
/// </summary>
dae::PookaInflatingState::PookaInflatingState()
{
}

dae::PookaInflatingState::~PookaInflatingState()
{
}

void dae::PookaInflatingState::OnEnter(PookaComponent& owner)
{
	std::cout << "PookaInflatingState" << std::endl;
	m_InflatingTimer = 0.f;
	m_HitCountTimer = 0.f;

	owner.GetAnimationComp()->SetAnimation("Sprites/PookaInflate.png", 3, 0.8f);

}

void dae::PookaInflatingState::OnExit(PookaComponent&)
{
}

void dae::PookaInflatingState::Update(PookaComponent& owner, float deltaTime)
{
	m_InflatingTimer += deltaTime;

	if (owner.IsBeingHit())
	{
		m_HitCountTimer += deltaTime;

		m_InflatingTimer = 0.f;
		if (m_HitCountTimer >= m_PookaHitsToPop)
		{
			owner.GetStateMachine().ChangeState(std::make_unique<PookaBlownUpState>());
			return;
		}
	}

	if (m_InflatingTimer > m_MaxGoBackToNormalTimer)
	{
		owner.GetStateMachine().ChangeState(std::make_unique<PookaNormalState>());
	}
}

void dae::PookaInflatingState::FixedUpdate(PookaComponent&, float)
{
}

/// <summary>
/// PookaBlownUpState
/// </summary>
dae::PookaBlownUpState::PookaBlownUpState()
{
}

dae::PookaBlownUpState::~PookaBlownUpState()
{
}

void dae::PookaBlownUpState::OnEnter(PookaComponent& owner)
{
	std::cout << "PookaBlownUpState" << std::endl;
	m_DeathTimer = 0.f;
	owner.GetAnimationComp()->SetAnimation("Sprites/PookaPop.png", 1, 1.f);
}

void dae::PookaBlownUpState::OnExit(PookaComponent& )
{
}

void dae::PookaBlownUpState::Update(PookaComponent& owner, float deltaTime)
{
	m_DeathTimer += deltaTime;

	if (m_DeathTimer > m_DeathAnimTime)
	{
		owner.PookaNotifyEnemyDied();
	}
}



void dae::PookaBlownUpState::FixedUpdate(PookaComponent&, float)
{
}

/// <summary>
/// PookaCrushedState
/// </summary>
dae::PookaCrushedState::PookaCrushedState()
{
}

dae::PookaCrushedState::~PookaCrushedState()
{
}

void dae::PookaCrushedState::OnEnter(PookaComponent&)
{
	std::cout << "PookaCrushedState" << std::endl;

}

void dae::PookaCrushedState::OnExit(PookaComponent&)
{
}

void dae::PookaCrushedState::Update(PookaComponent&, float)
{
}

void dae::PookaCrushedState::FixedUpdate(PookaComponent&, float)
{
}

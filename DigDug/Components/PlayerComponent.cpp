#include "PlayerComponent.h"
#include "GameObject.h"
#include "../Level.h"
#include "GameSettings.h"
#include <SDL3/SDL.h>
#include "SpriteAnimationComponent.h"
#include <iostream>
#include "Renderer.h"
#include "ResourceManager.h"
#include "../../Engine/Texture2D.h"
#include "Event.h"
#include "LivesComponent.h"
#include "Sound/ServiceLocator.cpp"


dae::PlayerComponent::PlayerComponent(GameObject* owner, Level* level, const glm::vec2& startPos)
	:Component(owner),
	m_pLevel{ level },
	m_AnimationComponent{ GetOwner()->GetComponent<SpriteAnimationComponent>() },
	m_Speed{ dae::PLAYER_SPEED },
	m_CurrentDirection{ 0.f,0.f },
	m_DesiredDirection{},
	m_CurrentTile{},
	//m_isMovingHorizontally{},
	//m_isMoving{},
	m_CurrentWorldPos{}
{
	m_PumpTexture = dae::ResourceManager::GetInstance().LoadTexture("Sprites/PlayerPump.png");
	RestartPlayer(startPos);
	m_SavedRespawnPos = startPos;
}

void dae::PlayerComponent::Render() const
{
	if (m_IsAttacking)
	{
		/*auto box = GetAttackHitbox();
		SDL_Renderer* r = Renderer::GetInstance().GetSDLRenderer();
		SDL_SetRenderDrawColor(r, 255, 0, 0, 100);
		SDL_RenderFillRect(r, &box);*/

		RevealPumpWeapon();
	}
}

void dae::PlayerComponent::FixedUpdate(const float)
{

}

void dae::PlayerComponent::CheckIfTileIsDug()
{
	glm::vec3 worldPos{ GetOwner()->GetLocalPosition() };
	glm::ivec2 currentPos = { WorldPositionToPlayfieldTile(worldPos.x,worldPos.y) };


	TileType tile = m_pLevel->GetTileAtPos(currentPos.x, currentPos.y);

	//dig
	if ((tile == TileType::LayerOne || tile == TileType::LayerTwo || tile == TileType::LayerThree || tile == TileType::LayerFour) && tile != TileType::DugTileVer && tile != TileType::DugTileHor)
	{
		m_JustDug = true;
		m_DigStateTimer = 0.f;

		if (m_AnimationComponent->GetSpriteRotation() <= -90.f || m_AnimationComponent->GetSpriteRotation() >= 90.f)
		{
			m_pLevel->SetTileAtPos(currentPos.x, currentPos.y, TileType::DugTileVer);
		}
		else if (m_AnimationComponent->GetSpriteRotation() == 0)
		{
			m_pLevel->SetTileAtPos(currentPos.x, currentPos.y, TileType::DugTileHor);
		}

		//GetOwner()->GetComponent<dae::ScoreComponent>()->AddScore(dae::PELLET_SCORE); //make event notify observer
	}



	//if (m_pLevel->CountPellets() == 0)
	//{
	//	SDL_Log("Next Level");
	//}
}


//-Movement-
void dae::PlayerComponent::RestartPlayer(const glm::vec2& startPos)
{
	m_SavedRespawnPos = { startPos };
	m_AnimationComponent->SetIsAnimated(false);
	m_CurrentTile = dae::WorldPositionToPlayfieldTile(startPos.x, startPos.y);
	m_TargetTile = m_CurrentTile;
	m_CurrentDirection = { 0.f, 0.f };
	m_DesiredDirection = { 0.f, 0.f };

	glm::vec2 tileWorldPos = dae::PlayfieldTileToWorldPosition(m_CurrentTile.x, m_CurrentTile.y);
	GetOwner()->SetLocalPosition(tileWorldPos);
}

void dae::PlayerComponent::Update(float deltaTime)
{
	m_CurrentWorldPos = GetOwner()->GetLocalPosition();
	glm::ivec2 currentPos = { WorldPositionToPlayfieldTile(m_CurrentWorldPos.x,m_CurrentWorldPos.y) };
	TileType tile = m_pLevel->GetTileAtPos(currentPos.x, currentPos.y);
	

	if (m_IsAlreadyDying)
	{
		m_DeathTimer += deltaTime;

		if (m_DeathTimer >= m_MaxDeathTimer)
		{
			GetOwner()->GetComponent<LivesComponent>()->TakeLife();
			if (GetOwner()->GetComponent<LivesComponent>()->GetLivesLeft() < 0)
			{
				PlayerGameOver();
			}

			RestartPlayer(m_SavedRespawnPos);
			m_IsAlreadyDying = false;
			m_DeathTimer = 0.f;
		}
		return;
	}

	if (m_IsAttacking)
	{
		m_AttackTimer += deltaTime;

		if (m_AttackTimer > m_MaxAttackDuration)
		{
			m_IsAttacking = false;
		}
	}

	if (m_JustDug)
	{
		m_DigStateTimer += deltaTime;
		ChangeState(PlayerState::Digging);

		if (m_DigStateTimer > m_DigStateHoldTime)
		{
			m_JustDug = false;
		}
	}


	if (!m_IsAttacking && m_DesiredDirection.x == 0.f && m_DesiredDirection.y == 0.f)
	{
		//m_TargetTile = m_CurrentTile;

		ChangeState(PlayerState::Idle);
		return;
	}
	else if (!m_IsAttacking && !m_JustDug && (tile == TileType::Surface || tile == TileType::DugTileHor || tile == TileType::DugTileVer))
	{
		ChangeState(PlayerState::Walking);
	}
	


	if (m_DesiredDirection == dae::GetOppositeDirection(m_CurrentDirection))
	{
		std::swap(m_CurrentTile, m_TargetTile);
		m_CurrentDirection = m_DesiredDirection;
	}

	glm::vec2 targetWorldPos = dae::PlayfieldTileToWorldPosition(m_TargetTile.x, m_TargetTile.y);
	glm::vec2 moveVector = targetWorldPos - m_CurrentWorldPos;
	float distToTarget = glm::length(moveVector);

	if (m_IsAttacking) return;
	if (distToTarget < 0.5f)
	{
		GetOwner()->SetLocalPosition(targetWorldPos);
		m_CurrentTile = m_TargetTile;

		CheckIfTileIsDug();

		if (m_DesiredDirection.x != 0.f || m_DesiredDirection.y != 0.f)
		{
			
			TryChangeDirection(m_DesiredDirection);
		}
	}
	else
	{
		glm::vec2 moveDir = glm::normalize(moveVector);
		glm::vec2 newPos = m_CurrentWorldPos + moveDir * m_Speed * deltaTime;
		GetOwner()->SetLocalPosition(newPos);
	}

}

void dae::PlayerComponent::TryChangeDirection(const glm::vec2& desiredDirection)
{
	glm::ivec2 nextTile = m_CurrentTile + glm::ivec2(desiredDirection);

	if (m_pLevel->CanMove(nextTile))
	{
		m_TargetTile = nextTile;
		m_CurrentDirection = desiredDirection;
		m_AnimationComponent->SetFlipMode(m_AnimationComponent->GetFlipMode());
		m_AnimationComponent->SetSpriteRotation(m_AnimationComponent->GetSpriteRotation());
	}
}


void dae::PlayerComponent::SetDesiredDirection(const glm::vec2& desiredDirection, SDL_FlipMode flipMode, double spriteRotation)
{
	m_DesiredDirection = desiredDirection;
	m_AnimationComponent->SetFlipMode(flipMode);
	m_AnimationComponent->SetSpriteRotation(spriteRotation);
	//m_AnimationComponent->SetIsAnimated(true);
	

}

void dae::PlayerComponent::StopDesiredDirection(const glm::vec2&)
{
	//m_AnimationComponent->SetIsAnimated(false);
	m_DesiredDirection = { 0.f,0.f };
}

void dae::PlayerComponent::ChangeState(PlayerState newState)
{
	auto& ss = dae::ServiceLocator::GetSoundSystem();
	if (m_CurrentState == newState) return;

	m_CurrentState = newState;



	switch (m_CurrentState)
	{
	case dae::PlayerState::Idle:
		std::cout << "Player Idle" << std::endl;
		m_AnimationComponent->SetAnimation("Sprites/PlayerIdle.png", 1, 1.f);
		break;
	case dae::PlayerState::Walking:
		std::cout << "Player Walking" << std::endl;
		m_AnimationComponent->SetAnimation("Sprites/PlayerWalking.png", 2, 5.f);
		break;
	case dae::PlayerState::Digging:
		std::cout << "Player Digging" << std::endl;
		m_AnimationComponent->SetAnimation("Sprites/PlayerDigging.png", 2, 5.f);
		break;
	case dae::PlayerState::Attacking:
		std::cout << "Player Attack" << std::endl;
		m_AnimationComponent->SetAnimation("Sprites/PlayerInflating.png", 2, 5.f);
		ss.PlayAudio(5, 1.f);
		break;
	case dae::PlayerState::Dying:
		std::cout << "Player Dying" << std::endl;
		m_AnimationComponent->SetAnimation("Sprites/PlayerDeath.png", 5, 2.5f);
		//player dying sound
		ss.PlayAudio(1, 1.f);
		break;
	case dae::PlayerState::Squashed:
		m_AnimationComponent->SetAnimation("Sprites/PlayerSquashed.png", 1, 1.f);
		break;
	default:
		break;
	}

	switch (m_CurrentState)
	{
	case dae::PlayerState::Idle:
		
		break;
	case dae::PlayerState::Walking:
		
	case dae::PlayerState::Digging:
		
		ss.PlayAudio(2, 1.f);
		break;
	case dae::PlayerState::Attacking:
		
		break;
	case dae::PlayerState::Dying:
		
		break;
	case dae::PlayerState::Squashed:
		
		break;
	default:
		break;
	}
}

glm::ivec2 dae::PlayerComponent::GetCurrentTile() const
{
	return m_TargetTile;
}

void dae::PlayerComponent::StarkAttack()
{
	m_IsAttacking = true;
	m_AttackTimer = 0.f;
	ChangeState(PlayerState::Attacking);

}

SDL_FRect dae::PlayerComponent::GetAttackHitbox() const
{
	glm::vec2 playerWPos = m_CurrentWorldPos;
	float pumpWidth = dae::TILE_SIZE * 2.f;
	float pumpHeight = dae::TILE_SIZE / 2;
	SDL_FRect attackBox{};

	if (m_CurrentDirection.x != 0.f) //hor
	{
		if (m_CurrentDirection.x > 0.f)
			attackBox.x = playerWPos.x;
		else
			attackBox.x = playerWPos.x - pumpWidth;

		attackBox.y = playerWPos.y - pumpHeight / 2;

		attackBox.w = pumpWidth;
		attackBox.h = pumpHeight;

	}
	else
	{
		if (m_CurrentDirection.y > 0.f)
			attackBox.y = playerWPos.y;
		else
			attackBox.y = playerWPos.y - pumpWidth;

		attackBox.x = playerWPos.x - pumpHeight / 2;

		attackBox.w = pumpHeight;
		attackBox.h = pumpWidth;
	}

	return attackBox;
}

void dae::PlayerComponent::RevealPumpWeapon() const
{
	auto rawSize = m_PumpTexture->GetSize();
	glm::vec2 scaledSize{ rawSize.x * dae::SIZE_MULTIPLIER, rawSize.y * dae::SIZE_MULTIPLIER };

	SDL_FRect srcRect{ 0, 0, static_cast<float>(rawSize.x), static_cast<float>(rawSize.y) };
	SDL_FRect dstRect{};
	float offset = dae::TILE_SIZE / 4.f;
	double rotation = 0.0;
	SDL_FlipMode flip = SDL_FLIP_NONE;


	if (m_CurrentDirection.x > 0.f) // right
	{
		dstRect = { m_CurrentWorldPos.x + offset, m_CurrentWorldPos.y - scaledSize.y / 2.f, scaledSize.x, scaledSize.y };
		flip = SDL_FLIP_HORIZONTAL;
	}
	else if (m_CurrentDirection.x < 0.f) // left
	{
		dstRect = { m_CurrentWorldPos.x - scaledSize.x - offset, m_CurrentWorldPos.y - scaledSize.y / 2.f, scaledSize.x, scaledSize.y };

	}
	else if (m_CurrentDirection.y < 0.f) // up
	{
		dstRect = { m_CurrentWorldPos.x - scaledSize.y , m_CurrentWorldPos.y - scaledSize.x + offset, scaledSize.y * 2 , scaledSize.x / 2 };
		rotation = 90.0;
	}
	else if (m_CurrentDirection.y > 0.f) // down
	{
		dstRect = { m_CurrentWorldPos.x - scaledSize.y  , m_CurrentWorldPos.y + offset * 3, scaledSize.y * 2, scaledSize.x / 2 };
		rotation = -90.0;
	}
	Renderer::GetInstance().RenderTexture(*m_PumpTexture, srcRect, dstRect, rotation, flip);
}

bool dae::PlayerComponent::IsAttacking() const
{
	return m_IsAttacking;
}

void dae::PlayerComponent::PlayerLoseLife()
{
	if (m_IsAlreadyDying) return;
	m_IsAlreadyDying = true;

	ChangeState(PlayerState::Dying);

}


void dae::PlayerComponent::OnNotify(unsigned int event, GameObject*)
{
	if (event == EventsId::playerDied)
	{
		PlayerLoseLife();
	}
}

void dae::PlayerComponent::PlayerGameOver()
{

}

SDL_FRect dae::PlayerComponent::GetPlayerRect() const
{
	return m_AnimationComponent->GetDstRect();
}

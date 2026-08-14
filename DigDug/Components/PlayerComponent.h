#pragma once
#include "Component.h"
#include <glm/glm.hpp>
#include <SDL3/SDL.h>
#include <memory>
#include "Observer/Observer.h"


namespace dae
{
	enum class PlayerState
	{
		Idle,
		Walking,
		Digging,
		Attacking,
		Dying,
		Squashed
	};

	class Level;
	class SpriteAnimationComponent;
	class Texture2D;
	class PlayerComponent :public Component, public dae::Observer
	{
	public:
		PlayerComponent(GameObject* owner, Level* level, const glm::vec2& startPos);


		void SetDesiredDirection(const glm::vec2& desiredDirection, SDL_FlipMode flipMode, double spriteRotation);
		void StopDesiredDirection(const glm::vec2& desiredDirection);
		void RestartPlayer(const glm::vec2& startPos);
		glm::ivec2 GetCurrentTile() const;

		void StarkAttack();
		SDL_FRect GetAttackHitbox() const;
		bool IsAttacking() const;

		void PlayerLoseLife();
		void PlayerGameOver();
		SDL_FRect GetPlayerRect() const;

		
	private:
		// Inherited via Component
		void FixedUpdate(const float fixedTimeStep) override;
		void Update(float elapsedSec) override;
		void Render() const override;

		void CheckIfTileIsDug();
		void TryChangeDirection(const glm::vec2& desiredDirection);
		void RevealPumpWeapon() const;



		dae::Level* m_pLevel;
		dae::SpriteAnimationComponent* m_AnimationComponent;


		//-Movement-
		float m_Speed{};
		glm::vec2 m_CurrentDirection{};
		glm::vec2 m_DesiredDirection{};

		glm::ivec2 m_CurrentTile{}; //currently at
		glm::ivec2 m_TargetTile{}; //going to here

	/*	bool m_isMovingHorizontally{};
		bool m_isMoving{};*/

		glm::vec2 m_CurrentWorldPos{};
		glm::vec2 m_SavedRespawnPos{};

		//States
		PlayerState m_CurrentState{ PlayerState::Idle };
		void ChangeState(PlayerState newState);


		// -Idle-

		// -Digging-
		bool m_JustDug{ false };
		float m_DigStateTimer{ 0.f };
		const float m_DigStateHoldTime{ .65f };

		// -Attack/Inflating-
		bool m_IsAttacking{ false };
		float m_AttackTimer{ 0.f };
		const float m_MaxAttackDuration = 0.45f;

		std::shared_ptr<Texture2D> m_PumpTexture{ nullptr };
	/*	float m_PumpTextureGrowTimer{ 0.f };
		const float m_PumpGrowTime{ 0.25f };*/

		// -Death-
		bool m_IsAlreadyDying{ false };
		float m_DeathTimer{ 0.f };
		float m_MaxDeathTimer{ 0.5f };

		// Inherited via Observer
		void OnNotify(unsigned int event, GameObject* actor) override;

		
	};

}

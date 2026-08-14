#pragma once
#include "Component.h"
#include <glm/glm.hpp>
#include "../../Engine/State/StateMachine.h"
#include "Observer/Subject.h"

namespace dae
{
	class Level;
	class PlayerComponent;
	class SpriteAnimationComponent;
	class PookaComponent :public Component
	{
	public:
		PookaComponent(GameObject* owner, Level* level, PlayerComponent* player, glm::vec2 startWorldPos);
		PookaComponent(GameObject* owner, Level* level, PlayerComponent* playerOne, PlayerComponent* playerTwo, glm::vec2 spawnPos);
		~PookaComponent() = default;

		void MoveTowardTargetTile(float deltaTime);
		void SetSpeed(float speed);
		void SetChaseTarget(glm::ivec2 tile);
		glm::ivec2 GetCurrentTile() const;
		glm::ivec2 GetCurrentDirection() const;
		Level* GetLevel() const;
		PlayerComponent* GetPlayerComp() const;
		dae::PlayerComponent* GetPlayerTwoComp() const;
		dae::SpriteAnimationComponent* GetAnimationComp() const;
		dae::GameObject* GetGameObject() const;
		glm::ivec2 PickBestDirection();
		StateContext<PookaComponent>& GetStateMachine() { return m_StateMachine; };

		void SnapToNearestDugTile(const glm::vec2& pos);
		bool IsBeingHit() const;
		bool IsPookaHittingPlayer() const;



		Subject m_Subject;
		void PookaNotifyEnemyDied();
		void PookaNotifyPlayerDied();
		void RestartSpawnPoint();
	private:
		// Inherited via Component
		void FixedUpdate(const float fixedTimeStep) override;
		void Update(float elapsedSec) override;
		void Render() const override;

		Level* m_pLevel;
		dae::SpriteAnimationComponent* m_AnimationComponent;
		PlayerComponent* m_pPlayer;
		PlayerComponent* m_pPlayerTwo;

		glm::ivec2 m_CurrentTile;
		glm::ivec2 m_TargetTile;
		glm::ivec2 m_CurrentDirection;
		float m_Speed;
		StateContext<PookaComponent> m_StateMachine;
		glm::vec2 m_CurrentWorldPos;

		dae::GameObject* m_pGameObject;

		glm::vec2 m_SavedSpawnPoint;
	};
}
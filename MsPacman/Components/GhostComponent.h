#pragma once
#include "Component.h"
#include <glm/glm.hpp>
#include "../../Engine/State/StateMachine.h"

namespace dae
{
	class Level;
	class PlayerComponent;


	enum class GhostType
	{
		Blinky,
		Pinky,
		Inky,
		Sue
	};


	class GhostComponent :public Component
	{
	public:
		GhostComponent(GameObject* owner, Level* level, PlayerComponent* player, GhostType type, glm::vec2 startWorldPos);
		~GhostComponent() = default;

		void MoveTowardTargetTile(float deltaTime);
		void SetChaseTarget(glm::ivec2 tile);
		glm::ivec2 GetCurrentTile() const;
		glm::ivec2 GetCurrentDirection() const;
		Level* GetLevel() const;
		PlayerComponent* GetPlayerComp() const;
		GhostType GetGhostType() const;
		//void SetTextureAnim();
		bool HasExitedHouse()const;

	private:
		glm::ivec2 PickBestDirection();
		// Inherited via Component
		void FixedUpdate(const float fixedTimeStep) override;
		void Update(float elapsedSec) override;
		void Render() const override;

		Level* m_pLevel;
		PlayerComponent* m_pPlayer;
		GhostType m_Type;
		glm::ivec2 m_CurrentTile;
		glm::ivec2 m_ChaseTargetTile;
		glm::ivec2 m_CurrentDirection;
		float m_Speed;
		StateContext<GhostComponent> m_StateMachine;
		bool m_HasExitedHouse;

	};
}
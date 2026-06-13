#pragma once
#include "Component.h"
#include <glm/glm.hpp>

namespace dae
{
	class Level;
	class PlayerComponent :public Component
	{
	public:
		PlayerComponent(GameObject* owner, Level* level);

		void SetDesiredDirection(const glm::vec2& direction);
		void MoveTowardTargetTile(const glm::vec2& currPos, const glm::vec2& targetPos, float deltaTime);
		void CheckTilePickUp();
		glm::ivec2 GetCurrentTile();

	private:


		dae::Level* m_pLevel;
		glm::ivec2 m_TargetTile;
		glm::vec2 m_CurrentDirection;
		glm::vec2 m_DesiredDirection;
		float m_Speed;

		// Inherited via Component
		void FixedUpdate(const float fixedTimeStep) override;

		void Update(float elapsedSec) override;

		void Render() const override;

	};

}

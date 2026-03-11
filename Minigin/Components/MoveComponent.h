#pragma once
#include "Components/Component.h"
#include <glm/vec2.hpp>


namespace dae
{
	class GameObject;
	class MoveComponent :public Component
	{
	public:
		MoveComponent(GameObject* owner, float speed);
		void Move(const glm::vec2& direction, float deltaTime);

	private:
		// Inherited via Component
		void FixedUpdate(const float fixedTimeStep) override;
		void Update(float elapsedSec) override;
		void Render() const override;

		GameObject* m_pGameObject;
		float m_Speed;
	};

}


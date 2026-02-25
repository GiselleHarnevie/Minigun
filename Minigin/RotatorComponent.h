#pragma once
#include "Component.h"

namespace dae
{
	class RotatorComponent : public Component
	{
	public:
		RotatorComponent(GameObject* gameObject, float speed, float radius);
		virtual ~RotatorComponent() = default;

		void Update(float elapsedSec) override;
		void FixedUpdate(const float fixedTimeStep) override;
	private:
		float m_RotSpeed;
		float m_Radius;
		float m_Angle;
		float m_tempPi;

		// Inherited via Component
		void Render() const override;
	};
}


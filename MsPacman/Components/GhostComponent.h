#pragma once
#include "Component.h"

namespace dae
{
	class GhostComponent :public Component
	{
	public:
		GhostComponent(GameObject* owner);
		~GhostComponent() = default;

	private:


		// Inherited via Component
		void FixedUpdate(const float fixedTimeStep) override;

		void Update(float elapsedSec) override;

		void Render() const override;

		

	};
}
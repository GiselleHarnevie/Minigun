#pragma once
#include "Component.h"
#include <memory>
#include "Observer/Subject.h"

namespace dae
{
	class LivesComponent :public Component
	{
	public:
		LivesComponent(GameObject* owner, int livesAmount);

		void TakeLife();
		int GetLivesLeft() const;

		Subject m_Subject;
	private:
		// Inherited via Component
		void FixedUpdate(const float fixedTimeStep) override;
		void Update(float elapsedSec) override;
		void Render() const override;


		int m_CurrentLivesLeft;
		
	};

}
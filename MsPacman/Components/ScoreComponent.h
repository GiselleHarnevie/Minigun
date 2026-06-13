#pragma once
#include "Component.h"
#include "TextComponent.h"
#include "Observer/Subject.h"

namespace dae
{
	class ScoreComponent : public Component
	{
	public:
		ScoreComponent(GameObject* owner);

		void AddScore(int score);
		int GetScore() const;
		Subject m_Subject;
	private:
		// Inherited via Component
		void FixedUpdate(const float fixedTimeStep) override;
		void Update(float elapsedSec) override;
		void Render() const override;

		int m_CurrentScore;
	};
}


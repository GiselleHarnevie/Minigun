#pragma once
#include "Component.h"
#include "TextComponent.h"
#include "Observer/Subject.h"
#include "Observer/Observer.h"

namespace dae
{
	class ScoreComponent : public Component ,public Observer
	{
	public:
		ScoreComponent(GameObject* owner, int currentScore);

		void AddScore(int score);
		int GetScore() const;
		Subject m_Subject;


	private:
		// Inherited via Component
		void FixedUpdate(const float fixedTimeStep) override;
		void Update(float elapsedSec) override;
		void Render() const override;

		int m_CurrentScore;

		// Inherited via Observer
		void OnNotify(unsigned int event, GameObject* actor) override;
	};
}


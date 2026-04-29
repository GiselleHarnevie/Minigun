#pragma once
#include "Component.h"
#include "Observer/Observer.h"

namespace dae
{
	class TextComponent;
	class ScoreUIComponent :public Component ,public Observer
	{
	public:
		ScoreUIComponent(GameObject* owner);

		void InitScoreTextDisplay();

	private:
		TextComponent* m_pTextComponent;

		// Inherited via Component
		void FixedUpdate(const float fixedTimeStep) override;
		void Update(float elapsedSec) override;
		void Render() const override;

		// Inherited via Observer
		void OnNotify(unsigned int event, GameObject* actor) override;
	};
}
#pragma once
#include "TextComponent.h"
#include "Observer/Observer.h"


namespace dae
{
	class RoundUIComponent : public Component, public Observer
	{
	public:
		RoundUIComponent(GameObject* owner, int roundNumber);

	private:
		// Inherited via Component
		void FixedUpdate(const float fixedTimeStep) override;
		void Update(float elapsedSec) override;
		void Render() const override;

		// Inherited via Observer
		void OnNotify(unsigned int event, GameObject* actor) override;

		TextComponent* m_pTextComponent;
	};

}

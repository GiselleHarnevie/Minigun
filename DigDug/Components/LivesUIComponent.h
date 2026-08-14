#pragma once
#include "TextComponent.h"
#include "Observer/Observer.h"


namespace dae
{
	class LivesUIComponent : public Component, public Observer
	{
	public:
		LivesUIComponent(GameObject* owner);

		void InitLivesTextDisplay(int currentLivesLeft);
		
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

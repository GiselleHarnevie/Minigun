#pragma once
#include "Component.h"
#include "TextComponent.h"

namespace dae
{
	class FPSComponent :public Component
	{
	public:
		FPSComponent(GameObject* gameObject);
		virtual ~FPSComponent() = default;

		// Inherited via Component
		void Render() const override;
		void Update(float elapsedSec) override;
		void FixedUpdate(const float fixedTimeStep) override;

		int GetFPS() const;

	private:
		int m_FPS;
		float m_FPSTimer;
		TextComponent* textComponent;
		int m_FrameCount;



	};
}
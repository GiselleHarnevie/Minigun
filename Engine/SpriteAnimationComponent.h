#pragma once
#include "Component.h"
#include "GameObject.h"
#include <SDL3/SDL.h>

namespace dae
{


	class Texture2D;
	class SpriteAnimationComponent : public Component
	{
	public:
		SpriteAnimationComponent(GameObject* owner, const std::string& fullpath);

		SpriteAnimationComponent(GameObject* owner, const std::string& fullPath, int nrFrames, float animationSpeed);
		void Render() const override;

		void SetTexture(const std::string& fullPath);

		void SetFlipMode(SDL_FlipMode flipMode);

		void SetSpriteRotation(double rotation);
		double GetSpriteRotation() const;

		SDL_FlipMode GetFlipMode() const;

		void SetIsAnimated(bool isAnimated);

		SDL_FRect GetDstRect() const;

		void SetAnimation(const std::string& fullPath, int nrFrames, float animationSpeed);

	private:
		// Inherited via Component
		void FixedUpdate(const float fixedTimeStep) override;
		void Update(float elapsedSec) override;


		std::shared_ptr<Texture2D> m_Texture{};
		SDL_FRect m_SrcRect;
		SDL_FRect m_DstRect;
		SDL_FlipMode m_FlipMode{};
		double m_SpriteRotation{};

		bool m_IsAnimated;
		int m_NrFrames;
		float m_AnimationSpeed;

		float m_FrameTime;
		float m_AccumulatedTime;
		int m_CurrentFrame;

		//std::unordered_map<std::string, AnimationData> m_Animations;
	};
}

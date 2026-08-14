#include "SpriteAnimationComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Texture2D.h"
#include <iostream>


dae::SpriteAnimationComponent::SpriteAnimationComponent(GameObject* owner, const std::string& fullpath)
	: Component(owner),
	m_DstRect{},
	m_SrcRect{}
{
	SetTexture(fullpath);
}

dae::SpriteAnimationComponent::SpriteAnimationComponent(GameObject* owner, const std::string& fullPath, int nrFrames, float animationSpeed)
	: Component(owner),
	m_AccumulatedTime{},
	m_CurrentFrame{}
{
	SetTexture(fullPath);
	m_IsAnimated = true;
	m_NrFrames = nrFrames;
	m_AnimationSpeed = animationSpeed;

	auto textureSize = m_Texture->GetSize();
	float frameWidth = textureSize.x / m_NrFrames;

	m_DstRect = { 0,0, frameWidth * 2.f, textureSize.y * 2.f };
	m_SrcRect = { 0,0, frameWidth, textureSize.y };
	m_FrameTime = 1.f / m_AnimationSpeed;
}

void dae::SpriteAnimationComponent::FixedUpdate(const float)
{

}

void dae::SpriteAnimationComponent::Update(float deltaTime)
{
	if (m_IsAnimated)
	{
		m_AccumulatedTime += deltaTime;
		if (m_AccumulatedTime > m_FrameTime)
		{
			++m_CurrentFrame;
			m_CurrentFrame %= m_NrFrames;
			m_AccumulatedTime -= m_FrameTime;
		}

		m_SrcRect.x = m_SrcRect.w * m_CurrentFrame;
	}


	if (m_Texture)
	{
		const glm::vec3& pos = GetOwner()->GetWorldPosition();
		m_DstRect.x = pos.x - (m_DstRect.w / 2.f);
		m_DstRect.y = pos.y - (m_DstRect.h / 2.f);
	}
}



void dae::SpriteAnimationComponent::Render() const
{
	if (m_Texture)
	{
		Renderer::GetInstance().RenderTexture(*m_Texture, m_SrcRect, m_DstRect, m_SpriteRotation, m_FlipMode);
	}
}

void dae::SpriteAnimationComponent::SetTexture(const std::string& fullPath)
{
	//std::cout << "Set Texture: " + fullPath <<std::endl;
	m_Texture = { ResourceManager::GetInstance().LoadTexture(fullPath) };
}

void dae::SpriteAnimationComponent::SetFlipMode(SDL_FlipMode flipMode)
{
	m_FlipMode = flipMode;
}

void dae::SpriteAnimationComponent::SetSpriteRotation(double rotation)
{
	m_SpriteRotation = rotation;
}

double dae::SpriteAnimationComponent::GetSpriteRotation() const
{
	return m_SpriteRotation;
}

SDL_FlipMode dae::SpriteAnimationComponent::GetFlipMode() const
{
	return m_FlipMode;
}

void dae::SpriteAnimationComponent::SetIsAnimated(bool isAnimated)
{
	m_IsAnimated = isAnimated;

}

SDL_FRect dae::SpriteAnimationComponent::GetDstRect() const
{
	return m_DstRect;
}

void dae::SpriteAnimationComponent::SetAnimation(const std::string& fullPath, int nrFrames, float animationSpeed)
{
	SetTexture(fullPath);
	m_IsAnimated = true;
	m_NrFrames = nrFrames;
	m_AnimationSpeed = animationSpeed;
	m_FrameTime = 1.f / m_AnimationSpeed;
	m_CurrentFrame = 0;
	m_AccumulatedTime = 0.f;

	auto textureSize = m_Texture->GetSize();
	float frameWidth = textureSize.x / m_NrFrames;

	m_DstRect = { m_DstRect.x, m_DstRect.y, frameWidth * 2.f, textureSize.y * 2.f };
	m_SrcRect = { 0,0, frameWidth, textureSize.y };
}
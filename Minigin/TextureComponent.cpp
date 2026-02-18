#include "TextureComponent.h"
#include "ResourceManager.h"
#include "Texture2D.h"
#include "Renderer.h"
#include "GameObject.h"

dae::TextureComponent::TextureComponent(GameObject* gameObject, const std::string& fullpath)
	: Component(gameObject),
	m_Texture{ dae::ResourceManager::GetInstance().LoadTexture(fullpath) }
{
}

void dae::TextureComponent::Render() const
{
	if (m_Texture)
	{
		const auto& pos = GetOwner()->GetPosition();
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	}
}

void dae::TextureComponent::SetTexture(const std::string& filename)
{
	m_Texture = dae::ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::TextureComponent::FixedUpdate(const float /*fixedTimeStep*/)
{
}

void dae::TextureComponent::Update(float /*elapsedSec*/)
{
}

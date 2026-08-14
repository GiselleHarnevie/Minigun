#include "TextureComponent.h"
#include "Texture2D.h"
#include "Renderer.h"
#include "GameObject.h"
#include "ResourceManager.h"

dae::TextureComponent::TextureComponent(GameObject* gameObject, const std::string& fullpath)
	: Component(gameObject),
	m_Texture{ dae::ResourceManager::GetInstance().LoadTexture(fullpath) }
{
	m_Width = m_Texture->GetSize().x;
	m_Height = m_Texture->GetSize().y;
}

dae::TextureComponent::TextureComponent(GameObject* owner, const std::string& fullpath, float multiplier)
	: Component(owner),
	m_Texture{ dae::ResourceManager::GetInstance().LoadTexture(fullpath) }
{
	m_Width = m_Texture->GetSize().x * multiplier;
	m_Height = m_Texture->GetSize().y * multiplier;
}

void dae::TextureComponent::Render() const
{
	if (m_Texture)
	{
		const auto& pos = GetOwner()->GetWorldPosition();
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y, m_Width, m_Height);

	}
}

void dae::TextureComponent::SetTexture(const std::string& filename)
{
	m_Texture = dae::ResourceManager::GetInstance().LoadTexture(filename);
}

//void dae::TextureComponent::SetTexture(const std::string& filename, float x,float y)
//{
//	m_Texture = dae::ResourceManager::GetInstance().LoadTexture(filename);
//
//}

void dae::TextureComponent::FixedUpdate(const float )
{
}

void dae::TextureComponent::Update(float)
{
}

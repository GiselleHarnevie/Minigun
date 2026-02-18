#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update(float /*deltaTime*/)
{

}

void dae::GameObject::FixedUpdate(float /*fixedTimeStep*/)
{

}

void dae::GameObject::Render() const
{
	for (auto& component : m_Components)
	{
		component->Render();
	}
}

void dae::GameObject::SetTexture(const std::string& filename)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::GameObject::SetPosition(float x, float y)
{
	if (m_pTransform)m_pTransform->SetPosition(x, y, 0.0f);
}

const glm::vec3& dae::GameObject::GetPosition() const
{
	if (m_pTransform) return m_pTransform->GetPosition();

	static glm::vec3 zero{};
	return zero;
}

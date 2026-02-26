#pragma once
#include <string>
#include <memory>
#include <vector>
#include <typeindex>
#include <type_traits>
#include "Components/TransformComponent.h"
#include "Components/Component.h"
#include <algorithm>

namespace dae
{
	class GameObject final
	{
	public:
		GameObject();
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void FixedUpdate(float fixedTimeStep);
		void Update(float deltaTime);
		void Render() const;

		//Component functions
		template<typename T, typename ...Args>
		requires std::is_base_of_v<Component, T>
		T& AddComponent(Args&&... args)
		{
			auto component = std::make_unique<T>(this, std::forward<Args>(args)...);
			T& ref = *component;
			m_Components.emplace_back(std::move(component));
			return ref;
		}

		template<typename T>
		T* GetComponent()
		{
			for (auto& component : m_Components)
			{
				auto t = dynamic_cast<T*>(component.get());
				if (t)
				{
					return t;
				}
			}

			return nullptr;
		}

		//todo: remove component and check whether component has been added

		//w2
		void SetParent(dae::GameObject* parent, bool keepWorldPosition);
		GameObject* GetParent();
		int GetChildCount();
		GameObject* GetChildAt(unsigned int index);
		bool IsChild(GameObject* potentialChild) const;

		TransformComponent& GetTransform();
		const glm::vec3& GetWorldPosition();
		void SetLocalPosition(const glm::vec3& pos);
		const glm::vec3& GetLocalPosition();
		void SetPositionDirty();

	private:
		std::vector<std::unique_ptr<Component>> m_Components;
		TransformComponent* m_pTransform = nullptr;

		//w2
		void UpdateWorldPosition();
		void AddChild(GameObject* child);
		void RemoveChild(GameObject* child);

		GameObject* m_pParent;
		std::vector <GameObject*> m_pChildren;

		glm::vec3 m_WorldPosition{};
		glm::vec3 m_LocalPosition{};
		bool m_PositionIsDirty{};
	};
}

#pragma once
#include <string>
#include <memory>
#include <vector>
#include "Transform.h"
#include "Component.h"
#include <algorithm>

namespace dae
{
	class Texture2D;
	class GameObject final
	{
	public:
		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		virtual void FixedUpdate(float fixedTimeStep);
		virtual void Update(float deltaTime);
		virtual void Render() const;

		void SetTexture(const std::string& filename);

		void SetPosition(float x, float y);
		const glm::vec3& GetPosition() const;

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

	private:
		std::vector<std::unique_ptr<Component>> m_Components;


		Transform* m_pTransform = nullptr;
		std::shared_ptr<Texture2D> m_texture{};

	};
}

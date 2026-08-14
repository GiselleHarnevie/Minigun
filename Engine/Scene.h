#pragma once
#include <memory>
#include <string>
#include <vector>
#include "GameObject.h"

namespace dae
{
	class Scene final
	{
	public:
		void Add(std::unique_ptr<GameObject> object);
		void Remove(const GameObject& object);
		void RemoveMarkedForDelete();
		void RemoveAll();

		void Update(float deltaTime);
		void FixedUpdate(float fixedTimeStep);
		void Render() const;

		~Scene() = default;
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		void SetPostUpdateCallback(std::function<void()> callback) { m_PostUpdateCallback = std::move(callback); }
	private:
		friend class SceneManager;
		explicit Scene() = default;

		std::vector < std::unique_ptr<GameObject>> m_objects{};
		std::function<void()> m_PostUpdateCallback;
	};

}

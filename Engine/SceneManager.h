#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Scene.h"
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);
		Scene* GetScene(const std::string& name);


		void Update(float deltaTime);
		void FixedUpdate(float fixedTimeStep);
		void Render();
		void SetActiveScene(int index);
		void SetActiveScene(const std::string& name);
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::unique_ptr<Scene>> m_scenes{};
		int m_activeSceneIndex{ 0 };

		std::unordered_map<std::string, Scene*> m_AllScenes;
	};
}

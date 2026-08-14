#include "SceneManager.h"
#include "Scene.h"
#include <iostream>

void dae::SceneManager::Update(float deltaTime)
{
	if (m_activeSceneIndex < static_cast<int>(m_scenes.size()))
		m_scenes[m_activeSceneIndex]->Update(deltaTime);
}

void dae::SceneManager::FixedUpdate(float fixedTimeStep)
{
	if (m_activeSceneIndex < static_cast<int>(m_scenes.size()))
		m_scenes[m_activeSceneIndex]->FixedUpdate(fixedTimeStep);
}

void dae::SceneManager::Render()
{
	if (m_activeSceneIndex < static_cast<int>(m_scenes.size()))
		m_scenes[m_activeSceneIndex]->Render();
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	m_scenes.emplace_back(new Scene());

	m_AllScenes[name] = m_scenes.back().get();

	return *m_scenes.back();
}

dae::Scene* dae::SceneManager::GetScene(const std::string& name)
{
	auto it = m_AllScenes.find(name);

	if (it != m_AllScenes.end())
		return it->second;
	return nullptr;
}

void dae::SceneManager::SetActiveScene(int index)
{
	if (index >= 0 && index < static_cast<int>(m_scenes.size()))
		m_activeSceneIndex = index;
}

void dae::SceneManager::SetActiveScene(const std::string& name)
{
	auto it = m_AllScenes.find(name);
	
	for (int i = 0; i < m_scenes.size(); i++)
	{
		if (m_scenes[i].get() == it->second)
		{
			std::cout << "Active Scene: " + name << std::endl;
			m_activeSceneIndex = i;
		}
	}
}
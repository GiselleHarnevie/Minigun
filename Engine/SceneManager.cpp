#include "SceneManager.h"
#include "SceneManager.h"
#include "Scene.h"

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

dae::Scene& dae::SceneManager::CreateScene()
{
	m_scenes.emplace_back(new Scene());
	return *m_scenes.back();
}

void dae::SceneManager::SetActiveScene(int index)
{
	if (index >= 0 && index < static_cast<int>(m_scenes.size()))
		m_activeSceneIndex = index;
}
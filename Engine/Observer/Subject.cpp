#include "Subject.h"
#include "Observer.h"
#include "../GameObject.h"

void dae::Subject::NotifyObservers(unsigned int event, GameObject* actor)
{
	for (auto& observer : m_Observers)
	{
		observer->OnNotify(event, actor);
	}
}

void dae::Subject::AddObserver(Observer* observer)
{
	m_Observers.emplace_back(observer);
}

void dae::Subject::RemoveObserver(Observer* observer)
{
	std::erase_if(m_Observers, [observer](Observer* i){ return i == observer; });
}

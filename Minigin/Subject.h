#pragma once
#include <vector>

namespace dae
{
	class Observer;
	class GameObject;
	class Subject
	{
	public:
		//notify observers
		void NotifyObservers(unsigned int event, GameObject* actor);

		//register and unregister observer
		void AddObserver(Observer* observer);
		void RemoveObserver(Observer* observer);

	private:
		//observers list
		std::vector<Observer*> m_Observers;
	};
}
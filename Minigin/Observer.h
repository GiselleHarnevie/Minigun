#pragma once


namespace dae
{
	class GameObject;
	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void OnNotify(unsigned int event, GameObject* actor) = 0;
	};
}
//uhh if i dont want a double inheritance when inheriting observer, what do i do instead?
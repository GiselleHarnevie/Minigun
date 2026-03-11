#pragma once

namespace dae
{
	class GameObject;
	class Command
	{
	public:
		virtual ~Command() = default;
		virtual void Execute(float deltaTime) = 0;

	private:

	};

}
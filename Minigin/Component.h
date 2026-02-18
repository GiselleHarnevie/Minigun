#pragma once

namespace dae {

	class GameObject;
	class Component
	{
	public:
		virtual ~Component() = default;
		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;

		virtual void FixedUpdate(const float fixedTimeStep) = 0;
		virtual void Update(float elapsedSec) = 0;
		virtual void Render() const = 0;

		void Destroy();
		bool IsDestroyed() const;
		


	protected:
		explicit Component(GameObject* pOwner);
		GameObject* GetOwner() const;

	private:
		GameObject* m_pOwner;
		bool m_IsDestroyed;
	};
}
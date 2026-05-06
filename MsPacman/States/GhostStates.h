#pragma once
#include "../Components/GhostComponent.h"
#include "../Engine/State/StateMachine.h"

namespace dae
{
	class GhostChaseState final :public State<GhostComponent>
	{
	public:
		GhostChaseState();
		~GhostChaseState();

	private:
		// Inherited via State
		void OnEnter(GhostComponent& owner) override;

		void OnExit(GhostComponent& owner) override;

		void Update(GhostComponent& owner, float deltaTime) override;

		void FixedUpdate(GhostComponent& owner, float deltaTime) override;

	};

	class GhostFrightenedState final :public State<GhostComponent>
	{
	public:
		GhostFrightenedState();
		~GhostFrightenedState();

	private:
		// Inherited via State
		void OnEnter(GhostComponent& owner) override;

		void OnExit(GhostComponent& owner) override;

		void Update(GhostComponent& owner, float deltaTime) override;

		void FixedUpdate(GhostComponent& owner, float deltaTime) override;

	};

	class GhostEatenState final :public State<GhostComponent>
	{
	public:
		GhostEatenState();
		~GhostEatenState();

	private:
		// Inherited via State
		void OnEnter(GhostComponent& owner) override;

		void OnExit(GhostComponent& owner) override;

		void Update(GhostComponent& owner, float deltaTime) override;

		void FixedUpdate(GhostComponent& owner, float deltaTime) override;

	};
}
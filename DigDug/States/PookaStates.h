#pragma once
#include "../Components/PookaComponent.h"
#include "../Engine/State/StateMachine.h"

//PookaWander standard, moves through dug stuff idly
//PookaChase
//PookaGhost/Eyeball stops at first tunnel
//Inflating State
//Popped/Dead State
//CrushedState

namespace dae
{
	class PookaNormalState final :public State<PookaComponent>
	{
	public:
		PookaNormalState();
		~PookaNormalState();
	private:
		// Inherited via State
		void OnEnter(PookaComponent& owner) override;
		void OnExit(PookaComponent& owner) override;
		void Update(PookaComponent& owner, float deltaTime) override;
		void FixedUpdate(PookaComponent& owner, float deltaTime) override;

		float m_NormalStateTimer = 0.f;
		float m_MaxNormalTimer = 4.f;
		
	};

	class PookaChaseState final :public State<PookaComponent>
	{
	public:
		PookaChaseState();
		~PookaChaseState();
	private:
		// Inherited via State
		void OnEnter(PookaComponent& owner) override;
		void OnExit(PookaComponent& owner) override;
		void Update(PookaComponent& owner, float deltaTime) override;
		void FixedUpdate(PookaComponent& owner, float deltaTime) override;

		float m_ChaseStateTimer = 0.f;
		float m_MaxChaseTimer = 6.f;
	};

	class PookaGhostState final :public State<PookaComponent>
	{
	public:
		PookaGhostState();
		~PookaGhostState();
	private:
		// Inherited via State
		void OnEnter(PookaComponent& owner) override;
		void OnExit(PookaComponent& owner) override;
		void Update(PookaComponent& owner, float deltaTime) override;
		void FixedUpdate(PookaComponent& owner, float deltaTime) override;

		float m_GhostTimer = 0.f;
		float m_MinimumGhostnvulnerability = 3.f;

	};

	class PookaInflatingState final :public State<PookaComponent>
	{
	public:
		PookaInflatingState();
		~PookaInflatingState();
	private:
		// Inherited via State
		void OnEnter(PookaComponent& owner) override;
		void OnExit(PookaComponent& owner) override;
		void Update(PookaComponent& owner, float deltaTime) override;
		void FixedUpdate(PookaComponent& owner, float deltaTime) override;

		//attack
		float m_InflatingTimer = 0.f;
		//float m_MaxInflatingTimer = 0.4f;

		//go back to normal
		float m_HitCountTimer = 0.f;
		float m_MaxGoBackToNormalTimer = 2.5f;

		float m_PookaHitsToPop = 2.f;
		//float m_PookaDeflateTime = 1.5f;
	
	};

	class PookaBlownUpState final :public State<PookaComponent>
	{
	public:
		PookaBlownUpState();
		~PookaBlownUpState();
	private:
		// Inherited via State
		void OnEnter(PookaComponent& owner) override;
		void OnExit(PookaComponent& owner) override;
		void Update(PookaComponent& owner, float deltaTime) override;
		void FixedUpdate(PookaComponent& owner, float deltaTime) override;

		float m_DeathTimer{0.f};
		float m_DeathAnimTime{ 0.5f };
	};

	class PookaCrushedState final :public State<PookaComponent>
	{
	public:
		PookaCrushedState();
		~PookaCrushedState();
	private:
		// Inherited via State
		void OnEnter(PookaComponent& owner) override;
		void OnExit(PookaComponent& owner) override;
		void Update(PookaComponent& owner, float deltaTime) override;
		void FixedUpdate(PookaComponent& owner, float deltaTime) override;
	};
}
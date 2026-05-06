#pragma once
#include <memory>

namespace dae
{
	template<typename Owner>
	class State
	{
	public:
		State() {};
		virtual ~State() = default;

		virtual void OnEnter(Owner& owner) = 0;
		virtual void OnExit(Owner& owner) = 0;

		virtual void Update(Owner& owner, float deltaTime) = 0;
		virtual void FixedUpdate(Owner& owner, float deltaTime) = 0;
	};

	template<typename Owner>
	class StateContext final
	{
	public:
		StateContext(Owner& owner)
			: m_Owner{owner}
		{

		}
		~StateContext() = default;


		//
		const State<Owner>* GetCurrentState() const
		{ 
			return m_pCurrentState.get(); 
		};

		void ChangeState(std::unique_ptr<State<Owner>> newState)
		{
			if (m_pCurrentState)
				m_pCurrentState->OnExit(m_Owner);

			m_pCurrentState = std::move(newState);

			if (m_pCurrentState)
				m_pCurrentState->OnEnter(m_Owner);
		};

		//
		void Update(float deltaTime)
		{
			if (m_pCurrentState)
				m_pCurrentState->Update(m_Owner, deltaTime);
		}
		void FixedUpdate(float deltaTime)
		{
			if (m_pCurrentState)
				m_pCurrentState->FixedUpdate(m_Owner, deltaTime);
		}
	private:
		Owner& m_Owner;
		std::unique_ptr<State<Owner>> m_pCurrentState;
	};
}
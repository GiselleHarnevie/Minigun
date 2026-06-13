#include "GhostStates.h"
#include "../Components/GhostComponent.h"
#include "../Components/PlayerComponent.h"
#include "GameSettings.h"

dae::GhostChaseState::GhostChaseState()
{

}

dae::GhostChaseState::~GhostChaseState()
{

}

void dae::GhostChaseState::OnEnter(GhostComponent&)
{

}

void dae::GhostChaseState::OnExit(GhostComponent&)
{

}

void dae::GhostChaseState::Update(GhostComponent& owner, float deltaTime)
{
	if (owner.HasExitedHouse() == false)
	{
		owner.SetChaseTarget(dae::GHOST_HOUSE_DOOR);
	}
	else {

	owner.SetChaseTarget(owner.GetPlayerComp()->GetCurrentTile());
	}
	owner.MoveTowardTargetTile(deltaTime);
}

void dae::GhostChaseState::FixedUpdate(GhostComponent&, float)
{

}

dae::GhostFrightenedState::GhostFrightenedState()
{

}

dae::GhostFrightenedState::~GhostFrightenedState()
{

}

void dae::GhostFrightenedState::OnEnter(GhostComponent&)
{

}

void dae::GhostFrightenedState::OnExit(GhostComponent&)
{

}

void dae::GhostFrightenedState::Update(GhostComponent&, float)
{
}

void dae::GhostFrightenedState::FixedUpdate(GhostComponent&, float)
{

}

dae::GhostEatenState::GhostEatenState()
{

}

dae::GhostEatenState::~GhostEatenState()
{

}

void dae::GhostEatenState::OnEnter(GhostComponent&)
{

}

void dae::GhostEatenState::OnExit(GhostComponent&)
{

}

void dae::GhostEatenState::Update(GhostComponent&, float)
{

}

void dae::GhostEatenState::FixedUpdate(GhostComponent&, float)
{

}

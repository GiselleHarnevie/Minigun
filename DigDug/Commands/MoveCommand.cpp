#include "MoveCommand.h"
#include "GameObject.h"
#include "Components/PlayerComponent.h"
#include "GameSettings.h"



dae::MoveCommand::MoveCommand(GameObject* gameObject, const glm::vec2& direction, SDL_FlipMode flipMode, double spriteRotation)
	:m_pGameObject{ gameObject },
	m_Direction{ direction },
	m_FlipMode{ flipMode },
	m_SpriteRotation{ spriteRotation }
	//m_Speed{speed}
{

}

void dae::MoveCommand::Execute(float )
{
	m_pGameObject->GetComponent<PlayerComponent>()->SetDesiredDirection(m_Direction, m_FlipMode, m_SpriteRotation);

	/*auto currentPos = m_pGameObject->GetLocalPosition();
	m_pGameObject->SetLocalPosition(
		glm::vec3{ currentPos.x + (m_Direction.x * dae::PLAYER_VELOCITY * deltaTime),
		currentPos.y + (m_Direction.y * dae::PLAYER_VELOCITY * deltaTime),
		currentPos.z
		});*/
}
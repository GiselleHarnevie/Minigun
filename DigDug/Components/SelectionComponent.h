#pragma once
#include "Component.h"
//#include "Observer/Subject.h"
#include "GameSettings.h"
#include <vector>

namespace dae
{
	class TextureComponent;

	class ConfirmSelectionCommand;
	class MoveArrowCommand;

	class SelectionComponent : public Component
	{
	public:
		SelectionComponent(GameObject* owner);

		void GetArrowDirection(const glm::vec2& direction);
		GameMode GetSelectedMode() const;
	private:
		// Inherited via Component
		void FixedUpdate(const float fixedTimeStep) override;
		void Update(float elapsedSec) override;
		void Render() const override;

		dae::TextureComponent* m_TextureComponent;
		glm::vec2 m_Direction;
		int m_SelectedIndex;

		std::vector<glm::vec2> m_ArrowPositions;

		MoveArrowCommand* m_pMoveArrowUp;
		MoveArrowCommand* m_pMoveArrowDown;
		ConfirmSelectionCommand* m_pConfirmSelection;

		float m_OffsetArrow;
	};

}
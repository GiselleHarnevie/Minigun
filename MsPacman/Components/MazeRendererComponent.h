#include "Component.h"
#include <memory>

namespace dae
{
	struct Pellet
	{
		//pellet rect, pellet position, pellet colour

	};

	class Level;
	class MazeRendererComponent : public Component
	{
	public:
		MazeRendererComponent(GameObject* owner, Level* currentLevel);
		~MazeRendererComponent() = default;

	private:
		// Inherited via Component
		void FixedUpdate(const float fixedTimeStep) override;

		void Update(float elapsedSec) override;

		void Render() const override;

		void DrawPellet();
		//void DrawPowerPellet();

		Level* m_CurrentLevel;
	};
}
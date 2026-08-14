#include "Component.h"
#include <memory>
#include <vector>

namespace dae
{

	class Level;
	class Texture2D;
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

		Level* m_CurrentLevel;

		std::shared_ptr<Texture2D> m_PlayfieldTextures[9];
	};
}
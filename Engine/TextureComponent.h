#pragma once
#include <memory>
#include <string>
#include "Component.h"

namespace dae
{
	class Texture2D;
	class TextureComponent :public Component
	{
	public:
		TextureComponent(GameObject* gameObject, const std::string& fullpath);
		TextureComponent(GameObject* owner, const std::string& fullpath, float multiplier);
		~TextureComponent() = default;

		void Render() const override;
		void SetTexture(const std::string& filename);
		//void SetTexture(const std::string& filename, float x, float y);
	private:
		std::shared_ptr<Texture2D> m_Texture{};

		// Inherited via Component
		void FixedUpdate(const float fixedTimeStep) override;
		void Update(float elapsedSec) override;

		float m_Width{};
		float m_Height{};
		//glm::vec2 m_Pos{};
	};

}
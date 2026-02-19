#pragma once
#include "Component.h"
#include "GameObject.h"
#include <memory>
#include <SDL3/SDL_pixels.h>
#include <string>

namespace dae
{
	class Font;
	class Texture2D;
	class TextComponent : public Component
	{
	public:
		TextComponent(GameObject* gameObject, const std::string& text, std::shared_ptr<Font> font, const SDL_Color& color);
		virtual ~TextComponent() = default;

		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

		void Render() const override;
		void SetText(const std::string& text);
		void SetPosition(float x, float y);
		void SetColor(const SDL_Color& color);

	private:
		// Inherited via Component
		void FixedUpdate(const float fixedTimeStep) override;
		void Update(float elapsedSec) override;

		bool m_needsUpdate{};
		std::string m_text{};
		SDL_Color m_color{ 255, 255, 255, 255 };
		TransformComponent* m_pTransform = nullptr;
		std::shared_ptr<Font> m_font{};
		std::shared_ptr<Texture2D> m_textTexture{};
	};

}
#pragma once

#include <glm/vec2.hpp>
#include <memory>

#include "IGameObject.h"
#include "../../Renderer/SpriteAnimator.h"

namespace RenderEngine {
	class Sprite;
}

class Tank : public IGameObject {
public:

	enum class EOrientation {
		Top,
		Bottom,
		Left,
		Right
	};

	//конструктор
	Tank(const float velocity, 
		 const glm::vec2 position, 
		 const glm::vec2& size);

	//для отрисовки
	void render() const override;

	//установка ориетации(направления) танка
	void setOrientation(const EOrientation eOrientation);

	//движение танка
	void move(const bool move);

	//для анимации спрайта
	void update(const uint64_t delta) override;

private:
	EOrientation m_eOrientation;
	//переменные самого спрайта в класе
	std::shared_ptr<RenderEngine::Sprite> m_pSprite_top;
	std::shared_ptr<RenderEngine::Sprite> m_pSprite_bottom;
	std::shared_ptr<RenderEngine::Sprite> m_pSprite_left;
	std::shared_ptr<RenderEngine::Sprite> m_pSprite_right;
	//4 аниматора для анимации спрайта для каждого состояния танка
	RenderEngine::SpriteAnimator m_spriteAnimatop_top;
	RenderEngine::SpriteAnimator m_spriteAnimatop_bottom;
	RenderEngine::SpriteAnimator m_spriteAnimatop_left;
	RenderEngine::SpriteAnimator m_spriteAnimatop_right;

	//переменная подтверждения движения
	bool m_move;
	//скорость
	float m_velocity;	
	//переменная для хранения направдения движения танка
	glm::vec2 m_moveOffset;
};
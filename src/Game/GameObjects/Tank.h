#pragma once

#include <glm/vec2.hpp>
#include <memory>

#include "IGameObject.h"

namespace RenderEngine {
	class AnimatedSprite;
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
	Tank(std::shared_ptr<RenderEngine::AnimatedSprite> pSprite, 
		const float velocity, 
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
	//переменная самого спрайта в класе
	std::shared_ptr<RenderEngine::AnimatedSprite> m_pSprite;
	//переменная подтверждения движения
	bool m_move;
	//скорость
	float m_velocity;	
	//переменная для хранения направдения движения танка
	glm::vec2 m_moveOffset;
};
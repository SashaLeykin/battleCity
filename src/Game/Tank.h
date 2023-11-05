#pragma once

#include <glm/vec2.hpp>

#include <memory>

namespace RenderEngine {
	class AnimatedSprite;
}

class Tank {
public:

	enum class EOrientation {
		Top,
		Botton,
		Left,
		Right
	};

	//конструктор
	Tank(std::shared_ptr<RenderEngine::AnimatedSprite> pSprite, const float velocity, const glm::vec2 position);

	//для отрисовки
	void render() const;

	//установка ориетации(направления) танка
	void setOrientation(const EOrientation eOrientation);

	//движение танка
	void move(const bool move);
	//для анимации спрайта
	void update(const uint64_t delta);

private:
	EOrientation m_eOrientation;
	//переменная самого спрайта в класе
	std::shared_ptr<RenderEngine::AnimatedSprite> m_pSprite;
	//переменная подтверждения движения
	bool m_move;
	//скорость
	float m_velocity;
	//позиция
	glm::vec2 m_position;
	//переменная для хранения направдения движения танка
	glm::vec2 m_moveOffset;
};
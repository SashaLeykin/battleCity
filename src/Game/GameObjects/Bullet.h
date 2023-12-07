//#pragma once
#ifndef BULLET_H
#define BULLET_H

#include "IGameObject.h"

#include <array>
#include <memory>

namespace RenderEngine {
	class Sprite;
}

class Bullet : public IGameObject {
public:
	enum class EOrientation : uint8_t {
		Top,
		Bottom,
		Left,
		Right
	};

	Bullet(const double velocity, const glm::vec2& position, const glm::vec2& size, const float layer);
	virtual void render() const override;
	bool isActive() const { return m_isActive; }
	void fire(const glm::vec2& position, const glm::vec2& direction);
	//столкновение
	virtual void onCollision() override;

private:
	//переменные направления пули
	std::shared_ptr<RenderEngine::Sprite> m_pSprite_top;
	std::shared_ptr<RenderEngine::Sprite> m_pSprite_bottom;
	std::shared_ptr<RenderEngine::Sprite> m_pSprite_left;
	std::shared_ptr<RenderEngine::Sprite> m_pSprite_right;
	EOrientation m_eOrientation;

	//скорость пули
	double m_maxVelocity;

	//активна ли выпущенная пуля?
	bool m_isActive;

};

#endif // !BULLET_H

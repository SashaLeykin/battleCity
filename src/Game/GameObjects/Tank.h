#pragma once

#include <glm/vec2.hpp>
#include <memory>

#include "IGameObject.h"
#include "../../Renderer/SpriteAnimator.h"
#include "../../System/Timer.h"

namespace RenderEngine {
	class Sprite;
}
class Bullet;

class Tank : public IGameObject {
public:

	enum class EOrientation {
		Top,
		Bottom,
		Left,
		Right
	};

	//конструктор
	Tank(const double maxVelocity, 
		 const glm::vec2 position, 
		 const glm::vec2& size, 
		 const float layer);

	//для отрисовки
	void render() const override;

	//установка ориетации(направления) танка
	void setOrientation(const EOrientation eOrientation);
	//для анимации спрайта
	void update(const double delta) override;
	//возвращение максимальной скорости
	double getMaxVelocity() const { return m_maxVelocity; }
	//переопределение функции для ограничения движения танка во время появления
	void setVelocity(const double velocity) override;
	//для стрельбы
	void fire();

private:
	EOrientation m_eOrientation;
	//для стрельбы указатель на пулю
	std::shared_ptr<Bullet> m_pCurrentBullet;
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
	//для анимации появления танка
	std::shared_ptr<RenderEngine::Sprite> m_pSprite_respawn;
	RenderEngine::SpriteAnimator m_spriteAnimatop_respawn;
	//для анимации  щита
	std::shared_ptr<RenderEngine::Sprite> m_pSprite_shield;
	RenderEngine::SpriteAnimator m_spriteAnimatop_shield;

	//подключение таймера
	Timer m_respawnTimer;
	Timer m_shieldTimer;
		
	//скорость
	double m_maxVelocity;	
	//переменная для хранения направдения движения танка
	//glm::vec2 m_moveOffset;
	//переменные для определения появления танка и имеет ли он щит
	bool m_isRespawning;
	bool m_hasShield;
};
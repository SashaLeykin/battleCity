#include "Tank.h"

#include "../../Resources/ResourcMenager.h"
#include "../../Renderer/Sprite.h"
#include "Bullet.h"
#include "../../Physics/PhysicsEngine.h"

Tank::Tank(const double maxVelocity,
		   const glm::vec2 position, 
		   const glm::vec2& size, 
		   const float layer)
	: IGameObject(position, size, 0.f, layer)
	, m_eOrientation(EOrientation::Top)
	, m_pCurrentBullet(std::make_shared<Bullet>(0.1, m_position + m_size / 4.f, m_size / 2.f, layer))
	, m_pSprite_top(ResourceMenager::getSprite("tankSprite_top"))
	, m_pSprite_bottom(ResourceMenager::getSprite("tankSprite_bottom"))
	, m_pSprite_left(ResourceMenager::getSprite("tankSprite_left"))
	, m_pSprite_right(ResourceMenager::getSprite("tankSprite_right"))
	, m_spriteAnimatop_top(m_pSprite_top)
	, m_spriteAnimatop_bottom(m_pSprite_bottom)
	, m_spriteAnimatop_left(m_pSprite_left)
	, m_spriteAnimatop_right(m_pSprite_right)
	, m_pSprite_respawn(ResourceMenager::getSprite("respawn"))
	, m_spriteAnimatop_respawn(m_pSprite_respawn)
	, m_pSprite_shield(ResourceMenager::getSprite("shield"))
	, m_spriteAnimatop_shield(m_pSprite_shield)
	
	, m_maxVelocity(maxVelocity)		
	, m_isRespawning(true)
	, m_hasShield(false)
{	
	//при установки таймера используем лямда функцию
	m_respawnTimer.setCallBack([&]()
		{
			m_isRespawning = false;
			m_hasShield = true;
			//запускаем таймер щита на 2 сек
			m_shieldTimer.start(2000);
		}
	);
	m_respawnTimer.start(1500);

	m_shieldTimer.setCallBack([&]()
		{
			m_hasShield = false;			
		}
	);
	//установка на танк коллайдера(прямоугольника)
	m_colliders.emplace_back(glm::vec2(0), m_size);
}

void Tank::setVelocity(const double velocity)
{
	if (!m_isRespawning)
	{
		m_velocity = velocity;
	}
}

void Tank::render() const
{
	//отрисовка появления танка и щита
	if (m_isRespawning)
	{
		m_pSprite_respawn->render(m_position, m_size, m_rotation, m_layer, m_spriteAnimatop_respawn.getCurrentFrame());
	}
	else
	{
		//отрисовка танка в зависимости от направления движения
		switch (m_eOrientation)
		{
		case Tank::EOrientation::Top:
			m_pSprite_top->render(m_position, m_size, m_rotation, m_layer, m_spriteAnimatop_top.getCurrentFrame());
			break;
		case Tank::EOrientation::Bottom:
			m_pSprite_bottom->render(m_position, m_size, m_rotation, m_layer, m_spriteAnimatop_bottom.getCurrentFrame());
			break;
		case Tank::EOrientation::Left:
			m_pSprite_left->render(m_position, m_size, m_rotation, m_layer, m_spriteAnimatop_left.getCurrentFrame());
			break;
		case Tank::EOrientation::Right:
			m_pSprite_right->render(m_position, m_size, m_rotation, m_layer, m_spriteAnimatop_right.getCurrentFrame());
			break;
		}

		if (m_hasShield)
		{
			m_pSprite_shield->render(m_position, m_size, m_rotation, m_layer , m_spriteAnimatop_shield.getCurrentFrame());
		}
	}	
	if (m_pCurrentBullet->isActive())
	{
		m_pCurrentBullet->render();
	}
}

void Tank::setOrientation(const EOrientation eOrientation)
{
	//проверка соответствует ли тякущая ориентация с заданной
	if (m_eOrientation == eOrientation)
	{
		return;
	}
	//если отличается то присваеваю
	m_eOrientation = eOrientation;

	switch (m_eOrientation)
	{
	case Tank::EOrientation::Top:		
		m_direction.x = 0.f;
		m_direction.y = 1.f;
		break;
	case Tank::EOrientation::Bottom:		
		m_direction.x = 0.f;
		m_direction.y = -1.f;
		break;
	case Tank::EOrientation::Left:		
		m_direction.x = -1.f;
		m_direction.y = 0.f;
		break;
	case Tank::EOrientation::Right:		
		m_direction.x = 1.f;
		m_direction.y = 0.f;
		break;
	default:
		break;
	}
}

void Tank::update(const double delta)
{
	if (m_isRespawning)
	{
		m_spriteAnimatop_respawn.apdate(delta);
		m_respawnTimer.update(delta);
	}
	else
	{
		//проверка есть ли щит
		if (m_hasShield)
		{
			m_spriteAnimatop_shield.apdate(delta);
			m_shieldTimer.update(delta);
		}

		if (m_velocity > 0)
		{
			switch (m_eOrientation)
			{
			case Tank::EOrientation::Top:
				m_spriteAnimatop_top.apdate(delta);
				break;
			case Tank::EOrientation::Bottom:
				m_spriteAnimatop_bottom.apdate(delta);
				break;
			case Tank::EOrientation::Left:
				m_spriteAnimatop_left.apdate(delta);
				break;
			case Tank::EOrientation::Right:
				m_spriteAnimatop_right.apdate(delta);
				break;
			}
		}
	}	
}

void Tank::fire()
{
	//if (!m_pCurrentBullet->isActive())
	{
		m_pCurrentBullet->fire(m_position + m_size / 4.f, m_direction);
		Physics::PhysicsEngine::addDynamicGameObject(m_pCurrentBullet);
	}
}

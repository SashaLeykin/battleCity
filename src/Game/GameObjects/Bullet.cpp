#include "Bullet.h"

#include "../../Resources/ResourcMenager.h"
#include "../../Renderer/Sprite.h"

Bullet::Bullet(const double velocity, const glm::vec2& position, const glm::vec2& size, const float layer)
	: IGameObject(position, size, 0.f, layer)
	, m_pSprite_top(ResourceMenager::getSprite("bullet_Top"))
	, m_pSprite_bottom(ResourceMenager::getSprite("bullet_Bottom"))
	, m_pSprite_left(ResourceMenager::getSprite("bullet_Left"))
	, m_pSprite_right(ResourceMenager::getSprite("bullet_Right"))
	, m_eOrientation(EOrientation::Top)
	, m_isActive(false)
{
	setVelocity(velocity);
	m_colliders.emplace_back(glm::vec2(0), m_size);
}

void Bullet::render() const
{
	switch (m_eOrientation)
	{
	case EOrientation::Top:
		m_pSprite_top->render(m_position, m_size, m_rotation, m_layer);
		break;
	case EOrientation::Bottom:
		m_pSprite_bottom->render(m_position, m_size, m_rotation, m_layer);
		break;
	case EOrientation::Left:
		m_pSprite_left->render(m_position, m_size, m_rotation, m_layer);
		break;
	case EOrientation::Right:
		m_pSprite_right->render(m_position, m_size, m_rotation, m_layer);
		break;	
	}
}

void Bullet::fire(const glm::vec2& position, const glm::vec2& direction)
{
	m_position = position;
	m_direction = direction; //направление

	if (m_direction.x == 0.f)
	{
		m_eOrientation = (m_direction.y < 0) ? EOrientation::Bottom : EOrientation::Top;
	}
	else
	{
		m_eOrientation = (m_direction.x < 0) ? EOrientation::Left : EOrientation::Right;
	}
	m_isActive = true;
}

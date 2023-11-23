#include "BrickWall.h"

#include "../../Resources/ResourcMenager.h"
#include "../../Renderer/Sprite.h"

BrickWall::BrickWall(const EBrickWallType eBrickWallType,
					 const glm::vec2& position, 
					 const glm::vec2& size, 
					 const float rotation,
					 const float layer)
	: IGameObject(position, size, rotation, layer)
	, m_eCurrentBrickState{ EBrickState::Destroyed,
		                    EBrickState::Destroyed,
		                    EBrickState::Destroyed,
		                    EBrickState::Destroyed }	
	, m_blockOffset  { glm::vec2(0, m_size.y / 2.f),
					   glm::vec2(m_size.x / 2.f, m_size.y / 2.f),
					   glm::vec2(0, 0),
					   glm::vec2(m_size.x / 2.f, 0) }
{
	m_sprites[static_cast<size_t>(EBrickState::All)]                 = ResourceMenager::getSprite("brickWall_All");
	m_sprites[static_cast<size_t>(EBrickState::TopLeft)]             = ResourceMenager::getSprite("brickWall_TopLeft");
	m_sprites[static_cast<size_t>(EBrickState::TopRight)]            = ResourceMenager::getSprite("brickWall_TopRight");
	m_sprites[static_cast<size_t>(EBrickState::Top)]                 = ResourceMenager::getSprite("brickWall_Top");
	m_sprites[static_cast<size_t>(EBrickState::BottomLeft)]          = ResourceMenager::getSprite("brickWall_BottomLeft");
	m_sprites[static_cast<size_t>(EBrickState::Left)]                = ResourceMenager::getSprite("brickWall_Left");
	m_sprites[static_cast<size_t>(EBrickState::TopRight_BottomLeft)] = ResourceMenager::getSprite("brickWall_TopRight_BottomLeft");
	m_sprites[static_cast<size_t>(EBrickState::Top_BottomLeft)]      = ResourceMenager::getSprite("brickWall_Top_BottomLeft");
	m_sprites[static_cast<size_t>(EBrickState::BottomRight)]          = ResourceMenager::getSprite("brickWall_BottomRight");
	m_sprites[static_cast<size_t>(EBrickState::TopLeft_BottomRight)] = ResourceMenager::getSprite("brickWall_TopLeft_BottomRight");
	m_sprites[static_cast<size_t>(EBrickState::Right)]               = ResourceMenager::getSprite("brickWall_Right");
	m_sprites[static_cast<size_t>(EBrickState::Top_BottomRight)]     = ResourceMenager::getSprite("brickWall_Top_BottomRight");
	m_sprites[static_cast<size_t>(EBrickState::Bottom)]              = ResourceMenager::getSprite("brickWall_Bottom");
	m_sprites[static_cast<size_t>(EBrickState::TopLeft_Bottom)]      = ResourceMenager::getSprite("brickWall_TopLeft_Bottom");
	m_sprites[static_cast<size_t>(EBrickState::TopRight_Bottom)]     = ResourceMenager::getSprite("brickWall_TopRight_Bottom");

	//в зависимости от типа стены
	switch (eBrickWallType)
	{
	case EBrickWallType::All:
		m_eCurrentBrickState.fill(EBrickState::All);
		break;
	case EBrickWallType::Top:
		m_eCurrentBrickState[static_cast<size_t>(EBrickLocation::TopLeft)]  = EBrickState::All;
		m_eCurrentBrickState[static_cast<size_t>(EBrickLocation::TopRight)] = EBrickState::All;
		break;
	case EBrickWallType::Bottom:
		m_eCurrentBrickState[static_cast<size_t>(EBrickLocation::BottomLeft)]  = EBrickState::All;
		m_eCurrentBrickState[static_cast<size_t>(EBrickLocation::BottomRight)] = EBrickState::All;
		break;
	case EBrickWallType::Left:
		m_eCurrentBrickState[static_cast<size_t>(EBrickLocation::TopLeft)]    = EBrickState::All;
		m_eCurrentBrickState[static_cast<size_t>(EBrickLocation::BottomLeft)] = EBrickState::All;
		break;
	case EBrickWallType::Right:
		m_eCurrentBrickState[static_cast<size_t>(EBrickLocation::TopRight)]    = EBrickState::All;
		m_eCurrentBrickState[static_cast<size_t>(EBrickLocation::BottomRight)] = EBrickState::All;
		break;
	case EBrickWallType::TopLeft:
		m_eCurrentBrickState[static_cast<size_t>(EBrickLocation::TopLeft)] = EBrickState::All;		
		break;
	case EBrickWallType::TopRight:
		m_eCurrentBrickState[static_cast<size_t>(EBrickLocation::TopRight)] = EBrickState::All;
		break;
	case EBrickWallType::BottomLeft:
		m_eCurrentBrickState[static_cast<size_t>(EBrickLocation::BottomLeft)] = EBrickState::All;		
		break;
	case EBrickWallType::BottomRight:		
		m_eCurrentBrickState[static_cast<size_t>(EBrickLocation::BottomRight)] = EBrickState::All;
		break;	
	}
}

void BrickWall::renderBrick(const EBrickLocation eBrickLocation) const
{	
	//создание переменной для определения статуса кирпича
	const EBrickState state = m_eCurrentBrickState[static_cast<size_t>(eBrickLocation)];
	if (state != EBrickState::Destroyed)
	{
		m_sprites[static_cast<size_t>(state)]->render(m_position + m_blockOffset[static_cast<size_t>(eBrickLocation)], m_size / 2.f, m_rotation, m_layer);
	}
}

void BrickWall::render() const
{
	renderBrick(EBrickLocation::TopLeft);
	renderBrick(EBrickLocation::TopRight);
	renderBrick(EBrickLocation::BottomLeft);
	renderBrick(EBrickLocation::BottomRight);	
}

void BrickWall::update(const double delta)
{
}

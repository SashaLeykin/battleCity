#include "Border.h"

#include "../../Resources/ResourcMenager.h"
#include "../../Renderer/Sprite.h"

Border::Border(const glm::vec2& position,
	                 const glm::vec2& size,  
	                 const float rotation,
					 const float layer)
	: IGameObject(position, size, rotation, layer)	
	, m_sprite(ResourceMenager::getSprite("border"))	
{	
}

void Border::render() const
{
	//m_layer - м_слой
	m_sprite->render(m_position, m_size, m_rotation, m_layer);
}

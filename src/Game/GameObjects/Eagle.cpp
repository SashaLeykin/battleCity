#include "Eagle.h"

#include "../../Resources/ResourcMenager.h"
#include "../../Renderer/Sprite.h"

Eagle::Eagle(const glm::vec2& position,
	                 const glm::vec2& size,  
	                 const float rotation,
					 const float layer)
	: IGameObject(position, size, rotation, layer)	
	, m_sprites{ ResourceMenager::getSprite("eagle"), 
	             ResourceMenager::getSprite("eagle_dead") }	
	, m_eCurrentState(EEagleState::Alive)	
{	
}

void Eagle::render() const
{
	m_sprites[static_cast<size_t>(m_eCurrentState)]->render(m_position, m_size, m_rotation, m_layer);
}

void Eagle::update(const double delta)
{

}



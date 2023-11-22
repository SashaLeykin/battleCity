#ifndef BORDER_H
#define BORDER_H

#include <memory>
#include <array>

#include "IGameObject.h"

namespace RenderEngine {
	class Sprite;
}
//� ����� Border - �������
class Border : public IGameObject { //�������
public:

	Border(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer);
	virtual void render() const override;
	
private:		
	//��� �������� ����� �������
	std::shared_ptr<RenderEngine::Sprite> m_sprite;	
};

#endif // !BORDER_H

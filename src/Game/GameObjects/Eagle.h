#ifndef EAGLE_H
#define EAGLE_H

//#include <glm/vec2.hpp>

#include <memory>
#include <array>

#include "IGameObject.h"
#include "../../Renderer/SpriteAnimator.h"

namespace RenderEngine {
	class Sprite;
}
//� ����� BrickWall - ��������� �����
class Eagle : public IGameObject {
public:
	//
	enum class EEagleState : uint8_t {
		Alive, //����� ����
		Dead
	};

	Eagle(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer);
	virtual void render() const override;

	//��� �������� �������
	void update(const double delta) override;
	
private:	
	//��� �������� ����� ��������� ����� �� 4 ��������� ������
	std::array<std::shared_ptr<RenderEngine::Sprite>, 2> m_sprites;
	//������� ��������� ����
	EEagleState m_eCurrentState;
};

#endif // !EAGLE_H

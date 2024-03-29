#ifndef WATER_H
#define WATER_H

//#include <glm/vec2.hpp>

#include <memory>
#include <array>

#include "IGameObject.h"
#include "../../Renderer/SpriteAnimator.h"

namespace RenderEngine {
	class Sprite;
}

class Water : public IGameObject {
public:
	//����� enum �� ��������� �������� �������������� � int, � ����� �� ���������� 
	// ������������� �� ������ ������������.	
	//��� ��������� ������� � enum class EBrickState
	enum class EBlockLocation : uint8_t {
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight
	};

	Water(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer);
	virtual void render() const override;

	//��� �������� �������
	void update(const double delta) override;

	virtual bool collides(const EObjectType objectType) override;
	
private:
	void renderBlock(const EBlockLocation eBlockLocation) const;	
	//��� �������� ����� ��������� ����� �� 4 ��������� ������
	std::shared_ptr<RenderEngine::Sprite> m_sprites;
	//��� �������� �������
	RenderEngine::SpriteAnimator m_spriteAnimator;
	//�������� ������� ��� �������� �������� 4 ����������� �������
	std::array<glm::vec2, 4> m_blockOffset;
};

#endif // !WATER_H

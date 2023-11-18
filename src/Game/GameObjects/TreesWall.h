#ifndef TREESWALL_H
#define TREESWALL_H

//#include <glm/vec2.hpp>

#include <memory>
#include <array>

#include "IGameObject.h"

namespace RenderEngine {
	class Sprite;
}
//� ����� BrickWall - ��������� �����
class TreesWall : public IGameObject {
public:
	//����� enum �� ��������� �������� �������������� � int, � ����� �� ���������� 
	// ������������� �� ������ ������������.	
	//��� ��������� ������� � enum class EBrickState
	enum class EBlockLocation {
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight
	};

	TreesWall(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer);
	virtual void render() const override;
	
private:
	void renderBlock(const EBlockLocation eBlockLocation) const;	
	//��� �������� ����� ��������� ����� �� 4 ��������� ������
	std::shared_ptr<RenderEngine::Sprite> m_sprites;
	//�������� ������� ��� �������� �������� 4 ����������� �������
	std::array<glm::vec2, 4> m_blockOffset;
};

#endif // !TREESWALL_H

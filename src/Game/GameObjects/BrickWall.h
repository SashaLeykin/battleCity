#ifndef BRICKWALL_H
#define BRICKWALL_H

//#include <glm/vec2.hpp>

#include <memory>
#include <array>

#include "IGameObject.h"

namespace RenderEngine {
	class Sprite;
}
//� ����� BrickWall - ��������� �����
class BrickWall : public IGameObject {
public:
	//����� enum �� ��������� �������� �������������� � int, � ����� �� ���������� 
	// ������������� �� ������ ������������.
	//��� ����������� ����� ������� ����. �����
	enum class EBrickWallType {
		All,
		Top,
		Bottom,
		Left,
		Right,
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight
	};
	//��������� �������(�����, �����������..)
	enum class EBrickState {
		All,
		TopLeft,
		TopRight,
		Top,
		BottomLeft,
		Left,
		TopRight_BottomLeft,
		Top_BottomLeft,
		BottomRight,
		TopLeft_BottomRight,
		Right,
		Top_BottomRight,
		Bottom,
		TopLeft_Bottom,
		TopRight_Bottom,
		Destroyed
	};

	//��� ��������� ������� � enum class EBrickState
	enum class EBrickLocation {
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight
	};

	BrickWall(const EBrickWallType eBrickWallType, 
		      const glm::vec2& position, 
			  const glm::vec2& size, 
			  const float rotation, 
		      const float layer);
	virtual void render() const override;
	virtual void update(const double delta) override;

private:
	//�������� ��������� �� ������
	//std::shared_ptr<RenderEngine::Sprite> m_pCurrentSprite;

	void renderBrick(const EBrickLocation eBrickLocation) const;

	//��� �������� ��������� ����� ���������� �� 4 ���������
	std::array<EBrickState, 4> m_eCurrentBrickState;

	//��� �������� ����� ��������� ����� �� 4 ��������� ������
	std::array<std::shared_ptr<RenderEngine::Sprite>, 15> m_sprites;

	//�������� ������� ��� �������� �������� 4 ����������� �������
	std::array<glm::vec2, 4> m_blockOffset;
};

#endif // !BRICKWALL_H

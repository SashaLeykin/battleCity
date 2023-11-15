#ifndef BETONWALL_H
#define BETONWALL_H

//#include <glm/vec2.hpp>

#include <memory>
#include <array>

#include "IGameObject.h"

namespace RenderEngine {
	class Sprite;
}
//� ����� BrickWall - ��������� �����
class BetonWall : public IGameObject {
public:
	//����� enum �� ��������� �������� �������������� � int, � ����� �� ���������� 
	// ������������� �� ������ ������������.
	//��� ����������� ����� ������� ����. �����
	enum class EBetonWallType {
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
	enum class EBlockState {
		Enabled,
		Destroyed
	};

	//��� ��������� ������� � enum class EBrickState
	enum class EBlockLocation {
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight
	};

	BetonWall(const EBetonWallType eBetonWallType, const glm::vec2& position, const glm::vec2& size, const float rotation);
	virtual void render() const override;
	virtual void update(const uint64_t delta) override;

private:
	void renderBlock(const EBlockLocation eBlockLocation) const;
	//��� �������� ��������� ����� ���������� �� 4 ���������
	std::array<EBlockState, 4> m_eCurrentBlockState;
	//��� �������� ����� ��������� ����� �� 4 ��������� ������
	std::shared_ptr<RenderEngine::Sprite> m_sprites;
	//�������� ������� ��� �������� �������� 4 ����������� �������
	std::array<glm::vec2, 4> m_blockOffset;
};

#endif // !BETONWALL_H

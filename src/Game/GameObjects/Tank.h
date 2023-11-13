#pragma once

#include <glm/vec2.hpp>
#include <memory>

#include "IGameObject.h"
#include "../../Renderer/SpriteAnimator.h"

namespace RenderEngine {
	class Sprite;
}

class Tank : public IGameObject {
public:

	enum class EOrientation {
		Top,
		Bottom,
		Left,
		Right
	};

	//�����������
	Tank(std::shared_ptr<RenderEngine::Sprite> pSprite_top, 
		 std::shared_ptr<RenderEngine::Sprite> pSprite_bottom,
		 std::shared_ptr<RenderEngine::Sprite> pSprite_left,
		 std::shared_ptr<RenderEngine::Sprite> pSprite_right,
		 const float velocity, 
		 const glm::vec2 position, 
		 const glm::vec2& size);

	//��� ���������
	void render() const override;

	//��������� ���������(�����������) �����
	void setOrientation(const EOrientation eOrientation);

	//�������� �����
	void move(const bool move);

	//��� �������� �������
	void update(const uint64_t delta) override;

private:
	EOrientation m_eOrientation;
	//���������� ������ ������� � �����
	std::shared_ptr<RenderEngine::Sprite> m_pSprite_top;
	std::shared_ptr<RenderEngine::Sprite> m_pSprite_bottom;
	std::shared_ptr<RenderEngine::Sprite> m_pSprite_left;
	std::shared_ptr<RenderEngine::Sprite> m_pSprite_right;
	//4 ��������� ��� �������� ������� ��� ������� ��������� �����
	RenderEngine::SpriteAnimator m_spriteAnimatop_top;
	RenderEngine::SpriteAnimator m_spriteAnimatop_bottom;
	RenderEngine::SpriteAnimator m_spriteAnimatop_left;
	RenderEngine::SpriteAnimator m_spriteAnimatop_right;

	//���������� ������������� ��������
	bool m_move;
	//��������
	float m_velocity;	
	//���������� ��� �������� ����������� �������� �����
	glm::vec2 m_moveOffset;
};
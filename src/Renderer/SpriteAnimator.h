#ifndef SPRITEANIMATOR_H
#define SPRITEANIMATOR_H

#include <memory>

namespace RenderEngine {

	class Sprite;

	class SpriteAnimator {
	public:
		// � ������������ ���������� ������ �� ������
		SpriteAnimator(std::shared_ptr<Sprite> pSprite);
		//������� ��� ��������� �������� �����
		size_t getCurrentFrame() const { return m_currentFrame; }
		//������� ��� ���������� �������� �����
		void apdate(const double delta);

	private:
		//���������� ��� �������� ������ �� ������� ������
		std::shared_ptr<Sprite> m_pSprite;
		//���������� ��� �������� �������� �����
		size_t m_currentFrame;
		//������� ����� ����������������� �����
		double m_currentFrameDuration;
		//������� ����� ��������
		double m_currentAnimationTime;
	};

}

#endif // !SPRITEANIMATOR_H

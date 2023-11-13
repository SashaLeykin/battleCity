#ifndef SPRITEANIMATOR_H
#define SPRITEANIMATOR_H

#include <memory>

namespace RenderEngine {

	class Sprite;

	class SpriteAnimator {
	public:
		// в конструкторе передается ссылка на спрайт
		SpriteAnimator(std::shared_ptr<Sprite> pSprite);
		//функция для получения текущего кадра
		size_t getCurrentFrame() const { return m_currentFrame; }
		//функция для обновления текущего кадра
		void apdate(const uint64_t delta);

	private:
		//переменная для хранения ссылки на текузий спрайт
		std::shared_ptr<Sprite> m_pSprite;
		//переменная для хранения текущего кадра
		size_t m_currentFrame;
		//текущее время Продолжительности кадра
		uint64_t m_currentFrameDuration;
		//текущее время анимации
		uint64_t m_currentAnimationTime;
	};

}

#endif // !SPRITEANIMATOR_H

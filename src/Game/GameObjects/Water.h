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
//о бъект BrickWall - Кирпичная стена
class Water : public IGameObject {
public:
	//Класс enum не допускает неявного преобразования в int, а также не сравнивает 
	// перечислители из разных перечислений.	
	//для упрощения доступа к enum class EBrickState
	enum class EBlockLocation {
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight
	};

	Water(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer);
	virtual void render() const override;

	//для анимации спрайта
	void update(const double delta) override;
	
private:
	void renderBlock(const EBlockLocation eBlockLocation) const;	
	//для создания блока кирпичной стены из 4 маленьких блоков
	std::shared_ptr<RenderEngine::Sprite> m_sprites;
	//для анимации спрайта
	RenderEngine::SpriteAnimator m_spriteAnimator;
	//создание массива для хранения векторов 4 квадратиков спрайта
	std::array<glm::vec2, 4> m_blockOffset;
};

#endif // !WATER_H

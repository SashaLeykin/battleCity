#ifndef ICE_H
#define ICE_H

//#include <glm/vec2.hpp>

#include <memory>
#include <array>

#include "IGameObject.h"

namespace RenderEngine {
	class Sprite;
}
//о бъект BrickWall - Кирпичная стена
class Ice : public IGameObject {
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

	Ice(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer);
	virtual void render() const override;
	
private:
	void renderBlock(const EBlockLocation eBlockLocation) const;	
	//для создания блока кирпичной стены из 4 маленьких блоков
	std::shared_ptr<RenderEngine::Sprite> m_sprites;
	//создание массива для хранения векторов 4 квадратиков спрайта
	std::array<glm::vec2, 4> m_blockOffset;
};

#endif // !ICE_H

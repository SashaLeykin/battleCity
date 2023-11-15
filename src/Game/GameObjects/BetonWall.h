#ifndef BETONWALL_H
#define BETONWALL_H

//#include <glm/vec2.hpp>

#include <memory>
#include <array>

#include "IGameObject.h"

namespace RenderEngine {
	class Sprite;
}
//о бъект BrickWall - Кирпичная стена
class BetonWall : public IGameObject {
public:
	//Класс enum не допускает неявного преобразования в int, а также не сравнивает 
	// перечислители из разных перечислений.
	//для обозначения видов спрайта кирп. стены
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
	//состояние кирпича(целый, разрушенный..)
	enum class EBlockState {
		Enabled,
		Destroyed
	};

	//для упрощения доступа к enum class EBrickState
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
	//для зранения состояния блока состоящего из 4 маленьких
	std::array<EBlockState, 4> m_eCurrentBlockState;
	//для создания блока кирпичной стены из 4 маленьких блоков
	std::shared_ptr<RenderEngine::Sprite> m_sprites;
	//создание массива для хранения векторов 4 квадратиков спрайта
	std::array<glm::vec2, 4> m_blockOffset;
};

#endif // !BETONWALL_H

#ifndef BRICKWALL_H
#define BRICKWALL_H

//#include <glm/vec2.hpp>

#include <memory>
#include <array>

#include "IGameObject.h"

namespace RenderEngine {
	class Sprite;
}
//о бъект BrickWall -  ирпична€ стена
class BrickWall : public IGameObject {
public:
	// ласс enum не допускает не€вного преобразовани€ в int, а также не сравнивает 
	// перечислители из разных перечислений.
	//дл€ обозначени€ видов спрайта кирп. стены
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
	//состо€ние кирпича(целый, разрушенный..)
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

	//дл€ упрощени€ доступа к enum class EBrickState
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
	//хранение указател€ на спрайт
	//std::shared_ptr<RenderEngine::Sprite> m_pCurrentSprite;

	void renderBrick(const EBrickLocation eBrickLocation) const;

	//дл€ зранени€ состо€ни€ блока состо€щего из 4 маленьких
	std::array<EBrickState, 4> m_eCurrentBrickState;

	//дл€ создани€ блока кирпичной стены из 4 маленьких блоков
	std::array<std::shared_ptr<RenderEngine::Sprite>, 15> m_sprites;

	//создание массива дл€ хранени€ векторов 4 квадратиков спрайта
	std::array<glm::vec2, 4> m_blockOffset;
};

#endif // !BRICKWALL_H

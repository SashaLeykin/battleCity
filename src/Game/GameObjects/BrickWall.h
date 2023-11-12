#ifndef BRICWALL_H
#define BRICWALL_H

//#include <glm/vec2.hpp>

#include <memory>

#include "IGameObject.h"

namespace RenderEngine {
	class Sprite;
}
//о бъект BrickWall - Кирпичная стена
class BrickWall : public IGameObject {
public:
	BrickWall(const std::shared_ptr<RenderEngine::Sprite> pSprite, const glm::vec2& position, const glm::vec2& size, const float rotation);
	virtual void render() const override;
	virtual void update(const uint64_t delta) override;

private:
	//хранение указателя на спрайт
	std::shared_ptr<RenderEngine::Sprite> m_pCurrentSprite;
};

#endif // !BRICWALL_H

#pragma once

#include "Sprite.h"

#include <map>
#include <vector>

namespace RenderEngine {	

	class AnimatedSprite : public Sprite {
	public:
		AnimatedSprite(std::shared_ptr<Texture2D> pTexture,
			 std::string initialSubTexturw,
			 std::shared_ptr<ShaderProgram> pShaderProgram,
			const glm::vec2& position = glm::vec2(0.f),
			const glm::vec2& size = glm::vec2(1.f),
			const float rotation = 0.f);

		//для установки самого состояния
		void insertState(std::string state, std::vector<std::pair<std::string, uint64_t>> subTexturesDuration);

		void render() const override;

		//которая будет устанавливать конктретное состояние кадра
		void setState(const std::string& newState);

		//которая будет обновлять
		void update(const uint64_t delta);

	private:
		//для хранения состояния и длительность кадров спрайта 
		std::map<std::string, std::vector<std::pair<std::string, uint64_t>>> m_stateMap;
		//
		size_t m_currentFrame = 0;
		//время прошедшее с начала установки
		uint64_t m_currentAnimationTame = 0;

		std::map<std::string, std::vector<std::pair<std::string, uint64_t>>>::const_iterator m_currentAnimationDuration;

		//реальное состояние (mutable - возможность менять при конст функции)
		mutable bool m_dirty = false;

	};
}
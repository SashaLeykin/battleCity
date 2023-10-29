#include "AnimatedSprite.h"
#include "Texture2D.h"

#include "iostream"

namespace Renderer {
	AnimatedSprite::AnimatedSprite( std::shared_ptr<Texture2D> pTexture, 
		std::string initialSubTexturw, 
		 std::shared_ptr<ShaderProgram> pShaderProgram, 
		const glm::vec2& position, 
		const glm::vec2& size, 
		const float rotation)
		//перредача параметров в конструктор  базавого класса
		:Sprite(std::move(pTexture), std::move(initialSubTexturw), std::move(pShaderProgram),
			    position, size, rotation)
	{
		m_currentAnimationDuration = m_stateMap.end();
	}

	void AnimatedSprite::insertState(std::string state, std::vector<std::pair<std::string, uint64_t>> subTexturesDuration)
	{
		m_stateMap.emplace(std::move(state), std::move(subTexturesDuration));//emplace - устанавливать
	}
	
	void AnimatedSprite::setState(const std::string& newState)
	{
		auto it = m_stateMap.find(newState);
		if (it == m_stateMap.end())
		{
			std::cout << "Can't animation state:" << newState << std::endl;
			return;
		}

		//не обнуляю счетчики пока совершается действие
		if (it != m_currentAnimationDuration)
		{
			m_currentAnimationTame = 0;
			m_currentFrame = 0;
			m_currentAnimationDuration = it;
			m_dirty = true; 
		}		

	}
	void AnimatedSprite::update(const uint64_t delta)
	{
		if (m_currentAnimationDuration != m_stateMap.end())
		{
			m_currentAnimationTame += delta;

			while (m_currentAnimationTame >= m_currentAnimationDuration->second[m_currentFrame].second)
			{
				m_currentAnimationTame -= m_currentAnimationDuration->second[m_currentFrame].second;
				++m_currentFrame;
				m_dirty = true;

				if (m_currentFrame == m_currentAnimationDuration->second.size())
				{
					m_currentFrame = 0;
				}
			}			
		}
	}

	void AnimatedSprite::render() const 
	{
		if (m_dirty)
		{
			auto subTexture = m_pTexture->getSubTexture(m_currentAnimationDuration->second[m_currentFrame].first);

			const GLfloat textureCoords[] = {
				// u   v
				subTexture.leftBottonUV.x, subTexture.leftBottonUV.y,
				subTexture.leftBottonUV.x, subTexture.rightTopUV.y,
				subTexture.rightTopUV.x, subTexture.rightTopUV.y,

				//subTexture.rightTopUV.x, subTexture.rightTopUV.y,
				subTexture.rightTopUV.x, subTexture.leftBottonUV.y
				//subTexture.leftBottonUV.x, subTexture.leftBottonUV.y
			};

			//после того как создали VertexBuffer and IndexBuffer
			m_textureCoordsBuffer.upDate(textureCoords, 2 * 4 * sizeof(GLfloat));
			//glBindBuffer(GL_ARRAY_BUFFER, m_textureCoordsVBO);
			//glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(textureCoords), &textureCoords);
			//glBindBuffer(GL_ARRAY_BUFFER, 0);

			m_dirty = false;
		}
		
		Sprite::render();
	}
}
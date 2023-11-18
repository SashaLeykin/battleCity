#pragma once

#include <glad/glad.h>
#include <glm/vec2.hpp>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"

#include <glad/glad.h>
#include <glm/vec2.hpp>

#include <memory>
#include <string>

namespace RenderEngine {

	class Texture2D;
	class ShaderProgram;

	class Sprite {
	public:
		//вспомогательная структура для хранения готовых координат саб текстуры
		//полность описывает кадр
		struct FrameDescription {
			FrameDescription(const glm::vec2 _leftBottomUV, const glm::vec2 _rightTopUV, const size_t _duration)
				:leftBottomUV(_leftBottomUV)
				, rightTopUV(_rightTopUV)
				, duration(_duration)
			{}
			//левый нижний угол
			glm::vec2 leftBottomUV;
			//правый верхний угол
			glm::vec2 rightTopUV;
			//продолжительность
			size_t duration;
		};

		public:
		Sprite( std::shared_ptr<Texture2D> pTexture,
			    std::string initialSubTexture,
			    std::shared_ptr<ShaderProgram> pShaderProgram);

		~Sprite();

		Sprite(const Sprite&) = delete;
		Sprite& operator=(const Sprite&) = delete;

		void render(const glm::vec2& position, 
			        const glm::vec2& size, 
					const float rotation, 
					const float layer = 0.f, 
					const size_t frameId = 0) const;
		
		void insertFrames(std::vector<FrameDescription> framesDescriptions);

		uint64_t getFrameDuration(const size_t frameId) const;
		//возвращает колличество кадров
		size_t getFrameCount() const;


	protected:
		std::shared_ptr<Texture2D> m_pTexture;
		std::shared_ptr<ShaderProgram> m_pShaderProgram;
		
		
		VertexArray m_vertexArray;
		VertexBuffer m_vertexCoordsBuffer;
		VertexBuffer m_textureCoordsBuffer;
		IndexBuffer m_indexBuffer;

		//вектор для хранения названия и координаты саб текстур продллжительность кадров
		std::vector<FrameDescription> m_framesDescriptions;
		//для сохранения последнего отрисованного кадра
		//mutable - возможность вносить изменения в константную функцию
		mutable size_t m_lastFrameId;
	};

}
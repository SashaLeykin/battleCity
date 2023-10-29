#pragma once

#include <glad/glad.h>

namespace Renderer {
	class VertexBuffer {
		public:
		//конструктор
		VertexBuffer();
		//деструктор
		~VertexBuffer();
		
		//запреты
		VertexBuffer(const VertexBuffer&) = delete;
		VertexBuffer& operator=(const VertexBuffer&) = delete;
		
		VertexBuffer& operator=(VertexBuffer&& vertexBuffer) noexcept;
		VertexBuffer(VertexBuffer&& vertexBuffer) noexcept;
		
		//функция для активизации VBO
		void init(const void* data, const unsigned int size); //принимает поинтр на данные
		//функция для обновления данных
		void upDate(const void* data, const unsigned int size) const;
		//функции для привязки и отвязки данных
		void bind() const;
		void unBind() const;
		
		private:
		GLuint m_id;
	};	
}
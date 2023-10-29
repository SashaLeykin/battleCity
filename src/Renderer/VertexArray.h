#pragma once

#include "vertexBuffer.h"
#include "VertexBufferLayout.h"

#include <glad/glad.h>

namespace Renderer {
	class VertexArray {
		public:
		//конструктор
		VertexArray();
		//деструктор
		~VertexArray();
		
		//запреты
		VertexArray(const VertexArray&) = delete;
		VertexArray& operator=(const VertexArray&) = delete;
		
		VertexArray& operator=(VertexArray&& vertexArray);
		VertexArray(VertexArray&& vertexArray) noexcept;

		void addBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout);
		
		//функции для привязки и отвязки данных
		void bind() const;
		void unBind() const;
		
		private:
		GLuint m_id = 0;
		unsigned int m_elementCount = 0;
	};
	
}
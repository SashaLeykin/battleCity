#pragma once

#include <glad/glad.h>

namespace Renderer {
	class IndexBuffer {
	public:
		//конструктор
		IndexBuffer();
		//деструктор
		~IndexBuffer();

		//запреты
		IndexBuffer(const IndexBuffer&) = delete;
		IndexBuffer& operator=(const IndexBuffer&) = delete;

		IndexBuffer& operator=(IndexBuffer&& indexBuffer);
		IndexBuffer(IndexBuffer&& indexBuffer) noexcept;

		//функция для активизации EBO
		void init(const void* data, const unsigned int size); //принимает поинтр на данные
		
		//функции для привязки и отвязки данных
		void bind() const;
		void unBind() const;

	private:
		GLuint m_id;
	};
}


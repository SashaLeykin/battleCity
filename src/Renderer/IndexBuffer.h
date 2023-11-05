#pragma once

#include <glad/glad.h>

namespace RenderEngine {
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
		void init(const void* data, const unsigned int count); //принимает поинтр на данные
		
		//функции для привязки и отвязки данных
		void bind() const;
		void unBind() const;

		unsigned int getCount() const { return m_count; };

	private:
		GLuint m_id;
		//
		unsigned int m_count;
	};
}


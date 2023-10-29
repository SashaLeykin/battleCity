#include "IndexBuffer.h"

namespace Renderer {
	//конструктор
	IndexBuffer::IndexBuffer()
		:m_id(0)
	{
	}
	//деструктор
	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &m_id);
	}

	IndexBuffer& IndexBuffer::operator=(IndexBuffer&& indexBuffer)
	{
		m_id = indexBuffer.m_id;
		indexBuffer.m_id = 0;
		return *this;
	}
	IndexBuffer::IndexBuffer(IndexBuffer&& indexBuffer) noexcept
	{
		m_id = indexBuffer.m_id;
		indexBuffer.m_id = 0;
	}

	//функция для активизации EBO
	void IndexBuffer::init(const void* data, const unsigned int size) //принимает поинтр на данные
	{
		glGenBuffers(1, &m_id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}
	
	//функции для привязки и отвязки данных
	void IndexBuffer::bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
	}
	void IndexBuffer::unBind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}
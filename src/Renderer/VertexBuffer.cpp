#include "VertexBuffer.h"

namespace Renderer {
	//конструктор
	VertexBuffer::VertexBuffer()
		:m_id(0)
	{		
	}
	//деструктор
	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_id);
	}
	
	VertexBuffer& VertexBuffer::operator=(VertexBuffer&& vertexBuffer) noexcept
	{
		m_id = vertexBuffer.m_id;
		vertexBuffer.m_id = 0;
		return *this;
	}
	VertexBuffer::VertexBuffer(VertexBuffer&& vertexBuffer) noexcept
	{
		m_id = vertexBuffer.m_id;
		vertexBuffer.m_id = 0;
	}
		
	//функция для активизации VBO
	void VertexBuffer::init(const void* data, const unsigned int size) //принимает поинтр на данные
	{
		glGenBuffers(1, &m_id);
		glBindBuffer(GL_ARRAY_BUFFER, m_id);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}
	//функция для обновления данных
	void VertexBuffer::upDate(const void* data, const unsigned int size) const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_id);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}
	//функции для привязки и отвязки данных
	void VertexBuffer::bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_id);
	}
	void VertexBuffer::unBind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}
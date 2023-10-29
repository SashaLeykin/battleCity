#include "VertexArray.h"

namespace Renderer {
	//конструктор
	VertexArray::VertexArray()	
	{		
		glGenVertexArrays(1, & m_id);
	}
	//деструктор
	VertexArray::~VertexArray()
	{
		glad_glDeleteVertexArrays(1, &m_id);
	}
	
	VertexArray& VertexArray::operator=(VertexArray&& vertexArray)
	{
		m_id = vertexArray.m_id;
		vertexArray.m_id = 0;
		return *this;
	}
	VertexArray::VertexArray(VertexArray&& vertexArray) noexcept
	{
		m_id = vertexArray.m_id;
		vertexArray.m_id = 0;
	}
			
	//функции для привязки и отвязки данных
	void VertexArray::bind() const
	{
		glBindVertexArray(m_id);
	}
	void VertexArray::unBind() const
	{
		glBindVertexArray(0);
	}

	void VertexArray::addBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout)
	{
		bind();
		vertexBuffer.bind();
		const auto& layoutElements = layout.getLayoutElement();
		GLbyte* offset = nullptr;
		for (unsigned int i = 0; i < layoutElements.size(); i++)
		{
			const auto& currentLayoutElement = layoutElements[i];
			GLuint currentAtribIndex = m_elementCount + i;
			glEnableVertexAttribArray(currentAtribIndex);
			glVertexAttribPointer(currentAtribIndex, currentLayoutElement.count, currentLayoutElement.type, currentLayoutElement.normalized, layout.getStride(), offset);
			offset += currentLayoutElement.size;
		}
		m_elementCount += static_cast<unsigned int>(layoutElements.size());
	}
}
#pragma once

#include <vector>
#include <glad/glad.h>

namespace Renderer
{
	struct VertexBufferLayoutElement {
		GLuint count;
		GLenum type;
		GLboolean normalized;
		unsigned int size;
	};

	class VertexBufferLayout {
	public:
		//�����������
		VertexBufferLayout();

		void rezerveElements(const size_t count);

		unsigned int getStride() const { return m_stride; }

		const std::vector<VertexBufferLayoutElement>& getLayoutElement() const 
		{ return m_layoutElements; }
	
		void addElementLayoutFloat(const unsigned int count, const bool normalized);

	private:
		//��������� ����� ��������� �������� ����� ������ � (��������, ������� ...)
		std::vector<VertexBufferLayoutElement> m_layoutElements;
		unsigned int m_stride;
	};
}
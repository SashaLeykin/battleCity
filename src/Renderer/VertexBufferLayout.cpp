#include "VertexBufferLayout.h"

namespace Renderer {
	Renderer::VertexBufferLayout::VertexBufferLayout()
		: m_stride(0)
	{}

	void Renderer::VertexBufferLayout::rezerveElements(const size_t count)
	{
		m_layoutElements.reserve(count);
	}

	void Renderer::VertexBufferLayout::addElementLayoutFloat(const unsigned int count, const bool normalized)
	{
		m_layoutElements.push_back({ count, GL_FLOAT, normalized });
		m_stride += m_layoutElements.back().size;
	}
}
#include "Renderer.h"

namespace RenderEngine {
	void Renderer::Draw(const VertexArray& vertexArray, 
						const IndexBuffer& indexBuffer, 
						const ShaderProgram& shader)
	{
		shader.use();
		vertexArray.bind();
		indexBuffer.bind();

		glDrawElements(GL_TRIANGLES, indexBuffer.getCount(), GL_UNSIGNED_INT, nullptr);
	}
	void Renderer::setClearColor(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
	}

	void Renderer::clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Renderer::setVieport(unsigned int width, unsigned int height, unsigned int leftOffset, unsigned int bottonOffset)
	{
		glViewport(leftOffset, bottonOffset, width, height);
	}

	std::string Renderer::getRendererStr()
	{
		
		return (char*)glGetString(GL_RENDERER);
	}

	std::string Renderer::getVersionStr()
	{		
		return (char*)glGetString(GL_VERSION);;
	}
}

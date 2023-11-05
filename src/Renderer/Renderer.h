#ifndef RENDERER_H
#define RENDERER_H

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "ShaderProgram.h"

#include "string"

namespace RenderEngine {

	class Renderer {
	public:
		static void Draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const ShaderProgram& shader);
		//убрать из main функции цвета фона программы
		static void setClearColor(float r, float g, float b, float a);
		static void clear();
		static void setVieport(unsigned int width, unsigned int height, 
			unsigned int leftOffset = 0, unsigned int bottonOffset = 0);

		static std::string getRendererStr();
		static std::string getVersionStr();

	private:

	};

}

#endif // !RENDERER_H

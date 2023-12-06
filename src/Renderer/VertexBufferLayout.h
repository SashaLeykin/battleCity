#pragma once

#include <vector>
#include <glad/glad.h>

namespace RenderEngine
{
	struct VertexBufferLayoutElement {
		GLint count; //количество
		GLenum type; //тип
		GLboolean normalized; //будут ли они нормализованы
		unsigned int size;
	};

	class VertexBufferLayout { // макет(шаблон) который показывает из чего состоит буфер VAO
	public:
		//конструктор
		VertexBufferLayout();

		//для резервирования количества элементов в векторе m_layoutElements 
		void rezerveElements(const size_t count);

		// возвращает шаг 
		unsigned int getStride() const { return m_stride; }

		//возвращает элементы вектора
		const std::vector<VertexBufferLayoutElement>& getLayoutElement() const 
		{ return m_layoutElements; }

	    //принимает количество элементов и будут ли они нормализованы
		void addElementLayoutFloat(const unsigned int count, const bool normalized);

	private:
		//описывает через структуру VertexBufferLayoutElement элементы наших данных о (текстуре, спрайте ...)
		std::vector<VertexBufferLayoutElement> m_layoutElements;
		unsigned int m_stride; //шаг между элементами
	};
}
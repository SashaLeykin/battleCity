 #include "Sprite.h"

#include "ShaderProgram.h"
#include "Texture2D.h"
#include "Renderer.h"

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace RenderEngine {

	Sprite::Sprite( std::shared_ptr<Texture2D> pTexture,
		            std::string initialSubTexture,
		            std::shared_ptr<ShaderProgram> pShaderProgram)
					: m_pTexture(std::move(pTexture))
					, m_pShaderProgram(std::move(pShaderProgram))					
	{		
		//прямоугольник можно отрисовать по 4 вертоксам но все равно 2 треугольниками
		const GLfloat vertexCoords[] = {
			// 1 - 2    1 -2     2
			// |   |    | /    / |
			// 0 - 3    0     0 -3

			// x   y
			 0.f, 0.f,
			 0.f, 1.f,
			 1.f, 1.f,
			 1.f, 0.f
		};

		auto subTexture = m_pTexture->getSubTexture(std::move(initialSubTexture));

		const GLfloat textureCoords[] = {
			// u   v
			subTexture.leftBottomUV.x, subTexture.leftBottomUV.y,
			subTexture.leftBottomUV.x, subTexture.rightTopUV.y,
			subTexture.rightTopUV.x,   subTexture.rightTopUV.y,						
			subTexture.rightTopUV.x,   subTexture.leftBottomUV.y			
		};

		//создание индексов для указания вершин треугольников
		const GLuint indices[] = {
			0, 1, 2, //первый треугольник
			2, 3, 0	 //второй треугольник	
		};

		// 2 * 4 * sizeof(GLfloat) - 2(x,y) * 4(4 - вершины) * размер 
		m_vertexCoordsBuffer.init(vertexCoords, 2 * 4 * sizeof(GLfloat));
		//
		VertexBufferLayout vertexCoordsLayout;
		//добовляем елемент
		vertexCoordsLayout.addElementLayoutFloat(2, false);
		m_vertexArray.addBuffer(m_vertexCoordsBuffer, vertexCoordsLayout);
			

		m_textureCoordsBuffer.init(textureCoords, 2 * 4 * sizeof(GLfloat));
		VertexBufferLayout textureCoordsLayout;
		textureCoordsLayout.addElementLayoutFloat(2, false);
		m_vertexArray.addBuffer(m_textureCoordsBuffer, textureCoordsLayout);
				
		m_indexBuffer.init(indices, 6);
				
		m_vertexArray.unBind();
		m_indexBuffer.unBind();
	}

	Sprite::~Sprite()
	{
		//glDeleteBuffers(1, &m_vertexCoordsVBO);
		//glDeleteBuffers(1, &m_textureCoordsVBO);
		//glDeleteBuffers(1, &m_EBO);
		//glDeleteVertexArrays(1, &m_VAO);
	}
	void Sprite::render(const glm::vec2& position, const glm::vec2& size, const float rotation) const
	{
		m_pShaderProgram->use();

		glm::mat4 model(1.f);

		model = glm::translate(model, glm::vec3(position, 0.f));
		model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.f));
		model = glm::rotate(model,glm::radians(rotation), glm::vec3(0.f, 0.f, 1.f));
		model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.f));
		model = glm::scale(model, glm::vec3(size, 1.f));
			
		m_pShaderProgram->setMatrix4("modelMat", model);

		glActiveTexture(GL_TEXTURE0);
		m_pTexture->bind();
		
		Renderer::Draw(m_vertexArray, m_indexBuffer, *m_pShaderProgram);
	}	
}

 #include "Sprite.h"

#include "ShaderProgram.h"
#include "Texture2D.h"

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace Renderer {
	Sprite::Sprite( std::shared_ptr<Texture2D> pTexture,
		 std::string initialSubTexture,
		std::shared_ptr<ShaderProgram> pShaderProgram,
		const glm::vec2& position,
		const glm::vec2& size,
		const float rotation)
		: m_pTexture(std::move(pTexture))
		, m_pShaderProgram(std::move(pShaderProgram))
		, m_position(position)
		, m_size(size)
		, m_rotation(rotation)
	{
		//const GLfloat vertexCoords[] = {
		//	// 2  3    1
		//	// | /    / |
		//	// 1     3  2

		//	// x   y
		//	 0.f, 0.f,
		//	 0.f, 1.f,
		//	 1.f, 1.f,

		//	 1.f, 1.f,
		//	 1.f, 0.f,
		//	 0.f, 0.f
		//};
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

		//const GLfloat textureCoords[] = {		
		//	// u   v
		//	 subTexture.leftBottonUV.x, subTexture.leftBottonUV.y,
		//	subTexture.leftBottonUV.x, subTexture.rightTopUV.y,
		//	subTexture.rightTopUV.x, subTexture.rightTopUV.y,

		//	subTexture.rightTopUV.x, subTexture.rightTopUV.y,
		//	subTexture.rightTopUV.x, subTexture.leftBottonUV.y,
		//	subTexture.leftBottonUV.x, subTexture.leftBottonUV.y
		//};
		const GLfloat textureCoords[] = {
			// u   v
			subTexture.leftBottonUV.x, subTexture.leftBottonUV.y,
			subTexture.leftBottonUV.x, subTexture.rightTopUV.y,
			subTexture.rightTopUV.x,   subTexture.rightTopUV.y,						
			subTexture.rightTopUV.x,   subTexture.leftBottonUV.y			
		};

		//создание индексов для указания вершин треугольников
		const GLuint indices[] = {
			0, 1, 2, //первый треугольник
			2, 3, 0	 //второй треугольник	
		};

		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		// 2 * 4 * sizeof(GLfloat) - 2(x,y) * 4(4 - вершины) * размер 
		m_vertexCoordsBuffer.init(vertexCoords, 2 * 4 * sizeof(GLfloat));

		//glGenBuffers(1, &m_vertexCoordsVBO);
		//glBindBuffer(GL_ARRAY_BUFFER, m_vertexCoordsVBO);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(vertexCoords), &vertexCoords, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

		m_textureCoordsBuffer.init(textureCoords, 2 * 4 * sizeof(GLfloat));

		//glGenBuffers(1, &m_textureCoordsVBO);
		//glBindBuffer(GL_ARRAY_BUFFER, m_textureCoordsVBO);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(textureCoords), &textureCoords, GL_STATIC_DRAW);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

		m_indexBuffer.init(indices, 6 * sizeof(GLuint));

		//генерация EBO для индексов
		//glGenBuffers(1, &m_EBO);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		//заполнение данных
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);

		//зануленеие текущих буферав
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	Sprite::~Sprite()
	{
		//glDeleteBuffers(1, &m_vertexCoordsVBO);
		//glDeleteBuffers(1, &m_textureCoordsVBO);
		//glDeleteBuffers(1, &m_EBO);
		glDeleteVertexArrays(1, &m_VAO);
	}
	void Sprite::render() const
	{
		m_pShaderProgram->use();

		glm::mat4 model(1.f);

		model = glm::translate(model, glm::vec3(m_position, 0.f));
		model = glm::translate(model, glm::vec3(0.5f * m_size.x, 0.5f * m_size.y, 0.f));
		model = glm::rotate(model,glm::radians(m_rotation), glm::vec3(0.f, 0.f, 1.f));
		model = glm::translate(model, glm::vec3(-0.5f * m_size.x, -0.5f * m_size.y, 0.f));
		model = glm::scale(model, glm::vec3(m_size, 1.f));

		glBindVertexArray(m_VAO);
		m_pShaderProgram->setMatrix4("modelMat", model);

		glActiveTexture(GL_TEXTURE0);
		m_pTexture->bind();

		//отрисовка без индексов, но больше вершин
		//glDrawArrays(GL_TRIANGLES, 0, 6);

		//отрисовка при помощи индексов
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		glBindVertexArray(0);
	}
	void Sprite::setPosition(const glm::vec2& position)
	{
		m_position = position;
	}
	void Sprite::setSize(const glm::vec2& size)
	{
		m_size = size;
	}
	void Sprite::setRotation(const float rotation)
	{
		m_rotation = rotation;
	}
}

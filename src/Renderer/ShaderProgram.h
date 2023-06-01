#pragma once

#include <glad/glad.h>
#include <string>

namespace Renderer {
	class ShaderProgram {
	public:
		ShaderProgram(const std::string& vertexShander, const std::string& fragmentShander);
		~ShaderProgram();
		bool isCompiled() const { return m_isCompiled; }
		void use() const;

		ShaderProgram() = delete;
		ShaderProgram(ShaderProgram&) = delete;
		ShaderProgram& operator=(const ShaderProgram&) = delete;

		ShaderProgram& operator=(ShaderProgram&& shaderProgram) noexcept;
		ShaderProgram(ShaderProgram&& shaderProgram) noexcept;

	private:
		bool creadShader(const std::string& sourse, GLenum shaderType, GLuint& shaderID);
		bool m_isCompiled = false;
		GLuint m_ID = 0;
	};
}

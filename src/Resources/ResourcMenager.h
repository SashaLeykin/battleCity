#pragma once

#include <string>
#include <memory>
#include <map>

namespace Renderer
{
	class ShaderProgram;
	class Texture2D;
}

class ResourceMenager {
public:
	ResourceMenager(const std::string& executablePath);
	~ResourceMenager() = default;

	ResourceMenager(const ResourceMenager&) = delete;
	ResourceMenager& operator= (const ResourceMenager&) = delete;
	ResourceMenager& operator=(ResourceMenager&&) = delete;
	ResourceMenager(ResourceMenager&&) = delete;

	std::shared_ptr<Renderer::ShaderProgram> loadShaders(const std::string& shaderName,
														const std::string& vertexPath,
														const std::string& fragmentPath);
	std::shared_ptr<Renderer::ShaderProgram> getShaderProgram(const std::string& shaderName);
	std::shared_ptr<Renderer::Texture2D> loadTexture(const std::string& textureName, const std::string& texturePath);

	std::shared_ptr<Renderer::Texture2D> getTexture(const std::string& textureName);

private:
	std::string getFileString(const std::string& realativeFilePath) const;
	//std::mapЧ это отсортированный ассоциативный контейнер, содержащий пары ключ-значение 
	//с уникальными ключами.
	typedef std::map<const std::string, std::shared_ptr<Renderer::ShaderProgram>> ShaderProgramsMap;
	ShaderProgramsMap m_shaderPrograms;

	typedef std::map<const std::string, std::shared_ptr<Renderer::Texture2D>> TexturesMap;
	TexturesMap m_textures;
	std::string m_path;
};
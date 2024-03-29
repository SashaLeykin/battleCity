#pragma once

#include <string>
#include <memory>
#include <map>
#include <vector>

namespace RenderEngine
{
	class ShaderProgram;
	class Texture2D;
	class Sprite;	
}

class ResourceMenager {
public:
	// ������ ������������ 
	static void setExecutablePath(const std::string& executablePath);
	// ������ �����������
	static void unLoadAllResources();

	~ResourceMenager() = delete;
	ResourceMenager() = delete;
	ResourceMenager(const ResourceMenager&) = delete;
	ResourceMenager& operator= (const ResourceMenager&) = delete;
	ResourceMenager& operator=(ResourceMenager&&) = delete;
	ResourceMenager(ResourceMenager&&) = delete;

	static std::shared_ptr<RenderEngine::ShaderProgram> loadShaders(const std::string& shaderName,
														        const std::string& vertexPath,
														        const std::string& fragmentPath);
	static std::shared_ptr<RenderEngine::ShaderProgram> getShaderProgram(const std::string& shaderName);
	static std::shared_ptr<RenderEngine::Texture2D> loadTexture(const std::string& textureName, 
		                                                    const std::string& texturePath);
	static std::shared_ptr<RenderEngine::Texture2D> getTexture(const std::string& textureName);
	
	static std::shared_ptr<RenderEngine::Sprite> loadSprite(const std::string& spriteName,
		                                                const std::string& textureName, 
		                                                const std::string& shaderName, 		                                               
		                                                const std::string& subTextureName = "default");
	static std::shared_ptr<RenderEngine::Sprite> getSprite(const std::string& spriteName);
	

	static std::shared_ptr<RenderEngine::Texture2D> loatTextureAtlas(const std::string textureName,
		                                                  const std::string texturePath,
		                                                  const std::vector<std::string> subTextures,
		                                                  const unsigned int subTextureWidth,
		                                                  const unsigned int subTextureHeight);
	//��� �������� ������� �� �������� ���� rapidJson
	static bool loadJSONResources(const std::string& JSONPath);
	//��� ����������� �������
	static const std::vector<std::vector<std::string>>& getLeves() { return m_levels; }

private:
	static std::string getFileString(const std::string& realativeFilePath);
	//std::map� ��� ��������������� ������������� ���������, ���������� ���� ����-�������� 
	//� ����������� �������.
	typedef std::map<const std::string, std::shared_ptr<RenderEngine::ShaderProgram>> ShaderProgramsMap;
	static ShaderProgramsMap m_shaderPrograms;

	typedef std::map<const std::string, std::shared_ptr<RenderEngine::Texture2D>> TexturesMap;
	static TexturesMap m_textures;

	typedef std::map<const std::string, std::shared_ptr<RenderEngine::Sprite>> SpritesMap;
	static SpritesMap m_sprites;	

	//������ ��� �������� �������
	static std::vector<std::vector<std::string>> m_levels;

	static std::string m_path;
};
#include "ResourcMenager.h"
#include "../Renderer/ShaderProgram.h"
#include "../Renderer/Texture2D.h"
#include "../Renderer/Sprite.h"
#include "../Renderer/AnimatedSprite.h"

#include <sstream>
#include <fstream>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h"

//объ€вление статических объектов
ResourceMenager::ShaderProgramsMap  ResourceMenager::m_shaderPrograms;
ResourceMenager::TexturesMap ResourceMenager::m_textures;
ResourceMenager::SpritesMap ResourceMenager::m_sprites;
ResourceMenager::AnimatedSpritesMap ResourceMenager::m_animatedSprites;
std::string ResourceMenager::m_path;

//вместо деструктора
void ResourceMenager::unLoadAllResources()
{
	m_shaderPrograms.clear();
	m_textures.clear();
	m_sprites.clear();
	m_animatedSprites.clear();	
}

// вместо конструктора
void ResourceMenager::setExecutablePath(const std::string& executablePath)
{
	size_t found = executablePath.find_last_of("/\\");
	m_path = executablePath.substr(0, found);
}

std::string ResourceMenager::getFileString(const std::string& realativeFilePath)
{
	std::ifstream f;
	f.open(m_path + "/" + realativeFilePath.c_str(), std::ios::in | std::ios::binary);
	if (!f.is_open())
	{
		std::cerr << "Fail to open file: " << realativeFilePath << std::endl;
		return std::string{};
	}

	std::stringstream buffer;
	buffer << f.rdbuf();

	return buffer.str();
}

std::shared_ptr<Renderer::ShaderProgram> ResourceMenager::loadShaders(const std::string& shaderName, 
	                                                                  const std::string& vertexPath, 
	                                                                  const std::string& fragmentPath)
{	
	std::string vertexString = getFileString(vertexPath);
	if (vertexString.empty())
	{
		std::cerr << "no vertex shader!" << std::endl;
		return nullptr;
	}

	std::string fragmentString = getFileString(fragmentPath);
	if (fragmentString.empty())
	{
		std::cerr << "no fragment shader!" << std::endl;
		return nullptr;
	}

	std::shared_ptr<Renderer::ShaderProgram> newSader;
	newSader = m_shaderPrograms.emplace(shaderName, std::make_shared<Renderer::ShaderProgram>(vertexString, fragmentString)).first->second;
	if (newSader->isCompiled())
	{
		return newSader;
	}

	std::cerr << "Can't load shader program:\n"
		<< "Vertex: " << vertexPath << "\n"
		<< "Fragment: " << fragmentPath << std::endl;

	return nullptr;
}

std::shared_ptr<Renderer::ShaderProgram> ResourceMenager::getShaderProgram(const std::string& shaderName)
{
	ShaderProgramsMap::const_iterator it = m_shaderPrograms.find(shaderName);
	if (it != m_shaderPrograms.end())
	{
		return it->second;
	}
	std::cerr << "Can't find the shader program: " << shaderName << std::endl;
	return nullptr;
}

std::shared_ptr<Renderer::Texture2D> ResourceMenager::loadTexture(const std::string& textureName, const std::string& texturePath)
{
	int channels = 0;
	int width = 0;
	int height = 0;
	//дл€ изменени€ системы координат 
	stbi_set_flip_vertically_on_load(true);
	unsigned char* pixels;
	pixels = stbi_load(std::string(m_path + "/" + texturePath).c_str(), &width, &height, &channels, 0);
	if (!pixels)
	{
		std::cerr << "Can't load image: " << texturePath << std::endl;
		return nullptr;
	}
	std::shared_ptr<Renderer::Texture2D> newtexture = m_textures.emplace(textureName, 
		std::make_shared<Renderer::Texture2D>(width, height, pixels, channels, 
		GL_NEAREST, GL_CLAMP_TO_EDGE)).first->second;

	stbi_image_free(pixels);
	return newtexture;	
}

std::shared_ptr<Renderer::Texture2D> ResourceMenager::getTexture(const std::string& textureName)
{
	TexturesMap::const_iterator it = m_textures.find(textureName);
	if (it != m_textures.end())
	{
		return it->second;
	}
	std::cerr << "Can't find the texsture:" << textureName << std::endl;
	return nullptr;
}

std::shared_ptr<Renderer::Sprite> ResourceMenager::loadSprite(const std::string& spriteName, 
	                                                          const std::string& textureName, 
	                                                          const std::string& shaderName, 
	                                                          const unsigned int spriteWidth, 
	                                                          const unsigned int spriteHeight,
	                                                          const std::string& subTextureName)
{
	auto pTexture = getTexture(textureName);
	if (!pTexture)
	{
		std::cerr << "Can't find the texsture:" << textureName << "for the sprite: " << spriteName << std::endl;
	}

	auto pShader = getShaderProgram(shaderName);
	if (!pTexture)
	{
		std::cerr << "Can't find the shader:" << shaderName << "for the sprite: " << spriteName << std::endl;
	}

	std::shared_ptr<Renderer::Sprite> newSprite = m_sprites.emplace(textureName,
		                              std::make_shared<Renderer::Sprite>(pTexture,
									   subTextureName,
									   pShader,
							           glm::vec2(0.f, 0.f),
		                               glm::vec2(spriteWidth, spriteHeight))).first->second;
	return newSprite;
}

std::shared_ptr<Renderer::AnimatedSprite> ResourceMenager::loadAnimatedSprite(const std::string& spriteName,
	                                                       const std::string& textureName,
	                                                       const std::string& shaderName,
	                                                       const unsigned int spriteWidth,
	                                                       const unsigned int spriteHeight,
	                                                       const std::string& subTextureName)
{
	auto pTexture = getTexture(textureName);
	if (!pTexture)
	{
		std::cerr << "Can't find the texsture:" << textureName << "for the animatedSprite: " << spriteName << std::endl;
	}

	auto pShader = getShaderProgram(shaderName);
	if (!pShader)
	{
		std::cerr << "Can't find the shader:" << shaderName << "for the animatedSprite: " << spriteName << std::endl;
	}

	std::shared_ptr<Renderer::AnimatedSprite> newSprite = m_animatedSprites.emplace(spriteName,
		                                    std::make_shared<Renderer::AnimatedSprite>(pTexture,
			                                subTextureName,
			                                pShader,
			                                glm::vec2(0.f, 0.f),
			                                glm::vec2(spriteWidth, spriteHeight))).first->second;
	return newSprite;
}


std::shared_ptr<Renderer::Sprite> ResourceMenager::getSprite(const std::string& spriteName)
{
	SpritesMap::const_iterator it = m_sprites.find(spriteName);
	if (it != m_sprites.end())
	{
		return it->second;
	}
	std::cerr << "Can't find the sprite:" << spriteName << std::endl;
	return nullptr;
}

std::shared_ptr<Renderer::AnimatedSprite> ResourceMenager::getAnimatedSprite(const std::string& spriteName)
{
	AnimatedSpritesMap::const_iterator it = m_animatedSprites.find(spriteName);
	if (it != m_animatedSprites.end())
	{
		return it->second;
	}
	std::cerr << "Can't find the animatedSprite:" << spriteName << std::endl;
	return nullptr;
}

std::shared_ptr<Renderer::Texture2D> ResourceMenager::loatTextureAtlas(const std::string textureName, 
	                                                                   const std::string texturePath, 
	                                                         const std::vector<std::string> subTextures, 
	                                                         const unsigned int subTextureWidth, 
	                                                         const unsigned int subTextureHeight)
{
	auto pTexture = loadTexture(std::move(textureName), std::move(texturePath));
	if (pTexture)
	{
		const unsigned int textureWidth = pTexture->width();
		const unsigned int textureHeight = pTexture->height();
		unsigned int currentTextureOffsetX = 0;
		unsigned int currentTextureOffsetY = textureHeight;
		for  (const auto& currentSubTextureName : subTextures)
		{
			glm::vec2 leftBottomUV(static_cast<float>(currentTextureOffsetX) / textureWidth, static_cast<float>(currentTextureOffsetY - subTextureHeight) / textureHeight);
			glm::vec2 rightTopUV(static_cast<float>(currentTextureOffsetX + subTextureWidth) / textureWidth, static_cast<float>(currentTextureOffsetY) / textureHeight);
			pTexture->addSubTexture(std::move(currentSubTextureName), leftBottomUV, rightTopUV);
			
			currentTextureOffsetX += subTextureWidth;
			if (currentTextureOffsetX >= textureWidth)
			{
				currentTextureOffsetX = 0;
				currentTextureOffsetY -= subTextureHeight;
			}
		}
	}
	return pTexture;
}


#include "ResourcMenager.h"
#include "../Renderer/ShaderProgram.h"
#include "../Renderer/Texture2D.h"
#include "../Renderer/Sprite.h"

#include <sstream>
#include <fstream>
#include <iostream>

#include <rapidjson/document.h>
#include <rapidjson/error/en.h>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h"

//объявление статических объектов
ResourceMenager::ShaderProgramsMap  ResourceMenager::m_shaderPrograms;
ResourceMenager::TexturesMap ResourceMenager::m_textures;
ResourceMenager::SpritesMap ResourceMenager::m_sprites;
std::string ResourceMenager::m_path;
std::vector<std::vector<std::string>> ResourceMenager::m_levels;

//вместо деструктора
void ResourceMenager::unLoadAllResources()
{
	m_shaderPrograms.clear();
	m_textures.clear();
	m_sprites.clear();		
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

std::shared_ptr<RenderEngine::ShaderProgram> ResourceMenager::loadShaders(const std::string& shaderName, 
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

	std::shared_ptr<RenderEngine::ShaderProgram> newSader;
	newSader = m_shaderPrograms.emplace(shaderName, std::make_shared<RenderEngine::ShaderProgram>(vertexString, fragmentString)).first->second;
	if (newSader->isCompiled())
	{
		return newSader;
	}

	std::cerr << "Can't load shader program:\n"
		<< "Vertex: " << vertexPath << "\n"
		<< "Fragment: " << fragmentPath << std::endl;

	return nullptr;
}

std::shared_ptr<RenderEngine::ShaderProgram> ResourceMenager::getShaderProgram(const std::string& shaderName)
{
	ShaderProgramsMap::const_iterator it = m_shaderPrograms.find(shaderName);
	if (it != m_shaderPrograms.end())
	{
		return it->second;
	}
	std::cerr << "Can't find the shader program: " << shaderName << std::endl;
	return nullptr;
}

std::shared_ptr<RenderEngine::Texture2D> ResourceMenager::loadTexture(const std::string& textureName, const std::string& texturePath)
{
	int channels = 0;
	int width = 0;
	int height = 0;
	//для изменения системы координат 
	stbi_set_flip_vertically_on_load(true);
	unsigned char* pixels;
	pixels = stbi_load(std::string(m_path + "/" + texturePath).c_str(), &width, &height, &channels, 0);
	if (!pixels)
	{
		std::cerr << "Can't load image: " << texturePath << std::endl;
		return nullptr;
	}
	std::shared_ptr<RenderEngine::Texture2D> newtexture = m_textures.emplace(textureName, 
		std::make_shared<RenderEngine::Texture2D>(width, height, pixels, channels, 
		GL_NEAREST, GL_CLAMP_TO_EDGE)).first->second;

	stbi_image_free(pixels);
	return newtexture;	
}

std::shared_ptr<RenderEngine::Texture2D> ResourceMenager::getTexture(const std::string& textureName)
{
	TexturesMap::const_iterator it = m_textures.find(textureName);
	if (it != m_textures.end())
	{
		return it->second;
	}
	std::cerr << "Can't find the texsture:" << textureName << std::endl;
	return nullptr;
}

std::shared_ptr<RenderEngine::Sprite> ResourceMenager::loadSprite(const std::string& spriteName, 
	                                                          const std::string& textureName, 
	                                                          const std::string& shaderName, 	                                                         
	                                                          const std::string& subTextureName)
{
	auto pTexture = getTexture(textureName);
	if (!pTexture)
	{
		std::cerr << "Can't find the texsture:" << textureName << "for the sprite: " << spriteName << std::endl;
	}

	auto pShader = getShaderProgram(shaderName);
	if (!pShader)
	{
		std::cerr << "Can't find the shader:" << shaderName << "for the sprite: " << spriteName << std::endl;
	}

	std::shared_ptr<RenderEngine::Sprite> newSprite = m_sprites.emplace(spriteName,
		                              std::make_shared<RenderEngine::Sprite>(pTexture,
									                                         subTextureName,
									                                         pShader)).first->second;
	return newSprite;
}



std::shared_ptr<RenderEngine::Sprite> ResourceMenager::getSprite(const std::string& spriteName)
{
	SpritesMap::const_iterator it = m_sprites.find(spriteName);
	if (it != m_sprites.end())
	{
		return it->second;
	}
	std::cerr << "Can't find the sprite:" << spriteName << std::endl;
	return nullptr;
}

std::shared_ptr<RenderEngine::Texture2D> ResourceMenager::loatTextureAtlas(const std::string textureName, 
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
			//+ 0.01f немнго изменеили размер текстуры для проподания накладывания соседних саб текстур
			glm::vec2 leftBottomUV(static_cast<float>(currentTextureOffsetX + 0.01f) / textureWidth, static_cast<float>(currentTextureOffsetY - subTextureHeight + 0.01f) / textureHeight);
			glm::vec2 rightTopUV(static_cast<float>(currentTextureOffsetX + subTextureWidth - 0.01f) / textureWidth, static_cast<float>(currentTextureOffsetY - 0.01f) / textureHeight);
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

bool ResourceMenager::loadJSONResources(const std::string& JSONPath)
{
	//создание строки
	const std::string JSONString = getFileString(JSONPath);
	//проверка наличия файла
	if (JSONString.empty())
	{
		std::cerr << "No JSON resources file!" << std::endl; 
		return false;
	}

	//создание документа
	rapidjson::Document document;
	rapidjson::ParseResult parseResult = document.Parse(JSONString.c_str());   //Parse - Разобрать
	if (!parseResult)
	{
		std::cerr << "JSON parse error!" << rapidjson::GetParseError_En(parseResult.Code()) 
			                             << "(" << parseResult.Offset() << ")" << std::endl;
		std::cerr << "In JSON file: " << JSONPath << std::endl;
		return false;
	}

	//вынимаем из файла данные по ключу
	auto shadersIt = document.FindMember("shaders"); //FindMember - Найти участника
	if (shadersIt != document.MemberEnd())
	{
		for (const auto& currentShader : shadersIt->value.GetArray())
		{
			//созаем переменную строки(для считывания в них данных из файла JSON)
			const std::string name = currentShader["name"].GetString();
			const std::string filePath_v = currentShader["filePath_v"].GetString();
			const std::string filePath_f = currentShader["filePath_f"].GetString();
			//загружаем шейдеры
			loadShaders(name, filePath_v, filePath_f);
		}
	}

	// вынимаем из файла данные по ключу (текстурный атлас)
	auto textureAtlasesIt = document.FindMember("textureAtlases"); //FindMember - Найти участника
	if (textureAtlasesIt != document.MemberEnd())
	{
		for(const auto& currentTextureAtlas : textureAtlasesIt->value.GetArray())
		{
			//создаем переменные для считывания в них данных из файла JSON
			const std::string name = currentTextureAtlas["name"].GetString();
			const std::string filePath = currentTextureAtlas["filePath"].GetString();
			const unsigned int subTextureWidht = currentTextureAtlas["subTextureWidth"].GetUint();
			const unsigned int subTextureHeight = currentTextureAtlas["subTextureHeight"].GetUint();

			//создание массива для хранения саб текстур
			const auto subTexturesArray = currentTextureAtlas["subTextures"].GetArray();
			std::vector<std::string> subTextures;
			subTextures.reserve(subTexturesArray.Size());
			//заполняем массив
			for (const auto& currentSubTexture : subTexturesArray)
			{
				subTextures.emplace_back(currentSubTexture.GetString());
			}
			//загрузка саб текстур
			loatTextureAtlas(name, filePath, std::move(subTextures), subTextureWidht, subTextureHeight);
		}
	}

	//загрузка из файла данные по ключу спрайта
	auto spritesIt = document.FindMember("sprites"); //FindMember - Найти участника( по имени)
	if (spritesIt != document.MemberEnd())
	{
		//если документ не пустой считываем данные
		for (const auto& currentSprite : spritesIt->value.GetArray())
		{
			//создаем переменные для считывания в них данных из файла JSON
			const std::string name = currentSprite["name"].GetString();
			const std::string textureAtlas = currentSprite["textureAtlas"].GetString();
			const std::string shader = currentSprite["shader"].GetString();
			//const unsigned int initialWidth = currentAnimatedSprite["initialWidth"].GetUint();
			//const unsigned int initialHeight = currentAnimatedSprite["initialHeight"].GetUint();
			const std::string subTexture = currentSprite["initialSubTexture"].GetString();

			//загрузка анимации
			auto pSprite = loadSprite(name, textureAtlas, shader, subTexture);
			if (!pSprite)
			{
				continue;
			}	
			//проверяю есть ли такой эдемент как frames
			auto framesIt = currentSprite.FindMember("frames");
			if (framesIt != currentSprite.MemberEnd())
			{
				const auto framesArray = framesIt->value.GetArray();
				//для хрнения описаний кадров
				std::vector<RenderEngine::Sprite::FrameDescription> frameDescriptions;
				frameDescriptions.reserve(framesArray.Size());
				for (const auto& currentFrame : framesArray)
				{
					//создаем переменные для считывания в них данных из файла JSON
					const std::string subTextureStr = currentFrame["subTexture"].GetString();
					const double duration = currentFrame["duration"].GetDouble();
					//получение координат из саб текстуры
					const auto pTextureAtlas = getTexture(textureAtlas);
					const auto pSubtexture = pTextureAtlas->getSubTexture(subTextureStr);
					//записываю в массив данные
					frameDescriptions.emplace_back(pSubtexture.leftBottomUV, pSubtexture.rightTopUV, duration);
				}
				pSprite->insertFrames(std::move(frameDescriptions));
			}
		}
	}

	// вынимаем из файла данные по ключу (levels карта)
	auto levelsIt = document.FindMember("levels"); //FindMember - Найти участника
	if (levelsIt != document.MemberEnd())
	{
		for (const auto& currentLevels : levelsIt->value.GetArray())
		{
			//создание массива для хранения саб текстур
			const auto description = currentLevels["description"].GetArray();
			std::vector<std::string> levelRows;
			//зарезервировать размер массива
			levelRows.reserve(description.Size());
			//максимальный размер строки
			size_t maxLength = 0;

			//заполняем массив
			for (const auto& currentRow : description)
			{
				levelRows.emplace_back(currentRow.GetString());
				//если максимальная длина меньше текущей длины страки то приравнивать
				if (maxLength < levelRows.back().length())
				{
					maxLength = levelRows.back().length();
				}
			}
			//цикл для заполнения пустых блоков
			for (auto& currentRow : levelRows)
			{
				while (currentRow.length() < maxLength)
				{
					//добавление пустого объекта
					currentRow.append("D");
				}
			}
			//сохраняем загруженную карту
			m_levels.emplace_back(std::move(levelRows));
		}
	}
	return true;
}


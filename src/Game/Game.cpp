#include "Game.h"

#include "../Resources/ResourcMenager.h"
#include "../Renderer/ShaderProgram.h"
#include "../Renderer/Texture2D.h"
#include "../Renderer/Sprite.h"
#include "../Renderer/AnimatedSprite.h"

#include "GameObjects/Tank.h"
#include "Level.h"

#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

Game::Game(const glm::ivec2& windowSize)
	:m_eCurrentGameState(EGameState::Active)
    , m_windowSize(windowSize)
{
	m_keys.fill(false);
}

Game::~Game()
{
}

void Game::render()
{
    //проверяем если танк?
    if (m_pTank)
    {
        m_pTank->render();
    }    

    //если карта
    if (m_pLevel)
    {
        m_pLevel->render();
    }
}

void Game::update(const uint64_t delta)
{
    if (m_pLevel)
    {
        m_pLevel->update(delta);
    }
    //проверяем если танк?  
    if (m_pTank)
    {
        //обработка нажатий клавишь для движения танка
        if (m_keys[GLFW_KEY_W])
        {
            m_pTank->setOrientation(Tank::EOrientation::Top);
            //разрешаем двдение
            m_pTank->move(true);
        }
        else if (m_keys[GLFW_KEY_A])
        {
            m_pTank->setOrientation(Tank::EOrientation::Left);
            //разрешаем двдение
            m_pTank->move(true);
        }
        else if (m_keys[GLFW_KEY_D])
        {
            m_pTank->setOrientation(Tank::EOrientation::Right);
            //разрешаем двдение
            m_pTank->move(true);
        }
        else if (m_keys[GLFW_KEY_S])
        {
            m_pTank->setOrientation(Tank::EOrientation::Bottom);
            //разрешаем двдение
            m_pTank->move(true);
        }
        else
        {
            m_pTank->move(false);
        }
        m_pTank->update(delta);
    }    
}

void Game::setKey(const int key, const int action)
{
	m_keys[key] = action;
}

bool Game::init()
{
    ResourceMenager::loadJSONResources("res/resources.json");
       
    //
    auto pSpriteShaderProgram = ResourceMenager::getShaderProgram("spriteShader");

    if (!pSpriteShaderProgram)
    {
        std::cerr << "Can't creat shader program: " << "spriteShader" << std::endl;
        return false;
    }
      
    //auto pTextureAtlas = ResourceMenager::loatTextureAtlas("DefaultTextureAtlas", "res/textures/map_16x16.png", std::move(subTexturesNames), 16, 16);
    auto pTextureAtlas = ResourceMenager::getTexture("mapTextureAtlas");
    if (!pTextureAtlas)
    {
        std::cerr << "Can't find texture atlas: " << "mapTextureAtlas" << std::endl;
        return false;
    }

    auto pTanksTextureAtlas = ResourceMenager::getTexture("tanksTextureAtlas");
    if (!pTanksTextureAtlas)
    {
        std::cerr << "Can't find texture atlas: " << "tanksTextureAtlas" << std::endl;
        return false;
    }

    
    //использование функции для отоброжения объекта(проекционная матрица)
    glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(m_windowSize.x), 0.f, static_cast<float>(m_windowSize.y), -100.f, 100.f);

    //pDefaultShaderProgram->setMatrix4("projectionMat", projectionMatrix);

    pSpriteShaderProgram->use();
    pSpriteShaderProgram->setInt("tex", 0);
    pSpriteShaderProgram->setMatrix4("projectionMat", projectionMatrix);

    //илнициализация танка   
    
    auto pTanksAnimatedSprite = ResourceMenager::getAnimatedSprite("tankAnimatedSprite");
    if (!pTanksAnimatedSprite)
    {
        std::cerr << "Can't find animated sprite: " << "tankAnimatedSprite" << std::endl;
        return false;
    }   

    m_pTank = std::make_unique<Tank>(pTanksAnimatedSprite, 0.0000001f, glm::vec2(0), glm::vec2(16.f, 16.f));

    //загрузка уровня
    m_pLevel = std::make_unique<Level>(ResourceMenager::getLeves()[0]);

	return true;
}

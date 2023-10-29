#include "Game.h"

#include "../Resources/ResourcMenager.h"
#include "../Renderer/ShaderProgram.h"
#include "../Renderer/Texture2D.h"
#include "../Renderer/Sprite.h"
#include "../Renderer/AnimatedSprite.h"

#include "Tank.h"

#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

Game::Game(const glm::ivec2& windowSize)
	:m_currentGameState(GameState::Active)
    , m_windowSize(windowSize)
{
	m_keys.fill(false);
}

Game::~Game()
{
}

void Game::render()
{
   ResourceMenager::getAnimatedSprite("NewAnimatedSprite")->render();

    //проверяем если танк?
    if (m_pTank)
    {
        m_pTank->render();
    }    
}

void Game::update(const uint64_t delta)
{
   ResourceMenager::getAnimatedSprite("NewAnimatedSprite")->update(delta);
   
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
            m_pTank->setOrientation(Tank::EOrientation::Botton);
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
    auto pDefaultShaderProgram = ResourceMenager::loadShaders("DefauldShader",
                                                              "res/shaders/vertex.txt",
                                                              "res/shaders/fragment.txt");
    if (!pDefaultShaderProgram)
    {
        std::cerr << "Can't creat shader program: " << "DefauldShader" << std::endl;
        return false;
    }

    auto pSpriteShaderProgram = ResourceMenager::loadShaders("SpriteShader",
                                                             "res/shaders/vSprite.txt",
                                                             "res/shaders/fSprite.txt");
    if (!pSpriteShaderProgram)
    {
        std::cerr << "Can't creat shader program: " << "SpriteShader" << std::endl;
        return false;
    }

    auto tex = ResourceMenager::loadTexture("DefaultTexture", "res/textures/map_16x16.png");

    std::vector<std::string> subTexturesNames = {
        "block",
        "topBlock",
        "bottomBlock",
        "leftBlock",
        "rightBlock",
        "topLeftBlock",
        "topRightBlock",
        "bottomLeftBlock",

        "bottomRightBlock",
        "beton",
        "topBeton",
        "bottombeton",
        "leftBeton",
        "rightBeton",
        "topLeftBeton",
        "topRightBeton",

        "botomLeftBeton",
        "botomRightBeton",
        "water1",
        "water2",
        "water3",
        "trees",
        "ice",
        "wall",

        "eagle",
        "deadEagle",
        "nothing",
        "respawn1",
        "respawn2",
        "respawn3",
        "respawn4" };

    auto pTextureAtlas = ResourceMenager::loatTextureAtlas("DefaultTextureAtlas", "res/textures/map_16x16.png", std::move(subTexturesNames), 16, 16);
    
    auto pAnimatedSprite = ResourceMenager::loadAnimatedSprite("NewAnimatedSprite", "DefaultTextureAtlas", "SpriteShader", 100, 100, "beton");
    pAnimatedSprite->setPosition(glm::vec2(300, 300));
    //создание вектора для анимации
    std::vector<std::pair<std::string, uint64_t>> waterState;
    waterState.emplace_back(std::make_pair<std::string, uint64_t>("water1", 500000000));
    waterState.emplace_back(std::make_pair<std::string, uint64_t>("water2", 500000000));
    waterState.emplace_back(std::make_pair<std::string, uint64_t>("water3", 500000000));

    std::vector<std::pair<std::string, uint64_t>> eagleState;
    eagleState.emplace_back(std::make_pair<std::string, uint64_t>("eagle", 1000000000));
    eagleState.emplace_back(std::make_pair<std::string, uint64_t>("deadEagle", 1000000000));

    pAnimatedSprite->insertState("waterState", std::move(waterState));
    pAnimatedSprite->insertState("eagleState", std::move(eagleState));

    pAnimatedSprite->setState("waterState");

    pDefaultShaderProgram->use();
    pDefaultShaderProgram->setInt("tex", 0);

    //создание единичной матрицы
    glm::mat4 modelMatri_1 = glm::mat4(1.f);
    //использование функции для перемещения объекта
    modelMatri_1 = glm::translate(modelMatri_1, glm::vec3(100.f, 50.f, 0.f));

    glm::mat4 modelMatri_2 = glm::mat4(1.f);
    modelMatri_2 = glm::translate(modelMatri_2, glm::vec3(500.f, 50.f, 0.f));

    //использование функции для отоброжения объекта(проекционная матрица)
    glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(m_windowSize.x), 0.f, static_cast<float>(m_windowSize.y), -100.f, 100.f);

    pDefaultShaderProgram->setMatrix4("projectionMat", projectionMatrix);

    pSpriteShaderProgram->use();
    pSpriteShaderProgram->setInt("tex", 0);
    pSpriteShaderProgram->setMatrix4("projectionMat", projectionMatrix);

    //илнициализация танка
   
    std::vector<std::string> TanksSubTexturesNames = {
       "TankTop1",
       "TankTop2",
       "TankLeft1",
       "TankLeft2",
       "TankBotton1",
       "TankBotton2",
       "TankRight1",
       "TankRight2"
    };
    auto pTanksTextureAtlas = ResourceMenager::loatTextureAtlas("TanksTextureAtlas",
        "res/textures/tanks.png", std::move(TanksSubTexturesNames), 16, 16);

    auto pTanksAnimatedSprite = ResourceMenager::loadAnimatedSprite("TanksAnimatedSprite", "TanksTextureAtlas", "SpriteShader", 100, 100, "TankTop1");
   // pAnimatedSprite->setPosition(glm::vec2(300, 300));

    std::vector<std::pair<std::string, uint64_t>> tankTopState;
    tankTopState.emplace_back(std::make_pair<std::string, uint64_t>("TankTop1", 500000000));
    tankTopState.emplace_back(std::make_pair<std::string, uint64_t>("TankTop2", 500000000));

    std::vector<std::pair<std::string, uint64_t>> tankBottonState;
    tankBottonState.emplace_back(std::make_pair<std::string, uint64_t>("TankBotton1", 500000000));
    tankBottonState.emplace_back(std::make_pair<std::string, uint64_t>("TankBotton2", 500000000));

    std::vector<std::pair<std::string, uint64_t>> tankLeftState;
    tankLeftState.emplace_back(std::make_pair<std::string, uint64_t>("TankLeft1", 500000000));
    tankLeftState.emplace_back(std::make_pair<std::string, uint64_t>("TankLeft2", 500000000));

    std::vector<std::pair<std::string, uint64_t>> tankRightState;
    tankRightState.emplace_back(std::make_pair<std::string, uint64_t>("TankRight1", 500000000));
    tankRightState.emplace_back(std::make_pair<std::string, uint64_t>("TankRight2", 500000000));

    pTanksAnimatedSprite->insertState("tankTopState", std::move(tankTopState));
    pTanksAnimatedSprite->insertState("tankBottonState", std::move(tankBottonState));
    pTanksAnimatedSprite->insertState("tankLeftState", std::move(tankLeftState));
    pTanksAnimatedSprite->insertState("tankRightState", std::move(tankRightState));

    //начальное состояние
    pTanksAnimatedSprite->setState("tankTopState");

    m_pTank = std::make_unique<Tank>(pTanksAnimatedSprite, 0.0000001f, glm::vec2(100.f, 100.f));

	return true;
}

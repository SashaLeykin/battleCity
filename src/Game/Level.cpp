#include "Level.h"

#include "GameObjects/BrickWall.h"
#include "GameObjects/BetonWall.h"

#include <iostream>

//константную переменную размер блока
const unsigned int BLOCK_SIZE = 16;

//функция createGameObjectFromDescription - создать игровой объект из описания(по блокам)
std::shared_ptr<IGameObject> createGameObjectFromDescription(const char description,
															 const glm::vec2& position, 
                                                             const glm::vec2 size,
															 const float rotation)
{
	switch (description)
	{
    case '0':        
        return std::make_shared<BrickWall>(BrickWall::EBrickWallType::Right, position, size, rotation);
    case '1':
        return std::make_shared<BrickWall>(BrickWall::EBrickWallType::Bottom, position, size, rotation);
    case '2':
        return std::make_shared<BrickWall>(BrickWall::EBrickWallType::Left, position, size, rotation);
    case '3':
        return std::make_shared<BrickWall>(BrickWall::EBrickWallType::Top, position, size, rotation);
    case '4':
        return std::make_shared<BrickWall>(BrickWall::EBrickWallType::All, position, size, rotation);
    case 'G':
        return std::make_shared<BrickWall>(BrickWall::EBrickWallType::BottomLeft, position, size, rotation);
    case 'H':
        return std::make_shared<BrickWall>(BrickWall::EBrickWallType::BottomRight, position, size, rotation);
    case 'I':
        return std::make_shared<BrickWall>(BrickWall::EBrickWallType::TopLeft, position, size, rotation);
    case 'J':
        return std::make_shared<BrickWall>(BrickWall::EBrickWallType::TopRight, position, size, rotation);

    case '5':
        return std::make_shared<BetonWall>(BetonWall::EBetonWallType::Right, position, size, rotation);
    case '6':
        return std::make_shared<BetonWall>(BetonWall::EBetonWallType::Bottom, position, size, rotation);
    case '7':
        return std::make_shared<BetonWall>(BetonWall::EBetonWallType::Left, position, size, rotation);
    case '8':
        return std::make_shared<BetonWall>(BetonWall::EBetonWallType::Top, position, size, rotation);
    case '9':
        return std::make_shared<BetonWall>(BetonWall::EBetonWallType::All, position, size, rotation);

    case 'D':
        return nullptr;
    default:
        std::cerr << "Unknown GameObject description: " << description << std::endl;
        break;
	}
    return nullptr;
}


Level::Level(const std::vector<std::string>& levelDescription)
{
    if (levelDescription.empty())
    {
        std::cerr << "Empty level description! Описание пустого уровня!" << std::endl;
    }

    //задаем длину и ширину карты (ширина = размер строки, длина размер вектора(кол-во строк))
    m_width = levelDescription[0].length();
    m_height = levelDescription.size();
    //резервируем место в массиве
    m_levelObjects.reserve(m_width * m_height);
    //создаем переменную для хранения текущего нижнего значения
    unsigned int currentBottomOffset = static_cast<unsigned int>(BLOCK_SIZE * (m_height - 1));
    //считывание  массива карты(проход по строкам)
    for (const std::string currentRow : levelDescription)
    {
        unsigned int currentLeftOffset = 0;
        //проход по каэдой букве в строке
        for (const char currentElement : currentRow)
        {
            //в хависимости от знака записывается в массив для хранения игровых объектов
            m_levelObjects.emplace_back(createGameObjectFromDescription(currentElement, 
                                                                glm::vec2(currentLeftOffset, currentBottomOffset), 
                                                                glm::vec2(BLOCK_SIZE, BLOCK_SIZE), 0.f));
            currentLeftOffset += BLOCK_SIZE;
        }
        currentBottomOffset -= BLOCK_SIZE;
    }

}

void Level::render() const
{
    //проход по всем игровым объектам
    for (const auto currentLevelObject : m_levelObjects)
    {
        //если массив не пустой рисуем карту
        if (currentLevelObject)
        {
            currentLevelObject->render();
        }
    }
}

void Level::update(const uint64_t delta)
{
    for (const auto& currentLevelObject : m_levelObjects)
    {
        if (currentLevelObject)
        {
            currentLevelObject->update(delta);
        }
    }
}

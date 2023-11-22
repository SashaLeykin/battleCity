#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <string>
#include <memory>

#include <glm/vec2.hpp>

class IGameObject;

class Level {
public:		
	//константную переменную размер блока
	static constexpr unsigned int BLOCK_SIZE = 16;

	//консруктор принимает описание уровня
	Level(const std::vector<std::string>& levelDescription);
	void render() const;
	void update(const uint64_t delta);

	size_t getLevelWidth() const;
	size_t getLevelHeight() const;

	//для получения конкретной позиции появления
	const glm::ivec2& getPlayerRespawn_1() const { return m_playerRespawn_1; }
	const glm::ivec2& getPlayerRespawn_2() const { return m_playerRespawn_2; }
	const glm::ivec2& getEnemyRespawn_1() const { return m_enemyRespawn_1; }
	const glm::ivec2& getEnemyRespawn_2() const { return m_enemyRespawn_2; }
	const glm::ivec2& getEnemyRespawn_3() const { return m_enemyRespawn_3; }

private:
	//размер карты(уровня)
	size_t m_width = 0;
	size_t m_height = 0;

	//для хранения танков на карте в начале игры
	glm::ivec2 m_playerRespawn_1;	
	glm::ivec2 m_playerRespawn_2;
	glm::ivec2 m_enemyRespawn_1;
	glm::ivec2 m_enemyRespawn_2;
	glm::ivec2 m_enemyRespawn_3;

	//масив для хранения игровых объектов
	std::vector<std::shared_ptr<IGameObject>> m_levelObjects;
};

#endif // !LEVEL_H

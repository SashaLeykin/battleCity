#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <string>
#include <memory>

class IGameObject;

class Level {
public:		
	//консруктор принимает описание уровня
	Level(const std::vector<std::string>& levelDescription);
	void render() const;
	void update(const uint64_t delta);


private:
	//размер карты(уровня)
	size_t m_width = 0;
	size_t m_height = 0;

	//масив для хранения игровых объектов
	std::vector<std::shared_ptr<IGameObject>> m_levelObjects;
};

#endif // !LEVEL_H

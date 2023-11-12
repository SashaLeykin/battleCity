//#pragma once
#ifndef IGAMEOBJECT_H
#define IGAMEOBJECT_H

#include <glm/vec2.hpp>

class IGameObject {
public:
	//конструктор будет принимать позицию объекта
	IGameObject(const glm::vec2& position, const glm::vec2& size, const float rotation);

	//виртуальная
	virtual void render() const = 0;
	virtual void update(const uint64_t delta) = 0;
	//деструктор
	virtual ~IGameObject();

protected:
	//переменные для классов детей
	glm::vec2 m_position;
	glm::vec2 m_size;
	float m_rotation;
};

#endif // !IGAMEOBJECT_H



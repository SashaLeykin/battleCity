//#pragma once
#ifndef IGAMEOBJECT_H
#define IGAMEOBJECT_H

#include <glm/vec2.hpp>

class IGameObject {
public:
	//конструктор будет принимать позицию объекта
	IGameObject(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer);

	//виртуальная
	virtual void render() const = 0;
	virtual void update(const double delta) {};
	//деструктор
	virtual ~IGameObject();

	//запрос позиции
	virtual glm::vec2& getCurrentPosition() { return m_position; }
	// запрос направления на объект
	virtual glm::vec2& getCurrentDirection() { return m_direction; }
	//запрос скорости
	virtual double  getCurrentVelocity() { return m_velocity; }
	//задать скорость
	virtual void setVelocity(const double velocity);

protected:
	//переменные для классов детей
	glm::vec2 m_position;
	glm::vec2 m_size;
	float m_rotation;
	//для создания слоев
	float m_layer;
	//вектор направления на объект
	glm::vec2 m_direction;
	//скорость
	double m_velocity;
};

#endif // !IGAMEOBJECT_H



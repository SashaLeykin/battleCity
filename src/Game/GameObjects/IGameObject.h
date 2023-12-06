//#pragma once
#ifndef IGAMEOBJECT_H
#define IGAMEOBJECT_H

#include <glm/vec2.hpp>

#include "../../Physics/PhysicsEngine.h"

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
	//
	const glm::vec2& getSize() const { return m_size; }
	//коллизии
	const std::vector<Physics::AABB>& getColliders() const { return m_colliders; }

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
	//прямоугольники для колизии(столкновение
	std::vector<Physics::AABB> m_colliders;
};

#endif // !IGAMEOBJECT_H



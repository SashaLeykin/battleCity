//#pragma once
#ifndef IGAMEOBJECT_H
#define IGAMEOBJECT_H

#include <glm/vec2.hpp>

#include "../../Physics/PhysicsEngine.h"

class IGameObject {
public:
	//��� ��������������� ����� ������� ����� �������������
	enum class EObjectType {
		BettonWall,
		Border, //�������
		BrickWall,
		Bullet,
		Eagle,
		Ice, //���
		Tank,
		Tress,
		Water,

		Uncnown //�����������
	};

	//����������� ����� ��������� ������� �������
	IGameObject(const EObjectType objectType,const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer);

	//�����������
	virtual void render() const = 0;
	virtual void update(const double delta) {};
	//����������
	virtual ~IGameObject();

	//������ �������
	virtual glm::vec2& getCurrentPosition() { return m_position; }
	// ������ ����������� �� ������
	virtual glm::vec2& getCurrentDirection() { return m_direction; }
	//������ ��������
	virtual double  getCurrentVelocity() { return m_velocity; }
	//������ ��������
	virtual void setVelocity(const double velocity);
	//
	const glm::vec2& getSize() const { return m_size; }
	//��������
	const std::vector<Physics::AABB>& getColliders() const { return m_colliders; }
	//������� ������ ��� ������������
	EObjectType getObjectType() const { return m_eObjectType; }

	virtual bool collides(const EObjectType objectType) { return true; }

	virtual void onCollision() {}

protected:
	//���������� ��� ������� �����
	glm::vec2 m_position;
	glm::vec2 m_size;
	float m_rotation;
	//��� �������� �����
	float m_layer;
	//���������� enum class EObjectType
	EObjectType m_eObjectType;

	//������ ����������� �� ������
	glm::vec2 m_direction;
	//��������
	double m_velocity;
	//�������������� ��� �������(������������
	std::vector<Physics::AABB> m_colliders;
};

#endif // !IGAMEOBJECT_H



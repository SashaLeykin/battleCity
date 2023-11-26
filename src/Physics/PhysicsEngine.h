#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include <unordered_set>
#include <memory>

class IGameObject;

class PhysicsEngine {
public:

	~PhysicsEngine() = delete;
	PhysicsEngine() = delete;
	PhysicsEngine(const PhysicsEngine&) = delete;
	PhysicsEngine& operator= (const PhysicsEngine&) = delete;
	PhysicsEngine& operator=(PhysicsEngine&&) = delete;
	PhysicsEngine(PhysicsEngine&&) = delete;

	static void init();
	//����������� �� �������
	static void terminate(); //terminate - ����������

	static void update(const double delta);
	//��� ���������� ��������
	static void addDynamicGameObject(std::shared_ptr<IGameObject> pGameObject);

private:
	//std::unordered_set� ������������� ���������, ���������� ����� ���������� �������� ���� Key. 
	// �����, ������� � �������� ����� ������� ��������� � ���������� ��������.
	static std::unordered_set<std::shared_ptr<IGameObject>> m_dynamicObjects;
};

#endif // !PHYSICSENGINE_H

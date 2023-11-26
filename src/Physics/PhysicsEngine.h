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
	//уничтодение не нужного
	static void terminate(); //terminate - прекратить

	static void update(const double delta);
	//для добавления объектов
	static void addDynamicGameObject(std::shared_ptr<IGameObject> pGameObject);

private:
	//std::unordered_set— ассоциативный контейнер, содержащий набор уникальных объектов типа Key. 
	// Поиск, вставка и удаление имеют среднюю сложность с постоянным временем.
	static std::unordered_set<std::shared_ptr<IGameObject>> m_dynamicObjects;
};

#endif // !PHYSICSENGINE_H

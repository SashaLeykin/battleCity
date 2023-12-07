#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include <unordered_set>
#include <memory>
#include <vector>

#include <glm/vec2.hpp>

class IGameObject;
class Level;


namespace Physics {

	//структура для определения прямоугольника опоясовающего объект для определения касания
	struct AABB {
		AABB(const glm::vec2& _bottomLeft, const glm::vec2 _topRight)
			: bottomLeft(_bottomLeft)
			, topRight(_topRight)
		{}
		glm::vec2 bottomLeft;
		glm::vec2 topRight;
	};

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
		//доступ физ. движка к объекту карты в ней сохранеется ссылка на текущий уровень
		static void setCurrentLevel(std::shared_ptr<Level> pLevel);

	private:
		//std::unordered_set— ассоциативный контейнер, содержащий набор уникальных объектов типа Key. 
		// Поиск, вставка и удаление имеют среднюю сложность с постоянным временем.
		static std::unordered_set<std::shared_ptr<IGameObject>> m_dynamicObjects;
		//переменная для хранения ссылки на уровень
		static std::shared_ptr<Level>  m_pCurrentLevel;

		//определение столкновения с соседними объектами
		static bool hasIntersection(const std::vector<AABB>& colliders1, const glm::vec2& position1,
			                        const std::vector<AABB>& colliders2, const glm::vec2& position2);
	};

}

#endif // !PHYSICSENGINE_H

#pragma once

#include <glm/vec2.hpp>
#include <array>
#include <memory>

class Tank;
class Level;

class Game {
public:
	Game(const glm::ivec2& windowSize);
	~Game();

	void render();
	//дл€ смены кадров пол€ игры
	void update(const double delta);
	//дл€ надати€ клавишь в игре
	void setKey(const int key, const int action);
	bool init();

	//получить размер текущего уровн€
	size_t getCurrentLevelWidth() const;
	size_t getCurrentLevelHeight() const;
		
private:
	std::array<bool, 349> m_keys;

	//состо€ние игры
	enum class EGameState {
		Active,
		Pause
	};

	//дл€ определени€ размера экрана
	glm::ivec2 m_windowSize;
	//переменна дл€ хранени€ состо€ни€ игры
	EGameState m_eCurrentGameState;
	//std::unique_ptrЧ это интеллектуальный указатель, который владеет другим объектом
	//  и управл€ет им через указатель и удал€ет этот объект, когда он unique_ptr выходит
	//  за пределы области действи€.
	//std::unique_ptr<Tank> m_pTank;
	//измен€ем умный укезатель дл€ подключени€ физака к танку
	std::shared_ptr<Tank> m_pTank;
	//временно указатель не уровень
	std::shared_ptr<Level> m_pLevel;
};
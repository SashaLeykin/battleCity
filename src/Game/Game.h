#pragma once

#include <glm/vec2.hpp>
#include <array>

class Game {
public:
	Game(const glm::ivec2& windowSize);
	~Game();

	void render();
	//для смены кадров поля игры
	void update(const uint64_t delta);
	//для надатия клавишь в игре
	void setKey(const int key, const int action);
	bool init();
		
private:
	std::array<bool, 349> m_keys;

	//состояние игры
	enum class GameState {
		Active,
		Pause
	};

	//для определения размера экрана
	glm::ivec2 m_windowSize;
	//переменна для хранения состояния игры
	GameState m_currentGameState;
};
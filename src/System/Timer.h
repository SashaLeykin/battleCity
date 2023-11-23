#pragma once

#include <functional>

class Timer {
public:
	Timer();

	void update(const double delta);
	void start(const double duration);
	//функция по установке обратного вызова
	void setCallBack(std::function<void()> callback);

private:
	//переменная обратного вызова
	std::function<void()> m_callback;
	//время до истечения таймера
	double m_timeLeft;
	//активен таймер или нет
	bool m_isRunning;
};
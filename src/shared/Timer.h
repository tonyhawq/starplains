#pragma once

#include <chrono>

class Timer
{
public:
	Timer();

	float time();
	void reset();
private:
	std::chrono::high_resolution_clock::time_point start;
};

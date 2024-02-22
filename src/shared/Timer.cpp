#include "Timer.h"

Timer::Timer()
{
	this->start = std::chrono::high_resolution_clock::now();
}

float Timer::time()
{
	std::chrono::duration<float, std::milli> dur = std::chrono::high_resolution_clock::now() - this->start;
	return dur.count();
}

void Timer::reset()
{
	this->start = std::chrono::high_resolution_clock::now();
}

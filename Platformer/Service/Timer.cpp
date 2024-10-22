#include "Timer.h"

Timer::Timer()
{
	::QueryPerformanceFrequency((LARGE_INTEGER*) &_frequency);
	::QueryPerformanceCounter((LARGE_INTEGER*) &_prevCounter);
}

Timer::~Timer()
{

}


void Timer::Update()
{
	int64 currCounter;
	::QueryPerformanceCounter((LARGE_INTEGER*) &currCounter);

	_interval = (currCounter - _prevCounter) / (double)_frequency * 1000;
	_prevCounter = currCounter;
	_accumulator += _interval;
	_frames += 1;

	/*
		
	*/
	if (_accumulator > 1)
	{
		_fps = _frames;
		_frames = 0;
		_accumulator = 0;
	}
		
}

double Timer::GetInterval()
{
	return _interval;
}

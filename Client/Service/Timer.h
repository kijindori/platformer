#pragma once
#include "pch.h"
class Timer
{
public:
	Timer();
	~Timer();

	void Update();
	double GetInterval();

private:
	int64 _frequency = 0;
	double _interval = 0;
	int64 _fps = 0 ;
	int64 _prevCounter = 0;
	int64 _accumulator = 0;
	int64 _frames = 0;
};


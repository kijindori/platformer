#pragma once
#include "Loader.h"
#include "AudioService.h"
#include "Camera.h"
#include "InputHandler.h"
#include "Timer.h"

class Collision;

class Locator
{
public:
	static AudioService* GetAudioService() { return _audioService; }
	static void provideAudioService(AudioService* audioService) { _audioService = audioService; }

	static Loader* GetLoader() { return _loader; }
	static void provideLoader(Loader* loader) { _loader = loader; }

	static InputHandler* GetInputService() { return _input; }
	static void provideInputService(InputHandler* input) { _input = input; }

	static Collision* GetCollisionService() { return _collision; }
	static void provideCollisionService(Collision* collision) { _collision = collision; }

	static Camera* GetCamera() { return _cam; }
	static void provideCamera(Camera* cam) { _cam = cam; }

	static Timer* GetTimer() { return _timer;  }
	static void provideTimer(Timer* timer) { _timer = timer; }

private:
	static AudioService* _audioService;
	static Loader* _loader;
	static InputHandler* _input;
	static Collision* _collision;
	static Camera* _cam;
	static Timer* _timer;
};


#pragma once
#include "Loader.h"
#include "AudioService.h"

#include "InputHandler.h"

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

private:
	static AudioService* _audioService;
	static Loader* _loader;
	static InputHandler* _input;
	static Collision* _collision;
};


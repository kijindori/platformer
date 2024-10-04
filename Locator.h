#pragma once
#include "ImageService.h"
#include "AudioService.h"
#include "TilemapService.h"
#include "InputHandler.h"

class Collision;

class Locator
{
public:
	static AudioService* GetAudioService() { return _audioService; }
	static void provideAudioService(AudioService* audioService) { _audioService = audioService; }

	static ImageService* GetImageService() { return _imageService; }
	static void provideImageService(ImageService* imageService) { _imageService = imageService; }

	static TilemapService* GetTilemapService() { return _tilemapService; }
	static void provideTilemapService(TilemapService* tilemapService) { _tilemapService = tilemapService; }

	static InputHandler* GetInputService() { return _input; }
	static void provideInputService(InputHandler* input) { _input = input; }

	static Collision* GetCollisionService() { return _collision; }
	static void provideCollisionService(Collision* collision) { _collision = collision; }

private:
	static AudioService* _audioService;
	static ImageService* _imageService;
	static TilemapService* _tilemapService;
	static InputHandler* _input;
	static Collision* _collision;
};


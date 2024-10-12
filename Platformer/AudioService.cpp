#include "pch.h"
#include "AudioService.h"

void AudioService::LoadFile(const wstring& path, wstring key)
{
}


void AudioService::SaveFile(const wstring& path, wstring key)
{
}


void* AudioService::Find(wstring key)
{
	return _loader[key];
}

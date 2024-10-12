#pragma once
#include "ResourceService.h"
#include "pch.h"
class AudioService : public ResourceService
{
public:
	virtual ~AudioService() {};
	virtual void LoadFile(const wstring& path, wstring key) override;
	virtual void SaveFile(const wstring& path, wstring key) override;
	virtual void* Find(wstring key);
private:
	unordered_map<wstring, Image*> _loader;
};


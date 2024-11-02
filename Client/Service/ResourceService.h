#pragma once
class ResourceService
{
public:
	virtual ~ResourceService() {}
	virtual void LoadFile(const wstring& path, wstring key) = 0;
	virtual void SaveFile(const wstring& path, wstring key) = 0;
	virtual void* Find(wstring key) = 0;

};


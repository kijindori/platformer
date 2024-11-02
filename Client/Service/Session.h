#pragma once
#include "pch.h"
#include "Player.h"
#include "Scene.h"


class Session
{
public:
	Session(SOCKET socket);
	~Session();

	SOCKET& GetSocket();
	queue<PlayerData*>& GetQueue();
	void UpdateScene(Scene* scene);

	char* GetRecvBuff();
	char* GetSendBuff();

	void Init();
	void RecvId();
	void Recv();
	void Send(BYTE* data, int len);
	
	int32 GetId();

public:
	uint32 _id = 0;
	CRITICAL_SECTION cs;
	queue<PlayerData*> _dataQueue;
	SOCKET _session = INVALID_SOCKET;
	char _recvBuff[1024] = { 0 };
	char _sendBuff[1024] = { 0 };
};


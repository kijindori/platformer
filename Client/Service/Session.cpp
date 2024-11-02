#include "Session.h"
#include "pch.h"



Session::Session(SOCKET socket):_session(socket)
{
	InitializeCriticalSection(&cs);
}

Session::~Session()
{

}

SOCKET& Session::GetSocket()
{
	return _session;
}

queue<PlayerData*>& Session::GetQueue()
{
	return _dataQueue;
}

char* Session::GetRecvBuff()
{
	return _recvBuff;
}

char* Session::GetSendBuff()
{
	return _sendBuff;
}

void Session::UpdateScene(Scene* scene)
{
	EnterCriticalSection(&cs);
	
	while (!_dataQueue.empty())
	{
		PlayerData* playerdata = nullptr;
		playerdata = _dataQueue.front();
		_dataQueue.pop();

		
		if (playerdata->id == GetId())
		{
			delete playerdata;
			continue;
		}
			

		Player* player = reinterpret_cast<Player*>( scene->FindPlayerById(playerdata->id) );
		if (!player)
		{
			player = reinterpret_cast<Player*>(
				scene->Spawn(ActorType::Player, 
					Vec2Int(48, 48),
					Vec2Int(playerdata->x,playerdata->y),
					playerdata->id)
			);
		}
		
		player->SetState((PlayerState)playerdata->state);
		player->SetPos(Vec2Int(playerdata->x, playerdata->y));
		player->SetIndex(playerdata->index);
		player->SetLeft(playerdata->direction < 0);

		delete playerdata;
	}

	LeaveCriticalSection(&cs);
	return;
}

void Session::Init()
{

}

void Session::RecvId()
{
	recv(_session, _recvBuff, sizeof(_recvBuff), 0);
	::memcpy(&_id, _recvBuff, sizeof(_id));
}

void Session::Recv()
{
	recv(_session, _recvBuff, sizeof(_recvBuff), 0);
	
	PlayerData* data = new PlayerData();
	::memcpy(&data->id		 , _recvBuff	 , 4);
	::memcpy(&data->x		 , _recvBuff + 4 , 4);
	::memcpy(&data->y		 , _recvBuff + 8 , 4);
	::memcpy(&data->state	 , _recvBuff + 12, 4);
	::memcpy(&data->index	 , _recvBuff + 16, 4);
	::memcpy(&data->direction, _recvBuff + 20, 4);
	
	EnterCriticalSection(&cs);
	_dataQueue.push(data);
	LeaveCriticalSection(&cs);
	
}

void Session::Send(BYTE* data, int len)
{
	send(_session, (char*)data, len, 0);
}

int32 Session::GetId()
{
	return _id;
}


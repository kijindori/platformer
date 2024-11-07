#include "pch.h"
#include "Collision.h"
#include "Locator.h"

AudioService*	Locator::_audioService			= nullptr;
Loader*			Locator::_loader				= nullptr;
InputHandler*	Locator::_input					= nullptr;
Collision*		Locator::_collision				= nullptr;
Camera*			Locator::_cam					= nullptr;
Timer*			Locator::_timer					= nullptr;
Scene*			Locator::_scene					= nullptr;
Session*		Locator::_session				= nullptr;

unsigned int WINAPI Receive(LPVOID param)
{
    Session* session = Locator::GetSession();
    while (true)
    {
        Sleep(1);
        session->Recv();
    }

    return 0;
}

void Locator::Init(HWND hWnd)
{
    assert( InitSession() );
	Locator::provideLoader( new Loader() );
	Locator::provideInputService( new InputHandler(hWnd) );
	Locator::provideCollisionService( new Collision() );
	Locator::provideTimer( new Timer() );
	Locator::provideScene( new Scene() );
}

bool Locator::InitSession()
{

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        int err = WSAGetLastError();
        return false;
    }

    SOCKET sock = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    InetPton(AF_INET, L"192.168.200.191", &addr.sin_addr.s_addr);

    if (connect(sock, (sockaddr*)&addr, sizeof(addr)) != 0)
    {
        int err = WSAGetLastError();
        return false;
    }
    _session = new Session(sock);

    char buff[20] = "Init Session";
    _session -> Send((BYTE*)buff, 20);
    _session -> RecvId();

    uint32 ret = _beginthreadex(
        NULL,
        0,
        Receive,
        (LPVOID)NULL,
        0,
        0
    );

    if (ret <= 0)
    {
        int err = GetLastError();
        return false;
    }

    return true;
}



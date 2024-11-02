#ifndef PCH_H
#define PCH_H
#pragma comment (lib,"Gdiplus.lib")
#pragma comment (lib,"ws2_32.lib")

// 여기에 미리 컴파일하려는 헤더 추가
#include "framework.h"
#include "Types.h"
#include "Define.h"
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <process.h>
#include <iostream>

#include <vector>
#include <queue>
#include <assert.h>
#include <windows.h>
#include <objidl.h>
#include <algorithm>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <gdiplus.h>


using namespace std;
using namespace Gdiplus;

struct Action
{
    int type;
    int target;
};

struct Param {
    SOCKET session;
    queue<Action*> q;
};
#endif //PCH_H

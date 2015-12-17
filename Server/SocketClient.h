#pragma once

//WinSock2要在Windows之前引用，否则会出现诸如SOCKADDR_IN重定义的情况
#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
#include <string>
#include <memory>

/*ws2_32.lib是winsock2的库文件
#pragma comment(lib,"ws2_32.lib")表示链接ws2_32.lib这个库文件*/
#pragma comment(lib,"ws2_32.lib")
using namespace std;

class SocketClient
{
public:
	SocketClient(SOCKET client);
	void ReceiveData();
	void CloseSocket();
	friend DWORD WINAPI Receiving(LPVOID lpParamter);

	~SocketClient(void);
private:
	SOCKET client;
};


#pragma once

//WinSock2Ҫ��Windows֮ǰ���ã�������������SOCKADDR_IN�ض�������
#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
#include <string>
#include <memory>

/*ws2_32.lib��winsock2�Ŀ��ļ�
#pragma comment(lib,"ws2_32.lib")��ʾ����ws2_32.lib������ļ�*/
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


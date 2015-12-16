#include "stdafx.h"
#include "SocketClient.h"

SocketClient::SocketClient(SOCKET sock):client(sock)
{
}

void SocketClient::ReceiveData()
{
	HANDLE hThread=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)Receiving,(LPVOID)this,0,NULL);
	CloseHandle(hThread);
}

DWORD WINAPI Receiving(LPVOID lpParamter)
{
	SocketClient *sock=(SocketClient*)lpParamter;
	int len;
	char buf[1024];
	while (true)
	{
		len=recv(sock->client,buf,sizeof(buf),0);
		if(len==-1) //-1非正常退出
		{
			break;
		}
		string recvStr=string(buf,len);
		cout<<recvStr<<endl;
		string sendStr("recv:");
		sendStr+=recvStr;
		strcpy_s(buf,sendStr.c_str());
		send(sock->client,buf,strlen(buf),0);
	}
	if(sock->client!=NULL)
	{
		//closesocket函数用来关闭套接字，执行成功返回0，否则返回SOCKET_ERROR
		closesocket(sock->client);
	}
	cout<<"exit:"<<sock->client<<endl;

	return 0;
}

void SocketClient::CloseSocket()
{
	if(this->client!=NULL)
	{
		closesocket(this->client);
		WSACleanup();
	}
}

SocketClient::~SocketClient(void)
{
	CloseSocket();
}

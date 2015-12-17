// Client.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
#include <string>
#pragma comment(lib,"ws2_32.lib")
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	WORD wVersionRequested=MAKEWORD(2,1);
	WSADATA wsaData; 
	int err;
	err=WSAStartup(wVersionRequested,&wsaData);
	if(err!=0)
	{
		return 0;
	}
	if(LOBYTE(wsaData.wVersion)!=2 || HIBYTE(wsaData.wVersion!=1))
	{
		return 0;
	}
	SOCKET sockClient=socket(AF_INET,SOCK_STREAM,0);
	SOCKADDR_IN addrServer;
	addrServer.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");
	addrServer.sin_family=AF_INET;
	addrServer.sin_port=htons(6000);
	int len=sizeof(SOCKADDR);
	len=connect(sockClient,(SOCKADDR*)&addrServer,len);
	if(len!=0)
	{
		cout<<"connect failed!"<<endl;
	}
	cout<<"connected!"<<endl;
	const int BUF_SIZE=1024;
	char buf[1024];
	while (true)
	{
		cin>>buf;
		send(sockClient,buf,strlen(buf),0);
		len=recv(sockClient,buf,BUF_SIZE,0);
		if(len==-1)
		{
			break;
		}
		string recvStr=string(buf,len);
		cout<<recvStr<<endl;

		Sleep(2000);
	}

	closesocket(sockClient);
	WSACleanup();

	system("PAUSE");
	return 0;
}


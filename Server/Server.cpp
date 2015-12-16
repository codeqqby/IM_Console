// Server.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "SocketClient.h"

int _tmain(int argc, _TCHAR* argv[])
{
	//定义Socket版本，其中高位字节指明副版本、低位字节指明主版本，此处为2.1
	WORD wVersionRequested=MAKEWORD(2,1); 

    //用于存储返回的Socket的版本信息
	WSADATA wsaData; 
	int err;

	//调用WSAStartup函数，操作系统根据请求的Socket版本来搜索相应的Socket库，然后绑定找到的Socket库到该应用程序中
	err=WSAStartup(wVersionRequested,&wsaData);

	//返回值---0:成功;非0:失败
	if(err!=0)
	{
		return 0;
	}

	//LOBYTE取低8位，即低位字节；HIBYTE取高8位，即高位字节
	if(LOBYTE(wsaData.wVersion)!=2 || HIBYTE(wsaData.wVersion!=1))
	{
		return 0;
	}

	/*socket函数用来创建一个能够进行网络通信的套接字;
	参数af指定通信发生的区域：AF_UNIX、AF_INET、AF_NS等，WINDOWS中仅支持AF_INET；
	参数type描述要建立的套接字的类型：TCP流式套接字(SOCK_STREAM)，如TCP、FTP；数据报式套接字(SOCK_DGRAM)，如UDP；原始式套接字(SOCK_RAW)，如IP、ICMP；
	参数protocol说明该套接字使用的特定协议，如果调用者不希望特别指定使用的协议，则置为0，使用默认的连接模式；
	该函数如果调用成功就返回新创建的套接字的描述符，如果失败就返回INVALID_SOCKET。
	*/
	SOCKET sockSever=socket(AF_INET,SOCK_STREAM,0);

	/*SOCKADDR是通用的套接字地址，SOCKADDR_IN是Internet环境下套接字地址；
	二者长度一样，都是16个字节；
	一般情况下，需要把SOCKADDR_IN结构强制转换成SOCKADDR结构再传入系统调用函数中*/
	SOCKADDR_IN addrServer;

	//address family, AF_xxx
	addrServer.sin_family=AF_INET;

	/*Internet address
	htonl函数，host to network long，把主机字节顺序转换为网络字节顺序；
	网络字节顺序，指一个数在内存中存储的时候，高位字节存放于低地址单元，低位字节存放在高地址单元中*/
	addrServer.sin_addr.S_un.S_addr=htonl(INADDR_ANY);

	/*Port number
	htons函数，host to network short，把主机字节顺序转换为网络字节顺序*/
	addrServer.sin_port=htons(6000);

	bind(sockSever,(SOCKADDR*)&addrServer,sizeof(SOCKADDR));
	listen(sockSever,5);

	SOCKADDR_IN addrClient;
	int len=sizeof(SOCKADDR_IN);
	while (true)
	{
		SOCKET client=accept(sockSever,(SOCKADDR*)&addrClient,&len);
		SocketClient *sock=new SocketClient(client);
		sock->ReceiveData();
	}

	//WSACleanup函数用来解除与Socket库的绑定并且释放Socket库所占用的系统资源
	WSACleanup();
	system("PAUSE");

	return 0;
}


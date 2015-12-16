// Server.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "SocketClient.h"

int _tmain(int argc, _TCHAR* argv[])
{
	//����Socket�汾�����и�λ�ֽ�ָ�����汾����λ�ֽ�ָ�����汾���˴�Ϊ2.1
	WORD wVersionRequested=MAKEWORD(2,1); 

    //���ڴ洢���ص�Socket�İ汾��Ϣ
	WSADATA wsaData; 
	int err;

	//����WSAStartup����������ϵͳ���������Socket�汾��������Ӧ��Socket�⣬Ȼ����ҵ���Socket�⵽��Ӧ�ó�����
	err=WSAStartup(wVersionRequested,&wsaData);

	//����ֵ---0:�ɹ�;��0:ʧ��
	if(err!=0)
	{
		return 0;
	}

	//LOBYTEȡ��8λ������λ�ֽڣ�HIBYTEȡ��8λ������λ�ֽ�
	if(LOBYTE(wsaData.wVersion)!=2 || HIBYTE(wsaData.wVersion!=1))
	{
		return 0;
	}

	/*socket������������һ���ܹ���������ͨ�ŵ��׽���;
	����afָ��ͨ�ŷ���������AF_UNIX��AF_INET��AF_NS�ȣ�WINDOWS�н�֧��AF_INET��
	����type����Ҫ�������׽��ֵ����ͣ�TCP��ʽ�׽���(SOCK_STREAM)����TCP��FTP�����ݱ�ʽ�׽���(SOCK_DGRAM)����UDP��ԭʼʽ�׽���(SOCK_RAW)����IP��ICMP��
	����protocol˵�����׽���ʹ�õ��ض�Э�飬��������߲�ϣ���ر�ָ��ʹ�õ�Э�飬����Ϊ0��ʹ��Ĭ�ϵ�����ģʽ��
	�ú���������óɹ��ͷ����´������׽��ֵ������������ʧ�ܾͷ���INVALID_SOCKET��
	*/
	SOCKET sockSever=socket(AF_INET,SOCK_STREAM,0);

	/*SOCKADDR��ͨ�õ��׽��ֵ�ַ��SOCKADDR_IN��Internet�������׽��ֵ�ַ��
	���߳���һ��������16���ֽڣ�
	һ������£���Ҫ��SOCKADDR_IN�ṹǿ��ת����SOCKADDR�ṹ�ٴ���ϵͳ���ú�����*/
	SOCKADDR_IN addrServer;

	//address family, AF_xxx
	addrServer.sin_family=AF_INET;

	/*Internet address
	htonl������host to network long���������ֽ�˳��ת��Ϊ�����ֽ�˳��
	�����ֽ�˳��ָһ�������ڴ��д洢��ʱ�򣬸�λ�ֽڴ���ڵ͵�ַ��Ԫ����λ�ֽڴ���ڸߵ�ַ��Ԫ��*/
	addrServer.sin_addr.S_un.S_addr=htonl(INADDR_ANY);

	/*Port number
	htons������host to network short���������ֽ�˳��ת��Ϊ�����ֽ�˳��*/
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

	//WSACleanup�������������Socket��İ󶨲����ͷ�Socket����ռ�õ�ϵͳ��Դ
	WSACleanup();
	system("PAUSE");

	return 0;
}


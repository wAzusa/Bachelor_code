#include <iostream>
#include <string>
#include <winsock2.h> //����socket��ͷ�ļ�
#pragma comment (lib, "ws2_32.lib")	//���� ws2_32.dll
#pragma warning(disable:4996)
using namespace std; 

int main() 
{
//****��ʼ��WSA
	WSADATA wsaData;	
	//��ʼ��WSAStartup()����(�淶�İ汾�ţ�ָ��WSADATA�ṹ���ָ��)�������ϵͳ˵��Ҫʹ���ĸ�����ļ�
	//->MSKEWORD(2,2)���汾��2�����汾��2
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)		
	{				
		return 0; 
	}
	
//****�����׽���
	SOCKET servSock = socket(PF_INET, SOCK_STREAM, 0); 	
		//����1��IP��ַ����,PF_INET6->IPv6��PF_INET->IPv4
		//����2�����ݴ��䷽ʽ,SOCK_STREAM �� SOCK_DGRAM 
		//����3������Э��,IPPROTO_TCP �� IPPTOTO_UDP,д0ϵͳ���Զ����㴦ʹ������Э��
	
	//�ж���Ч�׽���
	if (servSock == INVALID_SOCKET) 
	{
		cout << "socket error!" << endl; 
		return 0; 
	}
	
//****��ip�Ͷ˿�
	
	//����sockaddr_in�ṹ�����(inָinternet)
	sockaddr_in sockAddr; 
	//ÿ���ֽڶ���0���
	memset(&sockAddr, 0, sizeof(sockAddr));	
	//ʹ��IPv4��ַ
	sockAddr.sin_family = PF_INET; 
	//���ö˿ںţ���htons()����ת��
	sockAddr.sin_port = htons(1234); 
	//�����IP��ַ,32λ
	sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 

//****���׽���bind()
	//����1��socket���������׽��ֱ���
	//����2��sockaddr�ṹ�������ָ�룬sockaddr_inǿת
	//����3������2�����Ĵ�С��һ��ʹ��sizeof()����
	if (bind(servSock, (SOCKADDR*)& sockAddr, sizeof(SOCKADDR)) == SOCKET_ERROR)
	{
		cout << "bind error!" << endl; 
		return 0; 
	}
	cout << "���׽��ֳɹ���" << endl; 

//****��ʼ����listen()
	//5-����Ŷ���
	//listen()ֻ���׽��ֽ������״̬����û��������������
	if (listen(servSock, 5) == SOCKET_ERROR) 
	{
		cout << "listen error!" << endl; 
	}
	cout << "�������Ѿ��������״̬.." << endl; 

//****���տͻ�������accept()
	//������bind()��ͬ
	//accept()������������У�ֱ�����µ�������
	//����һ���µ��׽������Ϳͻ���ͨ�ţ�����ʹ���µ��׽���ͨ��
	SOCKADDR clntAddr;
	int nSize = sizeof(SOCKADDR);
	SOCKET clntSock = accept(servSock, (SOCKADDR*)& clntAddr, &nSize);
	cout << "accept����ִ����Ͽ�ʼ�����û�����" << endl;

//****��ʼͨ��
	while (1)
	{	
		cout << "����һ�仰�����س�(quit�˳�)" << endl; 
		string input; 
		cin >> input; 

		//��ͻ��˷�������
		send(clntSock, input.c_str(), input.length(), NULL);
		cout << "���ݷ��ͳɹ�" << endl; 

		//�������quit���Ͽ�����
		if (input == "quit")
			break; 
	}

	//�ر��׽���
	closesocket(clntSock);
	closesocket(servSock);

	//��ֹ DLL ��ʹ��
	WSACleanup();

	return 0;
}

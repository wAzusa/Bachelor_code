#include <iostream>
#include <WinSock2.h> //����WinSock2.hͷ�ļ�
using namespace std; 
#pragma comment(lib, "ws2_32.lib") //���� ws2_32.dll 
#pragma warning(disable:4996)

int main() 
{
//****��ʼ��WSA
	WSADATA wsaData;
	//��ʼ���汾
	WSAStartup(MAKEWORD(2, 2), &wsaData);	

//****�����û���socket	
	SOCKET sock = socket(PF_INET, SOCK_STREAM, 0);		

//****����sockAddr�ṹ��
	sockaddr_in sockAddr; 
	//ÿ���ֽڶ���0���
	memset(&sockAddr, 0, sizeof(sockAddr));		
	//�󶨷��������˿�		 
	sockAddr.sin_family = PF_INET;
	sockAddr.sin_port = htons(1234);
	sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

//****��������
	connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
	cout << "�ͻ��˷�����������" << endl; 

//****���շ��������ص�����
	while (1)
	{
		char szBuffer[MAXBYTE] = { 0 };
		recv(sock, szBuffer, MAXBYTE, NULL);
		if (strcmp(szBuffer, "quit") == 0)
			break;
		cout << "���ܷ��������ص���Ϣ����" << endl;
		cout << szBuffer << endl;
	}

//****�ر��׽��֡���ֹʹ�� DLL
	closesocket(sock);
	WSACleanup();

	return 0;
}

#include <iostream>
#include <string>
#include <winsock2.h> //包含socket的头文件
#pragma comment (lib, "ws2_32.lib")	//加载 ws2_32.dll
#pragma warning(disable:4996)
using namespace std; 

int main() 
{
//****初始化WSA
	WSADATA wsaData;	
	//初始化WSAStartup()函数(规范的版本号，指向WSADATA结构体的指针)，向操作系统说明要使用哪个库的文件
	//->MSKEWORD(2,2)主版本号2，副版本号2
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)		
	{				
		return 0; 
	}
	
//****创建套接字
	SOCKET servSock = socket(PF_INET, SOCK_STREAM, 0); 	
		//参数1，IP地址类型,PF_INET6->IPv6，PF_INET->IPv4
		//参数2，数据传输方式,SOCK_STREAM 和 SOCK_DGRAM 
		//参数3，传输协议,IPPROTO_TCP 和 IPPTOTO_UDP,写0系统会自动计算处使用那种协议
	
	//判断无效套接字
	if (servSock == INVALID_SOCKET) 
	{
		cout << "socket error!" << endl; 
		return 0; 
	}
	
//****绑定ip和端口
	
	//创建sockaddr_in结构体变量(in指internet)
	sockaddr_in sockAddr; 
	//每个字节都用0填充
	memset(&sockAddr, 0, sizeof(sockAddr));	
	//使用IPv4地址
	sockAddr.sin_family = PF_INET; 
	//设置端口号，用htons()函数转换
	sockAddr.sin_port = htons(1234); 
	//具体的IP地址,32位
	sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 

//****绑定套接字bind()
	//参数1，socket服务器端套接字变量
	//参数2，sockaddr结构体变量的指针，sockaddr_in强转
	//参数3，参数2变量的大小，一般使用sizeof()计算
	if (bind(servSock, (SOCKADDR*)& sockAddr, sizeof(SOCKADDR)) == SOCKET_ERROR)
	{
		cout << "bind error!" << endl; 
		return 0; 
	}
	cout << "绑定套接字成功！" << endl; 

//****开始监听listen()
	//5-最大排队数
	//listen()只让套接字进入监听状态，并没有真正接收请求
	if (listen(servSock, 5) == SOCKET_ERROR) 
	{
		cout << "listen error!" << endl; 
	}
	cout << "服务器已经进入监听状态.." << endl; 

//****接收客户端请求accept()
	//参数与bind()相同
	//accept()会阻塞程序进行，直到有新的请求到来
	//返回一个新的套接字来和客户端通信，后面使用新的套接字通信
	SOCKADDR clntAddr;
	int nSize = sizeof(SOCKADDR);
	SOCKET clntSock = accept(servSock, (SOCKADDR*)& clntAddr, &nSize);
	cout << "accept函数执行完毕开始接收用户输入" << endl;

//****开始通信
	while (1)
	{	
		cout << "输入一句话并按回车(quit退出)" << endl; 
		string input; 
		cin >> input; 

		//向客户端发送数据
		send(clntSock, input.c_str(), input.length(), NULL);
		cout << "数据发送成功" << endl; 

		//如果输入quit，断开连接
		if (input == "quit")
			break; 
	}

	//关闭套接字
	closesocket(clntSock);
	closesocket(servSock);

	//终止 DLL 的使用
	WSACleanup();

	return 0;
}

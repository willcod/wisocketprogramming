// Server.cpp : Defines the entry point for the console application.
//

#define  BUF_SZIE	 64
#include <cstdio>

#include "winsock2.h"
#pragma comment(lib, "ws2_32.lib")

int main(int argc, char* argv[]) {
	WSADATA			wsd;			//WSADATA����
	char			buf[BUF_SZIE];	//�������ݻ�����

	//��ʼ���׽��ֶ�̬��
	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0) {
		printf("WSAStartup failed!\n");
		return 1;
	}

	SOCKADDR_IN		addrServ;		//��������ַ
	//�����׽���
	SOCKET sServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == sServer) {
		printf("socket failed!\n");
		WSACleanup();//�ͷ��׽�����Դ;
		return  -1;
	}

	//�������׽��ֵ�ַ 
	addrServ.sin_family = AF_INET;
	addrServ.sin_port = htons(4999);
	addrServ.sin_addr.s_addr = INADDR_ANY;
	//���׽���
	int retVal = bind(sServer, LPSOCKADDR(&addrServ), sizeof(SOCKADDR_IN));
	if (SOCKET_ERROR == retVal) {
		printf("bind failed!\n");
		closesocket(sServer);	//�ر��׽���
		WSACleanup();			//�ͷ��׽�����Դ;
		return -1;
	}

	//��ʼ���� 
	retVal = listen(sServer, 1);
	if (SOCKET_ERROR == retVal) {
		printf("listen failed!\n");
		closesocket(sServer);	//�ر��׽���
		WSACleanup();			//�ͷ��׽�����Դ;
		return -1;
	}

	//���ܿͻ�������
	sockaddr_in addrClient{};
	int addrClientlen = sizeof(addrClient);
	SOCKET sClient = accept(sServer, reinterpret_cast<sockaddr*>(&addrClient), &addrClientlen);
	if (INVALID_SOCKET == sClient) {
		printf("accept failed!\n");
		closesocket(sServer);	//�ر��׽���
		WSACleanup();			//�ͷ��׽�����Դ;
		return -1;
	}

	//���տͻ�������
	ZeroMemory(buf, BUF_SZIE);
	retVal = recv(sClient, buf, BUF_SZIE, 0);
	if (SOCKET_ERROR == retVal) {
		printf("recv failed!\n");
		closesocket(sServer);	//�ر��׽���
		closesocket(sClient);	//�ر��׽���		
		WSACleanup();			//�ͷ��׽�����Դ;
		return -1;
	}

	printf("%s\n", buf);	//���"MyTCP"	

	//�˳�
	closesocket(sServer);	//�ر��׽���
	closesocket(sClient);	//�ر��׽���
	WSACleanup();			//�ͷ��׽�����Դ;
	return 0;
}


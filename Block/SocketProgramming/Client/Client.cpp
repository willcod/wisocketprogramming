// Client.cpp : Defines the entry point for the console application.
//

#define	BUF_SZIE	64
#include <cstdio>

#include "winsock2.h"
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

int main(int argc, char* argv[]) {

	WSADATA			wsd;			//WSADATA����
	SOCKET			sHost;			//�������׽���
	SOCKADDR_IN		servAddr;		//��������ַ
	char			buf[BUF_SZIE];	//�������ݻ�����
	int				retVal;			//����ֵ

	//��ʼ���׽��ֶ�̬��
	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0) {
		printf("WSAStartup failed!\n");
		return -1;
	}

	//�����׽���
	sHost = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == sHost) {
		printf("socket failed!\n");
		WSACleanup();//�ͷ��׽�����Դ
		return  -1;
	}

	//���÷�������ַ
	servAddr.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &servAddr.sin_addr);
	char str[INET_ADDRSTRLEN];
	const char* ptr = inet_ntop(AF_INET, &servAddr, str, sizeof(str));
	servAddr.sin_port = htons(static_cast<short>(4999));
	int	nServAddlen = sizeof(servAddr);

	//���ӷ�����
	retVal = connect(sHost, (LPSOCKADDR)&servAddr, sizeof(servAddr));
	if (SOCKET_ERROR == retVal) {
		printf("connect failed!\n");
		closesocket(sHost);	//�ر��׽���
		WSACleanup();		//�ͷ��׽�����Դ
		return -1;
	}

	//���������������
	ZeroMemory(buf, BUF_SZIE);
	strcpy_s(buf, "MyTCP");
	retVal = send(sHost, buf, strlen(buf), 0);
	if (SOCKET_ERROR == retVal) {
		printf("send failed!\n");
		closesocket(sHost);	//�ر��׽���
		WSACleanup();		//�ͷ��׽�����Դ
		return -1;
	}

	//�˳�
	closesocket(sHost);	//�ر��׽���
	WSACleanup();		//�ͷ��׽�����Դ
	return 0;
}


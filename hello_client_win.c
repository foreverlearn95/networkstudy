#include <stdio.h>
#include <stdlib.h>
#include <winsock.h>

void errorhandling(char* message);

int main(int argc, char* argv[]) {
	WSADATA wsadata;
	SOCKET hsocket;
	SOCKADDR_IN servaddr;

	char message[30];
	int strlen;
	if (argc != 3) {
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	}

	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
		errorhandling("WSAStartup() error!");

	hsocket = socket(PF_INET, SOCK_STREAM, 0);

	if (hsocket == INVALID_SOCKET)
		errorhandling("socket() error!");

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(argv[1]);
	servaddr.sin_port = htons(atoi(argv[2]));

	if (connect(hsocket, (SOCKADDR*)&servaddr, sizeof(servaddr)) == SOCKET_ERROR)
		errorhandling("connect() error!");

	strlen = recv(hsocket, message, sizeof(message) - 1, 0);
	if (strlen == -1)
		errorhandling("read() error!");
	printf("Message from server: %s \n", message);
	closesocket(hsocket);
	WSACleanup();
	//system("pause");
	return 0;

}

void errorhandling(char* message) {
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
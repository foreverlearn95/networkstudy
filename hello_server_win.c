#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

void errorhandling(char* message);

int main(int argc, char* argv[]){
    WSADATA wsaData;
    SOCKET hservsock, hclntsock;
    SOCKADDR_IN servaddr, clntaddr;

    int szclntaddr;
    char message[]="hello server!";
    if(argc!=2){
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }
    if(WSAStartup(MAKEWORD(2,2), &wsaData)!=0)
        errorhandling("WSAStartup() error!");
    hservsock = socket(PF_INET, SOCK_STREAM, 0);
    if(hservsock==INVALID_SOCKET)
        errorhandling("socket() error");
    
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddr.sin_port=htons(atoi(argv[1]));

    if(bind(hservsock, (SOCKADDR*) &servaddr, sizeof(servaddr))==SOCKET_ERROR)
        errorhandling("bind() error");
    if(listen(hservsock, 5)==SOCKET_ERROR)
        errorhandling("listen() error");
    
    szclntaddr = sizeof(clntaddr);
    hclntsock=accept(hservsock, (SOCKADDR*)&clntaddr,&szclntaddr);
    if(hclntsock==INVALID_SOCKET)
        errorhandling("accept() error");

    send(hclntsock, message, sizeof(message), 0);
    closesocket(hclntsock);
    closesocket(hservsock);
    WSACleanup();
    return 0;
}
void errorhandling(char* message)
{
    fputs(message, stderr);
    fputc('\n',stderr);
    exit(1);
}
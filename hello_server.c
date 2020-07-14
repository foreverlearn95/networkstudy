//understand just total flow

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
void error_handling(char *message);

int main(int argc, char *argv[]){
    int serv_sock;
    int clnt_sock;

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklent_t clnt_addr_size;

    char message[]="Hello world!";

    if(argc!=2){
        printf("Usage : %s <port>\n",argv[0]);
        exit(1);
    }
    serv_sock=socket(PF_INET, SOCK_STREAM, 0); //make socket by OS
    //socket을 만들면서 숫자를 부여해준다. socket make - > return int 


    if(serv_sock == -1)
        error_handling("socket() error");
    
    memset(&serv_addr, 0, sizeof(serv_addr)); // memset 으로 주소 0으로 clear
    // IP , port 할당.
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_addr.sin_port=htons(atoi(argv[1]));

    if(bind(serv_sock, (struct sockaadr*) &serv_addr, sizeof(serv_addr))==-1)
        error_handling("bind() error");
    if(listen(serv_sock,5)==-1) //연결요청 및 연결하면 받아들일 
        error_handling("listen() error");
    
    clnt_addr_size=sizeof(clnt_addr);

    //accept는 일단 호출해보는 것임 나한테 걸려온 전화 없었는지
    clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
    if(clnt_sock==-1)
        error_handling("accept() error");
    
    //write를 통해 data 전달
    write(clnt_sock, message, sizeof(message));
    close(clnt_sock);
    close(serv_sock);
    return 0;
}

void error_binding(char *message){
    fputs(message, stderr);
    fputc('\n',stderr);
    exit(1);
}
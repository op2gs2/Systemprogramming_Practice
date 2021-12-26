#include <sys/types.h>
#include <sys/socket.h> 
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h>
#define PORTNUM 9002

int main(void){
    int sd;
    char recv_msg[256];
    char send_msg[256];
    struct sockaddr_in sin;

    memset((char *)&sin, '\0', sizeof(sin));
    sin.sin_family = AF_INET; // 인터넷 도메인
    sin.sin_port = htons(PORTNUM); // 서버측 포트 번호
    sin.sin_addr.s_addr = inet_addr("127.0.0.1"); // 서버 IP 주소

    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    if (connect(sd, (struct sockaddr *)&sin, sizeof(sin))) {
        perror("connect");
        exit(1);
    }

    while(1){
        // 1. 보낼 메시지를 입력 받기
        #ifdef DEBUG
            //printf("****4. 보낼 메시지 받기****\n");
        #endif
        printf("Enter Message: ");
        gets(send_msg);

        // 2. 메시지를 보내기
        #ifdef DEBUG
            //printf("****5. 메시지 보내기****\n");
        #endif
        if (send(sd, send_msg, sizeof(send_msg), 0) == -1) {
            perror("send");
            exit(1);
        }

        // 3. <QUIT>이 입력되면 프로그램 종료
        #ifdef DEBUG
            //printf("****6. 프로그램 종료 여부 확인****\n");
        #endif
        if(strcmp(send_msg,"<QUIT>") == 0){
            close(sd);
            exit(0);
        }

        // 4. 보낸 메시지를 출력하기
        #ifdef DEBUG
            //printf("****7. 보낸 메시지를 출력하기\n****");
        #endif
        printf("YOU: %s\n", send_msg);
        strcpy(send_msg,"");
    }
}
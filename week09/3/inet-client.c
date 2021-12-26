#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define PORTNUM 9000

int main(void) {
    int sd;
    char recv_msg[256]; // 클라이언트가 받은 메시지
    char send_msg[256]; // 클라이언트가 보내는 메시지
    struct sockaddr_in sin;

    // 소켓 생성
    #ifdef DEBUG
        printf("1. 소켓 생성\n");
    #endif
    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    // 소켓 주소 구조체 생성
    #ifdef DEBUG
        printf("2. 소켓 구조체 생성\n");
    #endif
    memset((char *)&sin, '\0', sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(PORTNUM);
    sin.sin_addr.s_addr = inet_addr("127.0.0.1"); // server ip address
    

    // 서버에 접속 요청
    #ifdef DEBUG
        printf("3. 서버 접속\n");
    #endif
    if (connect(sd, (struct sockaddr *)&sin, sizeof(sin))) {
        perror("connect");
        exit(1);
    }

    while(1){
        // 사용자로부터 메시지를 읽기
        printf("Input a Message: ");
        gets(send_msg);

        // exit을 입력 받으면 프로그램 종료
        if(strcmp("exit",send_msg) == 0){
            printf("Close the Program\n");
            break;
        }

        // 서버로 메시지 전송하기
        #ifdef DEBUG
            printf("4. 메시지 송신\n");
        #endif
        if(send(sd, send_msg, sizeof(send_msg), 0) == -1){
            perror("send");
            exit(1);
        }

        // 서버가 보낸 메시지를 읽기
        #ifdef DEBUG
            printf("5. 메시지 수신\n");
        #endif
        if (recv(sd, recv_msg, sizeof(recv_msg), 0) == -1) {
            perror("recv");
            exit(1);
        }

        printf("From Server : %s\n", recv_msg);

    }
    
    close(sd);
    return 0;
}
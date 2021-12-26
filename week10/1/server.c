#include <sys/types.h>
#include <sys/socket.h> 
#include <unistd.h>
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h>
#define PORTNUM 9002

int main(void) {
    char recv_msg[256];
    char send_msg[256];
    struct sockaddr_in sin, cli; // 주소 정보를 저장할 구조체
    int sd, ns, clientlen = sizeof(cli);

    memset((char *)&sin, '\0', sizeof(sin)); // 소켓 주소 구조체 초기화 및 값 설정
    sin.sin_family = AF_INET; // 인터넷 도메인
    sin.sin_port = htons(PORTNUM); // 서버 포트
    sin.sin_addr.s_addr = inet_addr("127.0.0.1"); // 서버 IP 주소

    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) { // 소켓 생성
        perror("socket");
        exit(1);
    }

    if (bind(sd, (struct sockaddr *)&sin, sizeof(sin))) { // 소겟과 주소 연결
        perror("bind");
        exit(1);
    }

    if (listen(sd, 5)) { // 클라이언트 접속을 기다림
        perror("listen");
        exit(1);
    }
    
    if ((ns = accept(sd, (struct sockaddr *)&cli, &clientlen)) == -1) { // 클라이언트와 접속이 이루어짐
        perror("accept");
        exit(1);
    } // 새로운 소켓 기술자가 리턴됨

    close(sd);

    while(1){
        // 1. 보낼 메시지를 입력 받기
        #ifdef DEBUG
            //printf("****1. 보낼 메시지 받기****\n");
        #endif
        printf("Enter Message: ");
        gets(send_msg);

        // 2. 메시지를 보내기
        #ifdef DEBUG
            //printf("****2. 메시지 보내기****\n");
        #endif
        if (send(ns, send_msg, sizeof(send_msg), 0) == -1) {
            perror("send");
            exit(1);
        }

        // 3. <QUIT>이 입력되면 프로그램 종료
        #ifdef DEBUG
            //printf("****3. 프로그램 종료 여부 확인****\n");
        #endif
        if(strcmp(send_msg,"<QUIT>") == 0){
            close(ns);
            exit(0);
        }

        // 4. 보낸 메시지를 출력하기
        #ifdef DEBUG
            //printf("****4. 보낸 메시지를 출력하기\n****");
        #endif
        printf("YOU: %s\n", send_msg);
        strcpy(send_msg,"");

        // 5. 상대로부터 메시지 받기
        #ifdef DEBUG
            //printf("****5. 메시지 받기****\n");
        #endif
        if (recv(ns, recv_msg, sizeof(recv_msg), 0) == -1) {
            perror("recv");
            exit(1);
        }

        // 6. <QUIT>이 입력받으면 프로그램 종료
        #ifdef DEBUG
            //printf("****6. 프로그램 종료 여부 확인****\n");
        #endif
        if(strcmp(recv_msg,"<QUIT>") == 0){
            close(ns);
            exit(0);
        }

        // 7. 받은 메시지를 출력하기
        #ifdef DEBUG
            //printf("****7. 받은 메시지 출력****\n");
        #endif
        printf("From Client : %s\n", recv_msg);
        strcpy(recv_msg,"");
    }
}
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
    while(1){
        if ((ns = accept(sd, (struct sockaddr *)&cli, &clientlen)) == -1) { // 클라이언트와 접속이 이루어짐
            perror("accept");
            exit(1);
        } // 새로운 소켓 기술자가 리턴됨

        if(fork() == 0){
            close(sd);
            while(1){
                // 1. 상대로부터 메시지 받기
                if (recv(ns, recv_msg, sizeof(recv_msg), 0) == -1) {
                    perror("recv");
                    exit(1);
                }

                // 2. 받은 메시지를 출력하기
                printf("From Client : %s\n", recv_msg);
                strcpy(recv_msg,"");

                // 3. <QUIT>이 입력받으면 프로그램 종료
                if(strcmp(recv_msg,"<QUIT>") == 0){
                    close(ns);
                    exit(0);
                }
            }
        }
    }


    

    
}
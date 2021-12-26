#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define PORTNUM 9000

int main(void) {
    char send_msg[256]; // 서버가 보낸 메시지
    char recv_msg[256]; // 서버가 받은 메시지
    struct sockaddr_in sin, cli;
    int sd, ns, clientlen = sizeof(cli);
    
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
    
    // 소켓기술자와 소켓 주소 구조체 연결
    #ifdef DEBUG
        printf("3. bind() 완료\n");
    #endif
    if (bind(sd, (struct sockaddr *)&sin, sizeof(sin))) {
        perror("bind");
        exit(1);
    }

    // 클라이언트 접속요청 대기
    #ifdef DEBUG
        printf("4. 클라이언트 접속요청 대기\n");
    #endif
    if (listen(sd, 5)) {
        perror("listen");
        exit(1);
    }

    // 클라이언트와 연결
    #ifdef DEBUG
        printf("5. 클라이언트와 연결\n");
    #endif
    if ((ns = accept(sd, (struct sockaddr *)&cli, &clientlen))==-1){
        perror("accept");
        exit(1);
    }

    close(sd);

    while(1){
        // 클라이언트의 메시지 받기
        #ifdef DEBUG
            printf("6. 클라이언트 메시지 수신\n");
        #endif
        if (recv(ns, recv_msg, sizeof(recv_msg), 0) == -1){
            perror("recv");
            exit(1);
        }

        // Client로부터 exit이 입력되면 연결을 종료
        if(strcmp("exit",recv_msg) == 0){
            printf("Close the Connection\n");
            break;
        }

        // 아직 클라이언트로부터 입력을 못 받으면, 반복문 재 실행
        if(strcmp(recv_msg,"0") == 0){ 
            continue;
        }

        printf("Message Receives ...\n");
        // 클라이언트 메시지 출력
        printf("Recv msg: %s\n",recv_msg);
        
        // 클라이언트로 데이터 보내기
        #ifdef DEBUG
            printf("7. 클라이언트 메시지 송신\n");
        #endif
        printf("Send Message ...\n");
        strcpy(send_msg,"Server received the message.");
        if (send(ns, send_msg, sizeof(send_msg), 0) == -1) {
            perror("send");
            exit(1);
        }
        
        // 사용을 종료한 메시지 버퍼는 비워준다.
        strcpy(recv_msg,"0");
    }

    
    close(ns);
    return 0;
}
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/un.h>

#define SOCKET_NAME "hsocket"

int main(void) {
    char recv_msg[256];
    char send_msg[256];
    struct sockaddr_un ser, cli;
    int sd, nsd, len, clen, fd;
    FILE* pfile;

    // 유닉스 도메인 소켓 생성
    if ((sd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    memset((char *)&ser, 0, sizeof(struct sockaddr_un));
    ser.sun_family = AF_UNIX; // 소켓 구조체에 값 지정
    strcpy(ser.sun_path, SOCKET_NAME);
    len = sizeof(ser.sun_family) + strlen(ser.sun_path);

    // 소켓 기술자와 소켓 주소 구조체 연결
    if (bind(sd, (struct sockaddr *)&ser, len)) {
        perror("bind");
        exit(1);
    }

    // 클라이언트 접속 대기
    if (listen(sd, 5) < 0) {
        perror("listen");
        exit(1);
    }

    // 클라이언트 접속 받음
    printf("Waiting ...\n");
    if ((nsd = accept(sd, (struct sockaddr *)&cli, &clen)) == -1) {
        perror("accept");
        exit(1);
    }

    // 클라이언트로부터 파일 경로를 받음
    if (recv(nsd, recv_msg, sizeof(recv_msg), 0) == -1) {
        perror("recv");
        exit(1);
    }

    // 경로에 있는 파일을 열어봄
    pfile = fopen(recv_msg, "r");
    if (pfile == NULL){
        // 파일이 존재하지 않으면 오류메시지
        strcpy(send_msg, "File not exist!!\n");
    } else{
        // 파일을 16바이트 읽어들임
        fread(send_msg, 1, 16, pfile);
    }
    
    // 메시지를 클라이언트로 전송
    if(send(nsd, send_msg, sizeof(send_msg), 0) == -1){
        perror("send");
        exit(1);
    }

    close(nsd);
    close(sd);
    return 0;
}
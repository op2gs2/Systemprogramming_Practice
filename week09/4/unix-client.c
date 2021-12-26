#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/un.h>

#define SOCKET_NAME "hsocket"

int main(int argc, char *argv[]) {
    int sd, len;
    char send_msg[256];
    char recv_msg[256];
    struct sockaddr_un ser;

    // 명령행 인자가 조건과 맞지 않으면 에러
    if(argc != 2){
        fprintf(stderr, "Argument is insufficient!");
        exit(1);
    }

    // 유닉스 도메인 소켓 생성
    if ((sd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    // 소켓 구조체에 값 지정
    memset((char *)&ser, '\0', sizeof(ser));
    ser.sun_family = AF_UNIX; 
    strcpy(ser.sun_path, SOCKET_NAME);
    len = sizeof(ser.sun_family) + strlen(ser.sun_path);

    // 서버에 연결 요청
    if (connect(sd, (struct sockaddr *)&ser, len) < 0) {
        perror("bind");
        exit(1);
    }

    // 절대 경로로 표현된 파일의 경로를 서버로 전달
    strcpy(send_msg, argv[1]);
    if (send(sd, send_msg, sizeof(send_msg), 0) == -1) {
        perror("send");
        exit(1);
    }

    // 서버로부터 받은 메시지를 화면에 출력함
    if(recv(sd, recv_msg, sizeof(recv_msg), 0) == -1){
        perror("recv");
        exit(1);
    }
    printf("From Server: %s\n",recv_msg);

    close(sd);
    return 0;
}
#include <sys/types.h>
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define PORTNUM 9005

int main(void) {
    int sd, n;
    char buf[256];
    struct sockaddr_in sin;

    if ((sd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) { // 소켓 생성
        perror("socket");
        exit(1);
    }

    memset((char *)&sin, '\0', sizeof(sin)); // 소켓 주소 구조체 설정
    sin.sin_family = AF_INET; // 인터넷 도메인
    sin.sin_port = htons(PORTNUM); // 서버 포트번호
    sin.sin_addr.s_addr = inet_addr("127.0.0.1"); // 서버 IP 주소

    // 1. 서버에게 TIME-REQUEST 보내기
    strcpy(buf, "TIME-REQUEST");
    if (sendto(sd, buf, strlen(buf)+1, 0, \
    (struct sockaddr *)&sin, sizeof(sin)) == -1) { // 서버에 메시지 전송
        perror("sendto");
        exit(1);
    }

    // 2. 서버로부터 받은 메시지를 출력 후, 종료
    n = recvfrom(sd, buf, 255, 0, NULL, NULL); // 서버가 보낸 데이터 읽기
    buf[n] = '\0';
    printf("** Server Time : %s\n", buf);

    return 0;
}
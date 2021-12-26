#include <sys/types.h>
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#define PORTNUM 9005

int main(void) {
    char buf[256]; // 메시지의 송수신을 위한 버퍼
    char ip_buf[INET_ADDRSTRLEN]; // 클라이언트의 IP주소를 저장하기 위한 버퍼
    struct tm time_msg; // localtime()으로 변환된 정보를 저장하기 위한 변수
    time_t t; // 시간 정보를 얻어오기 위한 변수
    struct sockaddr_in sin, cli; // 소켓 주소 구조체
    int sd, clientlen = sizeof(cli); // 소켓 기술자

    if ((sd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) { // 소켓 생성
        perror("socket");
        exit(1);
    }

    memset((char *)&sin, '\0', sizeof(sin)); // 소켓 주소 구조체 설정
    sin.sin_family = AF_INET; // 인터넷 도메인
    sin.sin_port = htons(PORTNUM); // 서버 포트 번호
    sin.sin_addr.s_addr = inet_addr("127.0.0.1"); // 서버 IP 주소

    if (bind(sd, (struct sockaddr *)&sin, sizeof(sin))) { // 소켓 기술자와 소켓 주소 구조체 연결
        perror("bind");
        exit(1);
    }

    /*UDP는 바로 데이터 송수신을 할 수 있음*/
    while (1) { // 서버 프로그램은 무한 반복

        // 1. 클라이언트로부터 요청을 받음. 이 때, 올바른 요청인지 검사함.
        if ((recvfrom(sd, buf, 255, 0, \
        (struct sockaddr *)&cli, &clientlen)) == -1) { // 클라이언트의 메시지를 받음
            perror("recvfrom");
            exit(1);
        }
        if(strcmp(buf,"TIME-REQUEST") != 0){ // 클라이언트의 요청이 올바른 요청인지 확인함
            perror("REQUEST TYPE ERROR!!\n");
            exit(1);
        }

        // 2. 터미널에 클라이언트 IP를 출력함
        inet_ntop(AF_INET, &(cli.sin_addr), ip_buf, INET_ADDRSTRLEN);
        printf("**Client IP: %s\n",ip_buf);

        // 3. 클라이언트에게 현재 시간정보를 보내줌.
        t = time(NULL); // 현재 시간 정보를 얻어옴
        time_msg = *localtime(&t); // 시간을 보기 쉽게 변경해줌.
        sprintf(buf, "%d년 %d월 %d일 %d시 %d분 %d초\n",
         time_msg.tm_year+1900, time_msg.tm_mon+1, time_msg.tm_mday,
         time_msg.tm_hour, time_msg.tm_min, time_msg.tm_sec); // 시간 정보를 버퍼에 삽입

        if ((sendto(sd, buf, sizeof(buf), 0, \
        (struct sockaddr *)&cli, sizeof(cli))) == -1) { // 클라이언트로 메시지 보내기
            perror("sendto");
            exit(1);
        }
    }

    return 0;
}
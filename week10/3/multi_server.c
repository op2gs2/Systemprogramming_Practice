#include <sys/types.h>
#include <sys/socket.h> 
#include <unistd.h>
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h>
#include <time.h>
#define PORTNUM 9006

int main(void) {
    char buf[256];
    struct sockaddr_in sin, cli; // 주소 정보를 저장할 구조체
    int sd, ns, clientlen = sizeof(cli);

    char hostname[256];
    char ip_addr[256];
    int port;

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

    // 1. 가능한 서비스 목록을 클라이언트로 보냄
    strcpy(buf,"<Available Services>\n1. Echo server <ECHO>\n2. Get server info <SINFO>\n3. Get server time <STIME>\n");
    if (send(ns, buf, sizeof(buf), 0) == -1) {
        perror("send");
        exit(1);
    }

    // 2. 클라이언트의 메시지를 받음.
    if (recv(ns, buf, sizeof(buf), 0) == -1) {
        perror("recv");
        exit(1);
    }

    // 3. 클라이언트의 메시지를 바탕으로, 어떤 서비스를 실행할 지 결정
    if (strcmp(buf,"<ECHO>") == 0){
        while(1){
            // 1. 클라이언트로부터 메시지 받기
            if (recv(ns, buf, sizeof(buf), 0) == -1) {
                perror("recv");
                exit(1);
            }

            // 2. <QUIT>이 입력받으면 프로그램 종료
            if(strcmp(buf,"<QUIT>") == 0){
                close(ns);
                exit(0);
            }

            // 3. 클라이언트로 메시지 보내기
            if (send(ns, buf, sizeof(buf), 0) == -1) {
                perror("send");
                exit(1);
            }
        }
    } 
    
    else if (strcmp(buf,"<SINFO>") == 0){
        // 1. 서버 정보를 얻어옴
        if(gethostname(hostname,sizeof(hostname)) == -1){
            perror("gethostname");
            exit(1);
        }
        inet_ntop(AF_INET, &(sin.sin_addr), ip_addr, INET_ADDRSTRLEN);
        sprintf(buf,"Host name: %s\nIP address: %s\nPort: %d\n",hostname,ip_addr,ntohs(sin.sin_port));

        // 2. 서버 정보를 보냄
        if (send(ns, buf, sizeof(buf), 0) == -1) {
            perror("send");
            exit(1);
        }
    } 
    
    else if (strcmp(buf,"<STIME>") == 0){
        // 1. 시간 정보를 얻어옴
        time_t t = time(NULL); // 현재 시간 정보를 얻어옴
        struct tm time_msg = *localtime(&t); // 시간을 보기 쉽게 변경해줌.
        sprintf(buf, "%d년 %d월 %d일 %d시 %d분 %d초\n",
            time_msg.tm_year+1900, time_msg.tm_mon+1, time_msg.tm_mday,
            time_msg.tm_hour, time_msg.tm_min, time_msg.tm_sec); // 시간 정보를 버퍼에 삽입

        // 2. 시간 정보를 보냄
        if (send(ns, buf, sizeof(buf), 0) == -1) {
            perror("send");
            exit(1);
        }
    } 
    
    else {
        printf("Wrong Request!\n");
        close(ns);
        close(sd);
        exit(1);
    }

    close(ns);
    return 0;
}
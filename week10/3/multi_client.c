#include <sys/types.h>
#include <sys/socket.h> 
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h>
#define PORTNUM 9006

int main(void){
    int sd;
    char buf[256];
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

    // 1. 클라이언트는 서버의 메시지를 받고 출력함
    if (recv(sd, buf, sizeof(buf), 0) == -1) {
        perror("recv");
        exit(1);
    }
    printf("%s\n",buf);

    // 2. 서버로 어떤 서비스를 이용하는지 보냄
    printf("Select Service : ");
    gets(buf);
    if (send(sd, buf, sizeof(buf), 0) == -1) {
        perror("send");
        exit(1);
    }

    // 3. 각 서비스 별로 대응함.
   if (strcmp(buf,"<ECHO>") == 0){
        while(1){
            // 1. 보낼 메시지를 입력 받기
            printf("Enter Message: ");
            gets(buf);

            // 2. 메시지를 보내기
            if (send(sd, buf, sizeof(buf), 0) == -1) {
                perror("send");
                exit(1);
            }

            // 5. <QUIT>이 입력받으면 프로그램 종료
            if(strcmp(buf,"<QUIT>") == 0){
                close(sd);
                exit(0);
            }

            // 3. 상대로부터 메시지 받기
            if (recv(sd, buf, sizeof(buf), 0) == -1) {
                perror("recv");
                exit(1);
            }

            // 4. 받은 메시지를 출력하기
            printf("** From Server : %s\n", buf);
            strcpy(buf,"");
        }
   }

   else if (strcmp(buf,"<SINFO>") == 0 || strcmp(buf,"<STIME>") == 0){
        if (recv(sd, buf, sizeof(buf), 0) == -1) {
            perror("recv");
            exit(1);
        }
        printf("%s\n",buf);
   }

   else {
       printf("Wrong Request!\n");
   }

    close(sd);
    return 0;
}
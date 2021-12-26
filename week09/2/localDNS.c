#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]){
    int check_flag = 2;
    int i = 0;
    
    if(argc != 3){
        fprintf(stderr,"Agument Count Number Error!\n");
        exit(2);
    }

    struct hostent *hent;

    sethostent(0); // DB의 처음위치로 이동

    while((hent = gethostent()) != NULL){ // DB의 내용을 읽어오기
        if(strcmp(argv[1],hent->h_name) == 0){ // argv의 첫번째 값과 읽어온 호스트 이름이 일치하는지 확인
            printf("IP_addr: %s\n",inet_ntoa(*(struct in_addr*)hent->h_addr_list[i]));
            check_flag -= 1;
        } else if(strcmp(argv[2],hent->h_name) == 0){ // argv의 두번째 값과 읽어온 호스트 이름이 일치하는지 확인
            printf("IP_addr: %s\n",inet_ntoa(*(struct in_addr*)hent->h_addr_list[i]));
            check_flag -= 1;
        }
        i += 1;
    }

    if(check_flag > 0){ // Flag 값이 0보다 크다면, 출력
        printf("Not Found\n");
    }
        
    endhostent(); // DB 닫기

    return 0;
}
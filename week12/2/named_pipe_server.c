#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void) {
    FILE *fp;
    int rd_pipe, wr_pipe, n = 1;
    char msg[256]="";
    char send_msg[256]="";
    printf("Server =====\n");

    // FIFO 파일 생성
    if(fopen("./FIFO","rw") == NULL){
        if (mkfifo("./FIFO", 0666) == -1) {
            perror("mkfifo");
            exit(1);
        }
    }

    // FIFO2 파일 생성
    if(fopen("./FIFO2","rw") == NULL){
        if (mkfifo("./FIFO2", 0666) == -1) {
            perror("mkfifo");
            exit(1);
        }
    }    
    

    // FIFO 파이프 파일을 읽기모드로 열기
    if ((rd_pipe = open("./FIFO", O_RDONLY)) == -1) {
        perror("open");
        exit(1);
    }

    // FIFO2 파이프 파일을 쓰기모드로 열기
    if ((wr_pipe = open("./FIFO2", O_WRONLY)) == -1) {
        perror("open");
        exit(1);
    }


    // 클라이언트의 메시지 읽어들이기
    read(rd_pipe, msg, sizeof(msg));
     
    // 클라이언트의 메시지 확인하기
    if(strcmp(msg, "hello.txt") == 0){
        // 파일이 없을 경우
        if((fp = fopen("./hello.txt", "r")) == NULL){
            #ifdef DEBUG
                printf("fopen error!\n");
            #endif
            strcpy(send_msg, "File does not exist\n");
        } 
        // 파일이 존재할 경우
        else{
            #ifdef DEBUG
                printf("fread!\n");
            #endif
            fread(send_msg, sizeof(send_msg)+1, 1, fp);
            #ifdef DEBUG
                printf("To Client: %s\n",send_msg);
            #endif
        }
    } 
    else if(strcmp(msg, "<EXIT>") == 0){
        if (write(wr_pipe, send_msg, strlen(send_msg)+1) == -1) {
            perror("write");
            exit(1);
        }
        exit(1);
    }
    // 클라이언트의 메시지가 올바르지 않을 경우
    else{
        #ifdef DEBUG
            printf("Message Read Error!\n");
        #endif
        strcpy(send_msg, "File does not exist\n");
    }

    // FIFO 파일에 문자열 출력
    if (write(wr_pipe, send_msg, strlen(send_msg)+1) == -1) {
        perror("write");
        exit(1);
    }
    close(rd_pipe);
    close(wr_pipe);

    return 0;
}
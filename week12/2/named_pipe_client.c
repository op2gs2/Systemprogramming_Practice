#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    FILE *fp;
    int rd_pipe, wr_pipe, n;
    char msg[256]="";
    char recv_msg[256]="";
    printf("Client =====\n");

    // FIFO 파이프 파일을 쓰기모드로 열기
    if ((wr_pipe = open("./FIFO", O_WRONLY)) == -1) {
        perror("open");
        exit(1);
    }

    // FIFO2 파이프 파일을 쓰기모드로 열기
    if ((rd_pipe = open("./FIFO2", O_RDONLY)) == -1) {
        perror("open");
        exit(1);
    }


    // 파이프에 데이터 입력
    printf("<GET> "); 
    scanf("%s",msg);
    if (write(wr_pipe, msg, sizeof(msg)+1) == -1) {
        perror("write");
        exit(1);
    }
    #ifdef DEBUG
        printf("%s\n",msg);
    #endif

    // 서버에서 결과 가져오기
    read(rd_pipe, recv_msg, sizeof(recv_msg));

    // 서버로부터의 결과 출력
    printf("From Server: %s\n", recv_msg);

    // 서버의 반응을 확인 후, 파일에 저장여부 결정
    if(strcmp(recv_msg, "File does not exist\n") == 0){
        printf(recv_msg);
        exit(1);
    }
    // 별도의 파일에 저장
    else{
        fp = fopen("./download_hello.txt", "w");
        fwrite(recv_msg, sizeof(recv_msg), 1, fp);
    }

    close(rd_pipe);
    close(wr_pipe);

    return 0;
}
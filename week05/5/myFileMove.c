#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]){
    int opt = -1;

    // 인자 수 검사
    if(argc != 3){
        perror("Wrong Argument!");
        exit(1);
    }

    // 옵션 설정
    if((opt = getopt(argc, argv, "h")) == -1){
        switch(opt){
            case 'h':
                printf("Usage: ./myFileMove [src file] [dst file]\n");
                break;
            case '?':
                printf("You gave wrong argument!\n");
                break;
        }
    }

    // 파일을 이동함
    if(rename(argv[1], argv[2])==-1){
        perror("rename");
        exit(1);
    }

    return 0;
}
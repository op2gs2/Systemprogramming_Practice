#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char* argv[]){
    char *dirname = "";
    FILE *fp;
    
    if (argc < 2){
        perror("Argument Number Error!");
        exit(1);
    }

    // 1. 디렉토리명을 받음
    dirname = argv[1];

    // 2. 디렉토리를 생성
    if( mkdir(dirname, 0755) == -1){
        perror("mkdir");
        exit(1);
    }

    // 3. 만든 디렉토리로 이동
    if(chdir(dirname) == -1){
        perror("chdir");
        exit(1);
    }

    // 4. README.TXT 생성

    if((fp=fopen("README.txt","w+"))==NULL){
        perror("chdir");
        exit(1);
    }

    fclose(fp);
    return 0;
}
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	/*변수 초기화*/
    struct stat buffer;
    char *filetype = "";
    int permission = 0;

    /*인자가 없으면 종료*/
	if (argc < 1){
        fprintf(stderr,"Worng Argument Numbers!");
        exit(1);
    } 

    /*stat실행을 실패하면 종료*/
	if (stat(argv[1],&buffer) == -1){
        perror(argv[1]);
		exit(1);
    }

    /*파일의 종류 파악*/
    switch(buffer.st_mode & S_IFMT){
        case S_IFIFO:
            filetype = "FIFO 파일";
            break;
        case S_IFCHR:
            filetype = "문자 장치 특수 파일";
            break;
        case S_IFDIR:
            filetype = "디렉토리";
            break;
        case S_IFBLK:
            filetype = "블록 장치 특수 파일";
            break;
        case S_IFREG:
            filetype = "일반 파일";
            break;
        case S_IFLNK:
            filetype = "심볼릭 링크 파일";
            break;
        case S_IFSOCK:
            filetype = "소켓 파일";
            break;
    }

    /*접근 권한 파악하기*/
    // 사용자 권한 검사
    if ((buffer.st_mode & S_IREAD) != 0){
        permission += 400;
    }
    if((buffer.st_mode & S_IWRITE) != 0){
        permission += 200;
    }
    if((buffer.st_mode & S_IEXEC) != 0){
        permission += 100;
    }
    
    // 그룹 권한 검사
    if ((buffer.st_mode & (S_IREAD >> 3)) != 0){
        permission += 40;
    }
    if((buffer.st_mode & (S_IWRITE >> 3)) != 0){
        permission += 20;
    }
    if((buffer.st_mode & (S_IEXEC >> 3)) != 0){
        permission += 10;
    }

    // 기타 사용자 권한 검사
    if ((buffer.st_mode & (S_IREAD >> 6)) != 0){
        permission += 4;
    }
    if((buffer.st_mode & (S_IWRITE >> 6)) != 0){
        permission += 2;
    }
    if((buffer.st_mode & (S_IEXEC >> 6)) != 0){
        permission += 1;
    }

    /* 결과 출력 */
    printf("File Name: %s\n",argv[1]);
    printf("-  inode Number: %d\n",(int)buffer.st_ino);
    printf("-  File Type: %s\n",filetype);
	printf("-  Permission: %d\n",permission);
    printf("-  Number of links: %o\n",(unsigned int)buffer.st_nlink);
    printf("-  Size: %d\n",(int)buffer.st_size);

    return 0;
}
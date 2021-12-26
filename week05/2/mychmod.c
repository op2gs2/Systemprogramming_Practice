#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char permission_char1[9]="---------";
char permission_char2[9]="";

char* permission_to_char(int);
void analyze_permission_chmod(char*, int);

int main(int argc, char *argv[]){
	/*변수 초기화*/
    struct stat buffer;
    char *filename="";

    /* 인자 확인 및 파일 이름 설정*/
    if (argc == 2){
        filename = argv[1];
    } else if(argc == 3){
        filename = argv[2];
    } else{
        fprintf(stderr,"Worng Argument Numbers!");
        exit(1);
    }

    /*stat실행을 실패하면 종료*/
	if (stat(filename,&buffer) == -1){
        perror(argv[1]);
		exit(1);
    }

    /*파일의 권한을 문자열로 받아오기*/
    permission_to_char(buffer.st_mode);
    

    #ifdef DEBUG
    printf("변환된 권한: %s\n",permission_char2);
    #endif

    // argc = 2일 때는, 접근 권한만을 출력한다.
    if(argc == 2){
        printf("Permission : %s\n",permission_char1);
        return 0;
    } else{
        analyze_permission_chmod(filename,atoi(argv[1]));
        printf("Permission (before) : %s\n",permission_char1);
        printf("Permission (after) : %s\n",permission_char2);
    }

    return 0;
}

/*파일의 접근 권한을 파악하여, 문자열로 변환함*/
char* permission_to_char(int st_mode){

    #ifdef DEBUG
    printf("권한 변환 시작\n");
    #endif

    // 사용자 권한 검사
    if ((st_mode & S_IREAD) != 0){
        permission_char1[0]='r';
    }
    if((st_mode & S_IWRITE) != 0){
        permission_char1[1]='w';
    }
    if((st_mode & S_IEXEC) != 0){
        permission_char1[2]='x';
    }
    
    // 그룹 권한 검사
    if ((st_mode & (S_IREAD >> 3)) != 0){
        permission_char1[3]='r';
    }
    if((st_mode & (S_IWRITE >> 3)) != 0){
        permission_char1[4]='w';
    }
    if((st_mode & (S_IEXEC >> 3)) != 0){
        permission_char1[5]='x';
    }

    // 기타 사용자 권한 검사
    if ((st_mode & (S_IREAD >> 6)) != 0){
        permission_char1[6]='r';
    }
    if((st_mode & (S_IWRITE >> 6)) != 0){
        permission_char1[7]='w';
    }
    if((st_mode & (S_IEXEC >> 6)) != 0){
        permission_char1[8]='x';
    }

    #ifdef DEBUG
    printf("권한 변환 끝\n");
    #endif

    return permission_char1;
}

void analyze_permission_chmod(char* filename, int init_permission){
    // 인자로 주어진 권한 분석하기
    int user_perm = init_permission / 100;
    init_permission -= (user_perm * 100);
    int group_perm = init_permission / 10;
    init_permission -= (group_perm * 10);
    int other_perm = init_permission / 1;

    #ifdef DEBUG
    printf("User: %d\n",user_perm);
    printf("Group: %d\n",group_perm);
    printf("Other: %d\n",other_perm);
    #endif


    int permission = 0;

    #ifdef DEBUG
    printf("Analyze Permission Start!\n");
    #endif

    // 분석한 권한을 기반으로, 권한 변경하기
    switch (user_perm)
    {
    case 7:
        permission |= S_IRWXU;
        strcat(permission_char2,"rwx");
        break;
    case 4:
        permission |= S_IRUSR;
        strcat(permission_char2,"r");
        break;
    case 2:
        permission |= S_IWUSR;
        strcat(permission_char2,"w");
        break;
    case 1:
        permission |= S_IXUSR;
        strcat(permission_char2,"x");
        break;
    default:
        strcat(permission_char2,"---");
    }

    switch (group_perm)
    {
    case 7:
        permission |= S_IRWXG;
        strcat(permission_char2,"rwx");
        break;
    case 4:
        permission |= S_IRGRP;
        strcat(permission_char2,"r");
        break;
    case 2:
        permission |= S_IWGRP;
        strcat(permission_char2,"w");
        break;
    case 1:
        permission |= S_IXGRP;
        strcat(permission_char2,"x");
        break;
    default:
        strcat(permission_char2,"---");
    }

    switch (other_perm)
    {
    case 7:
        permission |= S_IRWXO;
        strcat(permission_char2,"rwx");
        break;
    case 4:
        permission |= S_IROTH;
        strcat(permission_char2,"r");
        break;
    case 2:
        permission |= S_IWOTH;
        strcat(permission_char2,"w");
        break;
    case 1:
        permission |= S_IXOTH;
        strcat(permission_char2,"x");
        break;
    default:
        strcat(permission_char2,"---");
    }

    if(chmod(filename, permission)!=0){
        perror("chmod");
        exit(1);
    }

    #ifdef DEBUG
    printf("chmod Done!\n");
    #endif

}